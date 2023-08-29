// Copyright 2021 atframework
// Created by owent on 2016/10/4.
//

#pragma once

#include <design_pattern/nomovable.h>
#include <design_pattern/noncopyable.h>
#include <design_pattern/result_type.h>
#include <gsl/select-gsl.h>
#include <time/time_utility.h>

// clang-format off
#include <config/compiler/protobuf_prefix.h>
// clang-format on

#include <google/protobuf/arena.h>
#include <google/protobuf/duration.pb.h>
#include <google/protobuf/timestamp.pb.h>

#include <protocol/pbdesc/atframework.pb.h>

// clang-format off
#include <config/compiler/protobuf_suffix.h>
// clang-format on

#include <config/server_frame_build_feature.h>

#include <std/explicit_declare.h>

#include <stdint.h>
#include <chrono>
#include <cstddef>
#include <functional>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "dispatcher/dispatcher_type_defines.h"
#include "dispatcher/task_type_traits.h"
#include "rpc/rpc_common_types.h"
#include "rpc/telemetry/rpc_trace.h"

namespace atapp {
class app;
}

PROJECT_NAMESPACE_BEGIN
namespace config {
class logic_telemetry_cfg;
}

class table_all_message;
PROJECT_NAMESPACE_END

namespace atframework {
class SSMsg;
}

namespace rpc {
class context {
 public:
  using string_view = opentelemetry::nostd::string_view;
  using tracer = rpc::telemetry::tracer;
  using trace_option = rpc::telemetry::trace_option;

  enum class parent_mode : uint8_t {
    kParent = 0,
    kLink = 1,
  };

  struct UTIL_SYMBOL_VISIBLE inherit_options {
    parent_mode mode;
    bool inherit_allocator;
    bool inherit_parent_span;

    inline inherit_options() noexcept
        : mode(parent_mode::kParent), inherit_allocator(true), inherit_parent_span(true) {}
    explicit inline inherit_options(parent_mode m) noexcept
        : mode(m), inherit_allocator(true), inherit_parent_span(true) {}
    explicit inline inherit_options(parent_mode m, bool inherit_alloc) noexcept
        : mode(m), inherit_allocator(inherit_alloc), inherit_parent_span(true) {}
    explicit inline inherit_options(parent_mode m, bool inherit_alloc, bool inherit_parent_trace_span) noexcept
        : mode(m), inherit_allocator(inherit_alloc), inherit_parent_span(inherit_parent_trace_span) {}
  };

  struct UTIL_SYMBOL_VISIBLE create_options {};

  struct UTIL_SYMBOL_VISIBLE task_context_data {
    uint64_t task_id;
    inline task_context_data() noexcept : task_id(0){};
  };

  template <class TMsg>
  struct UTIL_SYMBOL_VISIBLE message_holder {
    explicit message_holder(context &ctx) : arena_msg_ptr_(ctx.create<TMsg>()) {}
    explicit message_holder(message_holder &&other) : arena_msg_ptr_(nullptr) {
      using std::swap;

      if (other->GetArena() != nullptr) {
        arena_msg_ptr_ = ::google::protobuf::Arena::CreateMessage<TMsg>(other->GetArena());
      }
      swap(arena_msg_ptr_, other.arena_msg_ptr_);
      local_msg_.Swap(&other.local_msg_);
    }

    message_holder &operator=(message_holder &&other) {
      using std::swap;

      swap(arena_msg_ptr_, other.arena_msg_ptr_);
      local_msg_.Swap(&other.local_msg_);

      return *this;
    }

    inline const TMsg *operator->() const {
      UTIL_UNLIKELY_IF(nullptr == arena_msg_ptr_) { return &local_msg_; }

      return arena_msg_ptr_;
    }

    inline TMsg *operator->() {
      UTIL_UNLIKELY_IF(nullptr == arena_msg_ptr_) { return &local_msg_; }

      return arena_msg_ptr_;
    }

    inline const TMsg &operator*() const {
      UTIL_UNLIKELY_IF(nullptr == arena_msg_ptr_) { return local_msg_; }

      return *arena_msg_ptr_;
    }

    inline TMsg &operator*() {
      UTIL_UNLIKELY_IF(nullptr == arena_msg_ptr_) { return local_msg_; }

      return *arena_msg_ptr_;
    }

    UTIL_DESIGN_PATTERN_NOCOPYABLE(message_holder)

   private:
    TMsg *arena_msg_ptr_;
    TMsg local_msg_;
  };

 private:
  context(const context &) = delete;
  context &operator=(const context &) = delete;
  context &operator=(context &&) = delete;

  SERVER_FRAME_API context() noexcept;

 public:
  SERVER_FRAME_API explicit context(context &&other) noexcept;
  SERVER_FRAME_API context(context &parent, inherit_options options = {}) noexcept;
  SERVER_FRAME_API ~context();

  /**
   * @brief 创建和任务无关的RPC上下文，通常用于记录链路跟踪关系。
   *
   * @param options 创建选项
   * @return context 创建的子上下文对象
   */
  SERVER_FRAME_API static context create_without_task(create_options options = {}) noexcept;

