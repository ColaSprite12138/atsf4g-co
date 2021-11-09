﻿// Copyright 2021 atframework
// Created by owent with generate-for-pb.py at 2020-07-10 21:34:16

#include <config/compiler/protobuf_prefix.h>

#include <protocol/pbdesc/svr.const.err.pb.h>
#include <protocol/pbdesc/svr.protocol.pb.h>

#include <config/compiler/protobuf_suffix.h>

#include <log/log_wrapper.h>
#include <std/explicit_declare.h>
#include <time/time_utility.h>

#include <config/logic_config.h>
#include <utility/protobuf_mini_dumper.h>

#include <config/extern_service_types.h>

#include "router/router_manager_base.h"
#include "router/router_manager_set.h"

#include "task_action_router_update_sync.h"

task_action_router_update_sync::task_action_router_update_sync(dispatcher_start_data_t&& param)
    : base_type(COPP_MACRO_STD_MOVE(param)) {}
task_action_router_update_sync::~task_action_router_update_sync() {}

bool task_action_router_update_sync::is_stream_rpc() const { return true; }

int task_action_router_update_sync::operator()() {
  const rpc_request_type& req_body = get_request_body();
  // Stream request or stream response, just ignore auto response
  disable_rsp_msg();

  router_manager_base* mgr = router_manager_set::me()->get_manager(req_body.object().object_type_id());
  if (nullptr == mgr) {
    FWLOGERROR("router manager {} invalid", req_body.object().object_type_id());
    return hello::err::EN_SUCCESS;
  }

  router_manager_base::key_t key(req_body.object().object_type_id(), req_body.object().object_zone_id(),
                                 req_body.object().object_inst_id());
  std::shared_ptr<router_object_base> obj = mgr->get_base_cache(key);
  if (!obj) {
    return hello::err::EN_SUCCESS;
  }

  if (obj->get_router_version() < req_body.object().router_version()) {
    // router_src_bus_id字段是复用的
    obj->set_router_server_id(req_body.object().router_src_bus_id(), req_body.object().router_version());
  }

  return hello::err::EN_SUCCESS;
}

int task_action_router_update_sync::on_success() { return get_ret_code(); }

int task_action_router_update_sync::on_failed() { return get_ret_code(); }
