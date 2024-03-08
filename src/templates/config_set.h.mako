﻿## -*- coding: utf-8 -*-
<%!
import time
%><%
cpp_include_prefix = pb_set.get_custom_variable("cpp_include_prefix", "config/excel/")
xresloader_include_prefix = pb_set.get_custom_variable("xresloader_include_prefix", pb_set.pb_include_prefix)
%><%namespace name="pb_loader" module="pb_loader"/>
// Copyright ${time.strftime("%Y")} xresloader. All rights reserved.
// Generated by xres-code-generator, please don't edit it
//

#pragma once

#include <stdint.h>
#include <cstddef>
#include <functional>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <unordered_map>
#include <memory>
#include <cstring>

#include "lock/spin_rw_lock.h"

// clang-format off
#include "config/compiler/protobuf_prefix.h"
// clang-format on

#include "${pb_set.pb_include_prefix}${loader.get_pb_header_path()}"
#include "${xresloader_include_prefix}pb_header_v3.pb.h"

// clang-format off
#include "config/compiler/protobuf_suffix.h"
// clang-format on

% for block_file in pb_set.get_custom_blocks("custom_config_include"):
// include custom_config_include: ${block_file}
<%include file="${block_file}" />
% endfor

#include "${cpp_include_prefix}config_traits.h"

#ifndef EXCEL_CONFIG_LOADER_API
#  define EXCEL_CONFIG_LOADER_API
#endif

${pb_loader.CppNamespaceBegin(global_package)}

#ifndef EXCEL_CONFIG_LOADER_TRAITS
#  define EXCEL_CONFIG_LOADER_TRAITS
using excel_config_type_traits = ::excel::traits::config_traits<::excel::traits::type_guard>;
#endif

${loader.get_cpp_namespace_decl_begin()}

class ${loader.get_cpp_class_name()} {
 public:
  using item_type = const ${loader.get_pb_inner_class_name()};
  using proto_type = ${loader.get_pb_inner_class_name()};
  using item_ptr_type = excel_config_type_traits::shared_ptr<item_type>;

 public:
  EXCEL_CONFIG_LOADER_API ${loader.get_cpp_class_name()}();
  EXCEL_CONFIG_LOADER_API ~${loader.get_cpp_class_name()}();

  EXCEL_CONFIG_LOADER_API int on_inited(bool enable_multithread_lock);

  EXCEL_CONFIG_LOADER_API int load_all();

  EXCEL_CONFIG_LOADER_API void clear();

  EXCEL_CONFIG_LOADER_API const std::list<org::xresloader::pb::xresloader_data_source>& get_data_source() const;

  EXCEL_CONFIG_LOADER_API std::size_t get_data_hash_code_verison() const noexcept;

  EXCEL_CONFIG_LOADER_API const std::vector<item_ptr_type>& get_all_data() const noexcept;

 private:
  int load_file(const std::string& file_path);
  int load_list(const char*);
  int reload_file_lists();
  void merge_data(item_ptr_type);

 private:
  ::util::lock::spin_rw_lock           load_file_lock_;
  std::unordered_map<std::string, bool> file_status_; // true: already loaded
  std::list<org::xresloader::pb::xresloader_data_source> datasource_;

  bool all_loaded_;
  bool enable_multithread_lock_;
  std::size_t hash_code_verison_;
  std::vector<item_ptr_type> all_data_;

% for code_index in loader.code.indexes:
  // ------------------------- index: ${code_index.name} -------------------------
 public:
% if code_index.is_list():
  using ${code_index.name}_value_type = excel_config_type_traits::shared_ptr<const std::vector<item_ptr_type> >;
  EXCEL_CONFIG_LOADER_API ${code_index.name}_value_type
    get_list_by_${code_index.name}(${code_index.get_key_decl()});
  EXCEL_CONFIG_LOADER_API item_ptr_type get_by_${code_index.name}(${code_index.get_key_decl()}, size_t index);
private:
  ${code_index.name}_value_type _get_list_by_${code_index.name}(${code_index.get_key_decl()});
public:
% else:
  using ${code_index.name}_value_type = item_ptr_type;
  EXCEL_CONFIG_LOADER_API ${code_index.name}_value_type get_by_${code_index.name}(${code_index.get_key_decl()});
% endif
% if code_index.is_vector():
  using ${code_index.name}_container_type = excel_config_type_traits::shared_ptr<const std::vector<${code_index.name}_value_type> >;
% else:
  using ${code_index.name}_container_type = excel_config_type_traits::map_type<
    std::tuple<${code_index.get_key_type_list()}>,
    ${code_index.name}_value_type>;
% endif
  EXCEL_CONFIG_LOADER_API const ${code_index.name}_container_type& get_all_of_${code_index.name}() const;

 private:
% if code_index.is_vector():
  ${code_index.name}_container_type ${code_index.name}_data_;
% else:
  ${code_index.name}_container_type ${code_index.name}_data_;
% endif

% endfor
};

${loader.get_cpp_namespace_decl_end()}
${pb_loader.CppNamespaceEnd(global_package)} // ${global_package}
