﻿## -*- coding: utf-8 -*-
<%!
import time
%><%namespace name="pb_loader" module="pb_loader"/>
// Copyright ${time.strftime("%Y")} xresloader. All rights reserved.
// Generated by xres-code-generator, please don't edit it
//

#pragma once

#include <stdint.h>
#include <cstddef>
#include <cstdio>
#include <functional>
#include <list>
#include <string>
#include <memory>
#include <cstring>
#include <type_traits>

#include "lock/spin_rw_lock.h"

#include "config/compiler/protobuf_prefix.h"

#include "google/protobuf/descriptor.h"
#include "google/protobuf/message.h"

#include "protocol/config/pb_header_v3.pb.h"

#include "config/compiler/protobuf_suffix.h"

% for pb_msg in pb_set.generate_message:
%   for loader in pb_msg.loaders:
#include "${loader.get_cpp_header_path()}"
%   endfor
% endfor

${pb_loader.CppNamespaceBegin(global_package)}
struct config_group_t {
  std::string version;

% for pb_msg in pb_set.generate_message:
%   for loader in pb_msg.loaders:
  ${pb_loader.CppFullPath(global_package)}${loader.get_cpp_class_full_name()} ${loader.get_cpp_public_var_name()} ;
%   endfor
% endfor

% for block_file in pb_set.get_custom_blocks("custom_config_group"):
<%include file="${block_file}" />
% endfor
} ;

class config_manager {
public:
  using read_buffer_func_t = std::function<bool(std::string&, const char* path)>;
  using read_version_func_t = std::function<bool(std::string&)>;
  using config_group_ptr_t = std::shared_ptr<config_group_t>;
  using on_load_func_t = std::function<void(config_group_ptr_t)>;
  using on_filter_func_t = std::function<bool(org::xresloader::pb::xresloader_datablocks&, const ::google::protobuf::Descriptor*, const std::string&)>;

  struct on_not_found_event_data_t {
    const std::list<org::xresloader::pb::xresloader_data_source>* data_source;
    const ::google::protobuf::Descriptor* message_descriptor;
    const char* index_name;
    const char* keys;
    bool is_list;
    size_t list_index;
  };
  using on_not_found_func_t = std::function<void(const on_not_found_event_data_t&)>;

  struct log_level_t {
    enum type {
      LOG_LW_DISABLED = 0, // 关闭日志
      LOG_LW_ERROR,        // 错误
      LOG_LW_WARNING,
      LOG_LW_INFO,
      LOG_LW_DEBUG,
    };
  };

  struct log_caller_info_t {
    log_level_t::type level_id;
    const char *  level_name;
    const char *  file_path;
    uint32_t      line_number;
    const char *  func_name;

    log_caller_info_t();
    log_caller_info_t(log_level_t::type lid, const char *lname, const char *fpath, uint32_t lnum, const char *fnname);
  };

  using on_log_func_t = std::function<void(const log_caller_info_t& caller, const char* content)>;

private:
  config_manager();
  struct constructor_helper_t {};

public:
  config_manager(constructor_helper_t&);
  ~config_manager();

  static std::shared_ptr<config_manager> me();
  static inline std::shared_ptr<config_manager> instance() { return me(); };

  int init();

  int init_new_group();

  void reset();

  void clear();

  bool load_file_data(std::string& write_to, const std::string& file_path);

  /**
   * @brief 执行reload，如果版本号变化则要重新加载文件
   */
  int reload();

  /**
   * @brief 执行reload加载所有资源
   * @param del_when_failed 如果失败是否删除分组
   */
  int reload_all(bool del_when_failed = false);

  read_buffer_func_t get_buffer_loader() const;
  void set_buffer_loader(read_buffer_func_t fn);

  read_version_func_t get_version_loader() const;
  void set_version_loader(read_version_func_t fn);

  config_group_ptr_t get_current_config_group();

  inline void set_override_same_version(bool v) { override_same_version_ = v; }
  inline bool get_override_same_version() const { return override_same_version_; }

  inline void set_group_number(size_t sz) { max_group_number_ = sz; }
  inline size_t get_group_number() const { return max_group_number_; }

  inline void set_on_group_created(on_load_func_t func) { on_group_created_ = func; }
  inline const on_load_func_t& get_n_group_created() const { return on_group_created_; }

  inline void set_on_group_reload_all(on_load_func_t func) { on_group_reload_all_ = func; }
  inline const on_load_func_t& get_on_group_reload_all() const { return on_group_reload_all_; }

