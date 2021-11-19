// Copyright 2021 atframework
// Created by owent on 2019/06/20.
//

#include "router/action/task_action_router_close_manager_set.h"

#include <config/compiler/protobuf_prefix.h>

#include <protocol/pbdesc/svr.const.err.pb.h>

#include <config/compiler/protobuf_suffix.h>

#include <log/log_wrapper.h>
#include <time/time_utility.h>

#include <config/logic_config.h>
#include <utility/protobuf_mini_dumper.h>

#include <libatbus_protocol.h>

#include <rpc/rpc_async_invoke.h>

#include <utility>

#include "router/router_manager_base.h"
#include "router/router_manager_set.h"
#include "router/router_object_base.h"

task_action_router_close_manager_set::task_action_router_close_manager_set(ctor_param_t &&param)
    : task_action_no_req_base(param), param_(param), status_data_(std::make_shared<status_data_t>()) {
  status_data_->success_count_ = 0;
  status_data_->failed_count_ = 0;
  status_data_->current_idx_ = 0;
}

task_action_router_close_manager_set::~task_action_router_close_manager_set() {}

task_action_router_close_manager_set::result_type task_action_router_close_manager_set::operator()() {
  FWLOGINFO("router close task started");
  status_data_->success_count_ = 0;
  status_data_->failed_count_ = 0;

  util::time::time_utility::update();

  task_manager::task_t *task = task_manager::task_t::this_task();
  if (!task) {
    FWLOGERROR("current not in a task");
    return PROJECT_SERVER_FRAME_NAMESPACE_ID::err::EN_SYS_RPC_NO_TASK;
  }

  size_t closing_action_batch_count = logic_config::me()->get_cfg_router().closing_action_batch_count();
  std::vector<task_manager::task_ptr_t> pending_action_batch_tasks;
  pending_action_batch_tasks.reserve(closing_action_batch_count);

  while (param_.pending_list && status_data_->current_idx_ < param_.pending_list->size()) {
    std::shared_ptr<status_data_t> status_data = status_data_;
    pending_list_ptr_t pending_list = param_.pending_list;
    auto invoke_task = rpc::async_invoke(
        get_shared_context(), "task_action_router_close_manager_set",
        [status_data, pending_list](rpc::context &ctx) -> task_action_base::result_type {
          task_manager::task_t *sub_task = task_manager::task_t::this_task();
          if (!sub_task) {
            FWLOGERROR("current not in a task");
            return task_action_base::result_type(PROJECT_SERVER_FRAME_NAMESPACE_ID::err::EN_SYS_RPC_NO_TASK);
          }

          router_object_ptr_t obj = (*pending_list)[status_data->current_idx_];
          ++status_data->current_idx_;

          // 如果已下线并且用户缓存失效则跳过
          if (!obj) {
            return task_action_base::result_type(0);
          }

          // 已降级或不是实体，不需要保存
          if (!obj->check_flag(router_object_base::flag_t::EN_ROFT_IS_OBJECT)) {
            return task_action_base::result_type(0);
          }

          router_manager_base *mgr = router_manager_set::me()->get_manager(obj->get_key().type_id);
          if (nullptr == mgr) {
            FWLOGERROR("router close task save router object {}({}:{}:{}) but can not find manager", obj->name(),
                       obj->get_key().type_id, obj->get_key().zone_id, obj->get_key().object_id);
            ++status_data->failed_count_;
            return task_action_base::result_type(0);
          }

          // 管理器中的对象已被替换或移除则跳过
          if (mgr->get_base_cache(obj->get_key()) != obj) {
            return task_action_base::result_type(0);
          }

          // 降级的时候会保存
          bool res = mgr->remove_object(obj->get_key(), obj, nullptr);

          if (sub_task->is_timeout()) {
            FWLOGERROR("router close task save router object {}({}:{}:{}) timeout", obj->name(), obj->get_key().type_id,
                       obj->get_key().zone_id, obj->get_key().object_id);
            ++status_data->failed_count_;
            return task_action_base::result_type(0);
          }

          if (sub_task->is_canceled()) {
            FWLOGERROR("router close task save router object {}({}:{}:{}) but cancelled", obj->name(),
                       obj->get_key().type_id, obj->get_key().zone_id, obj->get_key().object_id);
            ++status_data->failed_count_;
            return task_action_base::result_type(0);
          }

          if (sub_task->is_faulted()) {
            FWLOGERROR("router close task save router object {}({}:{}:{}) but killed", obj->name(),
                       obj->get_key().type_id, obj->get_key().zone_id, obj->get_key().object_id);
            ++status_data->failed_count_;
            return task_action_base::result_type(0);
          }

          if (!res) {
            FWLOGERROR("router close task save router object {}({}:{}:{}) failed", obj->name(), obj->get_key().type_id,
                       obj->get_key().zone_id, obj->get_key().object_id);
            ++status_data->failed_count_;
          } else {
            FWLOGINFO("router close task save router object {}({}:{}:{}) success", obj->name(), obj->get_key().type_id,
                      obj->get_key().zone_id, obj->get_key().object_id);
            ++status_data->success_count_;
          }
          return task_action_base::result_type(0);
        });
    bool need_wait = false;
    if (invoke_task.is_success()) {
      if (!(*invoke_task.get_success())->is_exiting()) {
        pending_action_batch_tasks.emplace_back(std::move(*invoke_task.get_success()));
      }
    } else {
      need_wait = true;
    }
    if (pending_action_batch_tasks.size() >= closing_action_batch_count) {
      need_wait = true;
    }

    if (need_wait) {
      auto wait_result = rpc::wait_tasks(pending_action_batch_tasks);
      pending_action_batch_tasks.clear();
      if (wait_result.is_error()) {
        FWLOGERROR("Wait sub tasks to remove_object failed, result: {}({})", *wait_result.get_error(),
                   protobuf_mini_dumper_get_error_msg(*wait_result.get_error()));
      }
    }
  }

  if (!pending_action_batch_tasks.empty()) {
    auto wait_result = rpc::wait_tasks(pending_action_batch_tasks);
    pending_action_batch_tasks.clear();
    if (wait_result.is_error()) {
      FWLOGERROR("Wait sub tasks to remove_object failed, result: {}({})", *wait_result.get_error(),
                 protobuf_mini_dumper_get_error_msg(*wait_result.get_error()));
    }
  }

  // 如果超时了可能被强杀，这时候要强制触发保存
  if (task->is_exiting()) {
    save_fallback();
  }

  return PROJECT_SERVER_FRAME_NAMESPACE_ID::err::EN_SUCCESS;
}