  /**
   * @brief 创建临时的子上下文，通常用于协程栈上需要加一层链路跟踪。
   * @note 如果涉及异步调用和传递生命周期，请使用 create_shared_child
   *
   * @param options 继承选项
   * @return context 创建的子上下文对象
   */
  SERVER_FRAME_API context create_temporary_child(inherit_options options = {}) noexcept;

  /**
   * @brief 创建共享的子上下文，通常用于异步调用时保留链路信息。
   * @note 如果不涉及异步调用和传递生命周期，请使用 create_temporary_child
   *
   * @param options 继承选项
   * @return std::shared_ptr<context> 创建的子上下文智能指针
   */
  SERVER_FRAME_API std::shared_ptr<context> create_shared_child(inherit_options options = {}) noexcept;

  SERVER_FRAME_API void setup_tracer(
      tracer &, string_view name, trace_option &&options,
      std::initializer_list<std::pair<opentelemetry::nostd::string_view, opentelemetry::common::AttributeValue>>
          attributes = {});

  /**
   * @brief 创建链路跟踪器信息。
   * @note 如果不涉及异步调用和传递生命周期，请使用 create_temporary_child
   *
   * @param name 链路跟踪名称
   * @param options 继承选项
   * @param attributes 自定义属性
   * @return 链路跟踪器
   */
  EXPLICIT_DEPRECATED_ATTR SERVER_FRAME_API tracer
  make_tracer(string_view name, trace_option &&options,
              std::initializer_list<std::pair<opentelemetry::nostd::string_view, opentelemetry::common::AttributeValue>>
                  attributes = {});

  /**
   * @brief 使用内置的Arena创建protobuf对象。注意，该对象必须是局部变量，不允许转移给外部使用
   *
   * @tparam message类型
   * @return 在arena上分配的对象，失败返回nullptr
   */
  template <class TMSG>
  UTIL_SYMBOL_VISIBLE TMSG *create() {
    // 上面的分支减少一次atomic操作
    if (allocator_) {
      return ::google::protobuf::Arena::CreateMessage<TMSG>(allocator_.get());
    }

    auto arena = mutable_protobuf_arena();
    if (!arena) {
      return nullptr;
    }

    return ::google::protobuf::Arena::CreateMessage<TMSG>(arena.get());
  }

  SERVER_FRAME_API std::shared_ptr<::google::protobuf::Arena> mutable_protobuf_arena();
  SERVER_FRAME_API const std::shared_ptr<::google::protobuf::Arena> &get_protobuf_arena() const;
  SERVER_FRAME_API bool try_reuse_protobuf_arena(const std::shared_ptr<::google::protobuf::Arena> &arena) noexcept;

  SERVER_FRAME_API const tracer::span_ptr_type &get_trace_span() const noexcept;

  SERVER_FRAME_API void set_parent_context(rpc::context &parent, inherit_options options = {}) noexcept;
  SERVER_FRAME_API void add_link_span(const tracer::span_ptr_type &span_ptr) noexcept;

  /**
   * @brief Set the current service object, it's used for tracer
   * @param app atapp instance
   * @param telemetry telemetry configure
   */
  SERVER_FRAME_API static void set_current_service(atapp::app &app,
                                                   const PROJECT_NAMESPACE_ID::config::logic_telemetry_cfg &telemetry);

  SERVER_FRAME_API void set_task_context(const task_context_data &task_ctx) noexcept;
  UTIL_FORCEINLINE const task_context_data &get_task_context() const noexcept { return task_context_; }