  inline void set_on_group_destroyed(on_load_func_t func) { on_group_destroyed_ = func; }
  inline const on_load_func_t& get_on_group_destroyed() const { return on_group_destroyed_; }

  inline void set_on_filter(on_filter_func_t func) { on_filter_ = func; }
  inline const on_filter_func_t& get_on_filter() const { return on_filter_; }

  inline void set_on_not_found(on_not_found_func_t func) { on_not_found_ = func; }
  inline const on_not_found_func_t& get_on_not_found() const { return on_not_found_; }

  template <class INNER_MSG_TYPE, 
    typename std::enable_if<
     std::is_base_of<::google::protobuf::Message, INNER_MSG_TYPE>::value,
    int>::type = 0>
  bool filter(org::xresloader::pb::xresloader_datablocks& outer_msg, const std::string& file_path) const {
    if (!on_filter_) {
      return true;
    }

    return on_filter_(outer_msg, INNER_MSG_TYPE::descriptor(), file_path);
  }

  template <class INNER_MSG_TYPE, 
    typename std::enable_if<
     !std::is_base_of<::google::protobuf::Message, INNER_MSG_TYPE>::value,
    int>::type = 0>
  bool filter(org::xresloader::pb::xresloader_datablocks&, const std::string&) const {
    return true;
  }

  inline void set_on_log(on_log_func_t func) { on_log_ = func; }
  inline const on_log_func_t& get_on_log() const { return on_log_; }

  static void log(const log_caller_info_t &caller,
#ifdef _MSC_VER
    _In_z_ _Printf_format_string_ const char *fmt, ...);
#elif (defined(__clang__) && __clang_major__ >= 3)
    const char *fmt, ...) __attribute__((__format__(__printf__, 2, 3)));
#elif (defined(__GNUC__) && __GNUC__ >= 4)
// 格式检查(成员函数有个隐含的this参数)
#if defined(__MINGW32__) || defined(__MINGW64__)
    const char *fmt, ...) __attribute__((format(__MINGW_PRINTF_FORMAT, 2, 3)));
#else
    const char *fmt, ...) __attribute__((format(printf, 2, 3)));
#endif
#else
    const char *fmt, ...);
#endif

private:
  static bool default_buffer_loader(std::string&, const char* path);
  static bool default_version_loader(std::string&);
  static void default_log_writer(const log_caller_info_t& caller, const char* content);

private:
  static bool is_destroyed_;
  bool override_same_version_;
  size_t max_group_number_;
  on_load_func_t on_group_created_;
  on_load_func_t on_group_reload_all_;
  on_load_func_t on_group_destroyed_;
  on_log_func_t on_log_;
  on_filter_func_t on_filter_;
  on_not_found_func_t on_not_found_;

  read_buffer_func_t read_file_handle_;
  read_version_func_t read_version_handle_;
  mutable ::util::lock::spin_rw_lock handle_lock_;

  std::list<config_group_ptr_t> config_group_list_;
  mutable ::util::lock::spin_rw_lock config_group_lock_;

  std::string log_buffer_;
};
${pb_loader.CppNamespaceEnd(global_package)} // ${global_package}


#ifndef EXCEL_CONFIG_MANAGER_LOGFILENF
#define EXCEL_CONFIG_MANAGER_LOGFILENF(lv, name) ::excel::config_manager::log_caller_info_t(lv, name, __FILE__, __LINE__, __FUNCTION__)
#endif


#define EXCEL_CONFIG_MANAGER_LOGDEBUG(...) ::excel::config_manager::log(EXCEL_CONFIG_MANAGER_LOGFILENF(::excel::config_manager::log_level_t::LOG_LW_DEBUG, "DEBUG"),  __VA_ARGS__)
#define EXCEL_CONFIG_MANAGER_LOGINFO(...) ::excel::config_manager::log(EXCEL_CONFIG_MANAGER_LOGFILENF(::excel::config_manager::log_level_t::LOG_LW_INFO, "INFO"),  __VA_ARGS__)
#define EXCEL_CONFIG_MANAGER_LOGWARNING(...) ::excel::config_manager::log(EXCEL_CONFIG_MANAGER_LOGFILENF(::excel::config_manager::log_level_t::LOG_LW_WARNING, "WARNING"), __VA_ARGS__)
#define EXCEL_CONFIG_MANAGER_LOGERROR(...) ::excel::config_manager::log(EXCEL_CONFIG_MANAGER_LOGFILENF(::excel::config_manager::log_level_t::LOG_LW_ERROR, "ERROR"), __VA_ARGS__)
