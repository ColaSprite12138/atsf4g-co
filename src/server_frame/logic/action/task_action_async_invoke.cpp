﻿// Copyright 2021 atframework
// @brief Created by owent on 2021-11-01 13:17:07

#include "task_action_async_invoke.h"

#include <config/compiler/protobuf_prefix.h>

#include <protocol/pbdesc/svr.const.err.pb.h>

#include <config/compiler/protobuf_suffix.h>

#include <log/log_wrapper.h>
#include <std/explicit_declare.h>
#include <time/time_utility.h>

#include <config/logic_config.h>
#include <utility/protobuf_mini_dumper.h>

task_action_async_invoke::task_action_async_invoke(ctor_param_t&& param)
    : task_action_no_req_base(param), param_(param) {}

task_action_async_invoke::~task_action_async_invoke() {}

const char* task_action_async_invoke::name() const { return param_.name.c_str(); }

int task_action_async_invoke::operator()() {
  if (param_.callable) {
    return param_.callable(get_shared_context());
  }
  return PROJECT_SERVER_FRAME_NAMESPACE_ID::err::EN_SUCCESS;
}
