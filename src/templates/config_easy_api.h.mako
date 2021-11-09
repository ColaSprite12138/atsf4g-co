## -*- coding: utf-8 -*-
<%!
import time
%><%namespace name="pb_loader" module="pb_loader"/>
// Copyright ${time.strftime("%Y")} xresloader. All rights reserved.
// Generated by xres-code-generator, please don't edit it
//
#pragma once

#include "config/excel/config_manager.h"

${pb_loader.CppNamespaceBegin(global_package)}
% for pb_msg in pb_set.generate_message:
%   for loader in pb_msg.loaders:
// ======================================== ${loader.code.class_name} ========================================
%     for code_index in loader.code.indexes:
const ${pb_loader.CppFullPath(global_package)}${loader.get_cpp_class_full_name()}::${code_index.name}_container_type&
  get_${loader.code.class_name}_all_of_${code_index.name}();
%       if code_index.is_list():
const ${pb_loader.CppFullPath(global_package)}${loader.get_cpp_class_full_name()}::${code_index.name}_value_type*
  get_${loader.code.class_name}_by_${code_index.name}(${code_index.get_key_decl()});
${pb_loader.CppFullPath(global_package)}${loader.get_cpp_class_full_name()}::item_ptr_type
  get_${loader.code.class_name}_by_${code_index.name}(${code_index.get_key_decl()}, size_t idx);
%       else:
${pb_loader.CppFullPath(global_package)}${loader.get_cpp_class_full_name()}::${code_index.name}_value_type
  get_${loader.code.class_name}_by_${code_index.name}(${code_index.get_key_decl()});
%       endif
%     endfor
%   endfor
% endfor
${pb_loader.CppNamespaceEnd(global_package)} // ${global_package}
