// Copyright 2022 atframework
// Created by owent on 2021-07-13.
//

#pragma once

#include <config/compile_optimize.h>

// clang-format off
#include <config/compiler/protobuf_prefix.h>
// clang-format on

#include <google/protobuf/timestamp.pb.h>

#include <protocol/pbdesc/atframework.pb.h>

#include <opentelemetry/trace/span.h>
#include <opentelemetry/trace/tracer.h>

// clang-format off
#include <config/compiler/protobuf_suffix.h>
// clang-format on

#include <stdint.h>
#include <chrono>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class dispatcher_implement;

namespace rpc {

namespace telemetry {

template <class T>
class UTIL_SYMBOL_VISIBLE multiple_key_value_iterable_view final : public opentelemetry::common::KeyValueIterable {
 public:
  explicit multiple_key_value_iterable_view(opentelemetry::nostd::span<const T> containers) noexcept
      : containers_{containers} {}

  // KeyValueIterable
  bool ForEachKeyValue(
      opentelemetry::nostd::function_ref<bool(opentelemetry::nostd::string_view, opentelemetry::common::AttributeValue)>
          callback) const noexcept override {
    for (auto& container : containers_) {
      auto element_iter = std::begin(container);
      auto element_last = std::end(container);
      for (; element_iter != element_last; ++element_iter) {
        if (!callback(element_iter->first, element_iter->second)) {
          return false;
        }
      }
    }
    return true;
  }

  size_t size() const noexcept override {
    size_t ret = 0;
    for (auto& container : containers_) {
      ret += opentelemetry::nostd::size(container);
    }
    return ret;
  }

 private:
  opentelemetry::nostd::span<const T> containers_;
};

using trace_link_pair_type = std::pair<
    opentelemetry::trace::SpanContext,
    std::initializer_list<std::pair<opentelemetry::nostd::string_view, opentelemetry::common::AttributeValue>>>;
using trace_links_type = opentelemetry::nostd::span<const trace_link_pair_type>;
using trace_attribute_pair_type = std::pair<opentelemetry::nostd::string_view, opentelemetry::common::AttributeValue>;
using trace_attributes_type = opentelemetry::nostd::span<const trace_attribute_pair_type>;

struct UTIL_SYMBOL_VISIBLE trace_start_option {
  using string_view = opentelemetry::nostd::string_view;
  using span_ptr_type = opentelemetry::nostd::shared_ptr<opentelemetry::trace::Span>;
  using trace_id_span = opentelemetry::nostd::span<const uint8_t, opentelemetry::trace::TraceId::kSize>;
  using span_id_span = opentelemetry::nostd::span<const uint8_t, opentelemetry::trace::SpanId::kSize>;

  std::shared_ptr<dispatcher_implement> dispatcher;
  atframework::RpcTraceSpan::SpanKind kind;
  bool is_remote;
  const ::atframework::RpcTraceSpan* parent_network_span;
  span_ptr_type parent_memory_span;
  trace_links_type links;
  trace_attributes_type attributes;

  inline trace_start_option()
      : dispatcher(nullptr),
        kind(atframework::RpcTraceSpan::SPAN_KIND_INTERNAL),
        is_remote(true),
        parent_network_span(nullptr),
        parent_memory_span(nullptr),
        links({}),
        attributes({}) {}
};

struct UTIL_SYMBOL_VISIBLE trace_finish_option {
  int32_t result_code;
  trace_attributes_type attributes;

  inline trace_finish_option() : result_code(0), attributes({}) {}

  inline trace_finish_option(int32_t code, trace_attributes_type attrs) : result_code(code), attributes(attrs) {}
};

class tracer {
 public:
  using string_view = trace_start_option::string_view;
  using span_ptr_type = trace_start_option::span_ptr_type;
  using trace_id_span = trace_start_option::trace_id_span;
  using span_id_span = trace_start_option::span_id_span;

 public:
  SERVER_FRAME_API tracer();
  SERVER_FRAME_API ~tracer();

  SERVER_FRAME_API tracer(tracer&& other);
  SERVER_FRAME_API tracer& operator=(tracer&& other) noexcept;

  SERVER_FRAME_API bool start(string_view name, trace_start_option&& options);
  SERVER_FRAME_API int32_t finish(trace_finish_option&& options);

  UTIL_FORCEINLINE const tracer::span_ptr_type& get_trace_span() const { return trace_span_; }

  /**
   * @brief Set the trace name
   *
   * @param name
   */
  SERVER_FRAME_API void update_trace_name(string_view name);

 private:
  friend class context;
  std::chrono::system_clock::time_point start_system_timepoint_;
  std::chrono::steady_clock::time_point start_steady_timepoint_;
  span_ptr_type trace_span_;
  std::string trace_span_name_;
  opentelemetry::nostd::string_view span_kind_;
  std::shared_ptr<dispatcher_implement> dispatcher_;
};

}  // namespace telemetry

}  // namespace rpc