void task_action_router_close_manager_set::save_fallback() {
  while (param_.pending_list && status_data_->current_idx_ < param_.pending_list->size()) {
    router_object_ptr_t obj = (*param_.pending_list)[status_data_->current_idx_];
    ++status_data_->current_idx_;

    // 如果已下线并且用户缓存失效则跳过
    if (!obj) {
      continue;
    }

    // 已降级或不是实体，不需要保存
    if (!obj->check_flag(router_object_base::flag_t::EN_ROFT_IS_OBJECT)) {
      continue;
    }

    router_manager_base *mgr = router_manager_set::me()->get_manager(obj->get_key().type_id);
    if (nullptr == mgr) {
      FWLOGERROR("router close task save router object {}({}:{}:{}) but can not find manager", obj->name(),
                 obj->get_key().type_id, obj->get_key().zone_id, obj->get_key().object_id);
      ++status_data_->failed_count_;
      continue;
    }

    // 管理器中的对象已被替换或移除则跳过
    if (mgr->get_base_cache(obj->get_key()) != obj) {
      continue;
    }

    // 降级的时候会保存
    mgr->remove_object(obj->get_key(), obj, nullptr);

    FWLOGWARNING(
        "router close task save router object {}({}:{}:{}) for fallback(task killed), we don't know if it's success "
        "to save to DB",
        obj->name(), obj->get_key().type_id, obj->get_key().zone_id, obj->get_key().object_id);
  }
}

int task_action_router_close_manager_set::on_success() {
  if (router_manager_set::me()->closing_task_.get() == task_manager::task_t::this_task()) {
    router_manager_set::me()->closing_task_.reset();
  }

  FWLOGINFO("router close task done.(success save: {}, failed save: {})", status_data_->success_count_,
            status_data_->failed_count_);
  return get_result();
}

int task_action_router_close_manager_set::on_failed() {
  if (router_manager_set::me()->closing_task_.get() == task_manager::task_t::this_task()) {
    router_manager_set::me()->closing_task_.reset();
  }

  FWLOGERROR("router close task failed.(success save: {}, failed save: {}) ret: {}", status_data_->success_count_,
             status_data_->failed_count_, get_result());
  return get_result();
}

int task_action_router_close_manager_set::on_timeout() {
  if (router_manager_set::me()->closing_task_.get() == task_manager::task_t::this_task()) {
    router_manager_set::me()->closing_task_.reset();
  }

  FWLOGWARNING("router close task timeout, we will continue on next round.");
  return 0;
}