 private:
  std::shared_ptr<::google::protobuf::Arena> allocator_;
  struct trace_context_data {
    tracer::span_ptr_type trace_span;
    tracer::span_ptr_type parent_span;
    parent_mode caller_mode;
    std::vector<tracer::span_ptr_type> link_spans;
  };
  trace_context_data trace_context_;
  task_context_data task_context_;
};

UTIL_FORCEINLINE std::chrono::system_clock::duration make_duration(
    const std::chrono::system_clock::duration &value) noexcept {
  return value;
}

template <class Rep, class Period>
UTIL_FORCEINLINE std::chrono::system_clock::duration make_duration(
    const std::chrono::duration<Rep, Period> &value) noexcept {
  return std::chrono::duration_cast<std::chrono::system_clock::duration>(value);
}

UTIL_FORCEINLINE std::chrono::system_clock::duration make_duration(const google::protobuf::Duration &value) noexcept {
  return std::chrono::duration_cast<std::chrono::system_clock::duration>(std::chrono::seconds{value.seconds()}) +
         std::chrono::duration_cast<std::chrono::system_clock::duration>(std::chrono::nanoseconds{value.nanos()});
}

template <class Rep, class Period>
UTIL_FORCEINLINE std::chrono::system_clock::duration make_duration_or_default(
    const google::protobuf::Duration &value, const std::chrono::duration<Rep, Period> &default_value) noexcept {
  if (value.seconds() > 0 || value.nanos() > 0) {
    return make_duration(value);
  }

  return make_duration(default_value);
}

/**
 * @brief sleep and wait a moment
 *
 * @param timeout
 * @return future of 0 or error code
 */
SERVER_FRAME_API result_code_type wait(context &ctx, std::chrono::system_clock::duration timeout);

/**
 * @brief sleep and wait a moment
 *
 * @tparam Rep
 * @tparam Period
 * @param timeout
 * @return future of 0 or error code
 */
template <class Rep, class Period>
UTIL_FORCEINLINE result_code_type wait(context &ctx, std::chrono::duration<Rep, Period> timeout) {
  return wait(ctx, make_duration(timeout));
}

SERVER_FRAME_API result_code_type wait(context &ctx, atframework::SSMsg &msg, const dispatcher_await_options &options);
SERVER_FRAME_API result_code_type wait(context &ctx, PROJECT_NAMESPACE_ID::table_all_message &msg,
                                       const dispatcher_await_options &options);

/**
 * @brief wait for multiple messages
 *
 * @param waiters sequences of waiting messages
 * @param received received messages
 * @param wakeup_count wakeup and return after got this count of messages(0 means wait all)
 * @return future of 0 or error code
 */
SERVER_FRAME_API result_code_type wait(context &ctx, const std::unordered_set<dispatcher_await_options> &waiters,
                                       std::unordered_map<uint64_t, atframework::SSMsg> &received,
                                       size_t wakeup_count = 0);

/**
 * @brief wait for multiple messages
 *
 * @param waiters sequences of waiting messages
 * @param received received messages
 * @param wakeup_count wakeup and return after got this count of messages(0 means wait all)
 * @return future of 0 or error code
 */
SERVER_FRAME_API result_code_type wait(context &ctx, const std::unordered_set<dispatcher_await_options> &waiters,
                                       std::unordered_map<uint64_t, atframework::SSMsg *> &received,
                                       size_t wakeup_count = 0);

/**
 * @brief Custom wait for a message or resume
 *
 * @param type_address type object address, user should keep it unique for each message type
 * @param options await options
 * @param receive_callback callback to read data from dispatcher_resume_data_type
 * @param receive_callback_private_data private data of receive_callback, should be alive before resumed
 * @return future of 0 or error code
 */
SERVER_FRAME_API result_code_type custom_wait(context &ctx, const void *type_address,
                                              const dispatcher_await_options &options,
                                              dispatcher_receive_resume_data_callback receive_callback = nullptr,
                                              void *receive_callback_private_data = nullptr);

template <class TPTR>
UTIL_FORCEINLINE const void *custom_wait_convert_ptr(TPTR &&input) {
  return reinterpret_cast<void *>(input);
}

UTIL_FORCEINLINE const void *custom_wait_convert_ptr(const void *input) { return input; }

UTIL_FORCEINLINE const void *custom_wait_convert_ptr(void *input) { return const_cast<void *>(input); }

/**
 * @brief Custom wait for a message or resume
 *
 * @param type_address type object address, user should keep it unique for each message type
 * @param options await options
 * @param real_callback callback to read data from dispatcher_resume_data_type
 * @param real_private_data private data of receive_callback, should be alive before resumed
 * @return future of 0 or error code
 */
template <class TPRIVATE_DATA, class TCALLBACK, class TPTR,
          class = typename std::enable_if<std::is_pointer<typename std::remove_reference<TPTR>::type>::value>::type>
UTIL_SYMBOL_VISIBLE result_code_type custom_wait(context &ctx, TPTR &&type_address,
                                                 const dispatcher_await_options &options,
                                                 TCALLBACK && real_callback,
                                                 TPRIVATE_DATA &&real_private_data) {
  auto callback_data = std::make_pair(real_callback, &real_private_data);
  using callback_date_type = decltype(callback_data);

  dispatcher_receive_resume_data_callback receive_callback = [](const dispatcher_resume_data_type *resume_data,
                                                                void *stack_data) {
    callback_date_type *restore_callback_data = reinterpret_cast<callback_date_type *>(stack_data);
    if (nullptr != restore_callback_data && restore_callback_data->first &&
        nullptr != restore_callback_data->second) {
      (restore_callback_data->first)(resume_data, std::forward<TPRIVATE_DATA>(*restore_callback_data->second));
    }
  };

  RPC_RETURN_CODE(RPC_AWAIT_CODE_RESULT(custom_wait(ctx, custom_wait_convert_ptr(type_address), options,
                                                    receive_callback, reinterpret_cast<void *>(&callback_data))));
}

/**
 * @brief Custom resume a waiter
 *
 * @param task task to resume
 * @param resume_data resume data
 * @return 0 or error code
 */
SERVER_FRAME_API int32_t custom_resume(const task_type_trait::task_type &task,
                                       dispatcher_resume_data_type &resume_data);

/**
 * @brief Custom resume a waiter
 *
 * @param task_id id of task to resume
 * @param resume_data resume data
 * @return 0 or error code
 */
SERVER_FRAME_API int32_t custom_resume(task_type_trait::id_type task_id, dispatcher_resume_data_type &resume_data);

}  // namespace rpc
