# Python3_EXECUTABLE
# PROJECT_THIRD_PARTY_XRESCODE_GENERATOR_PY
# SRC_LIST
execute_process(
  COMMAND
    "${ATFRAMEWORK_CMAKE_TOOLSET_THIRD_PARTY_PROTOBUF_BIN_PROTOC}" --proto_path
    "${PROJECT_SERVER_FRAME_PROTOCOL_DIR}/config" --proto_path "${PROJECT_THIRD_PARTY_INSTALL_DIR}/include" --proto_path
    "${ATFRAMEWORK_LIBATBUS_REPO_DIR}/include" --proto_path "${ATFRAMEWORK_LIBATAPP_REPO_DIR}/include" --proto_path
    "${PROJECT_THIRD_PARTY_XRESLOADER_PROTO_DIR}" --proto_path
    "${PROJECT_THIRD_PARTY_XRESLOADER_PROTO_DIR}/extensions/v3" --proto_path
    "${PROJECT_THIRD_PARTY_XRESCODE_GENERATOR_REPO_DIR}/pb_extension" -o "${CMAKE_CURRENT_BINARY_DIR}/config-test.pb"
    ${PROTO_DESC_LIST_CONFIG} "${PROJECT_THIRD_PARTY_XRESLOADER_PROTO_DIR}/pb_header_v3.proto"
    "${PROJECT_THIRD_PARTY_XRESLOADER_PROTO_DIR}/extensions/v3/xresloader.proto"
    "${PROJECT_THIRD_PARTY_XRESLOADER_PROTO_DIR}/extensions/v3/xresloader_ue.proto"
    "${PROJECT_THIRD_PARTY_XRESCODE_GENERATOR_REPO_DIR}/pb_extension/xrescode_extensions_v3.proto"
    "${PROJECT_THIRD_PARTY_INSTALL_DIR}/include/google/protobuf/duration.proto"
    "${PROJECT_THIRD_PARTY_INSTALL_DIR}/include/google/protobuf/timestamp.proto"
    "${PROJECT_THIRD_PARTY_INSTALL_DIR}/include/google/protobuf/descriptor.proto"
  RESULT_VARIABLE PROJECT_SERVER_FRAME_CONFIG_SET_RES
  ERROR_VARIABLE PROJECT_SERVER_FRAME_CONFIG_SET_ERR COMMAND_ECHO STDOUT)

if(NOT ${PROJECT_SERVER_FRAME_CONFIG_SET_RES} EQUAL 0)
  message(FATAL_ERROR "${PROJECT_SERVER_FRAME_CONFIG_SET_ERR}")
endif()

execute_process(
  COMMAND
    ${Python3_EXECUTABLE} ${PROJECT_THIRD_PARTY_XRESCODE_GENERATOR_PY} -i "${PROJECT_SOURCE_TEMPLATE_DIR}" -p
    "${CMAKE_CURRENT_BINARY_DIR}/config-test.pb" -o "${CMAKE_CURRENT_LIST_DIR}/config/excel" -g
    "${PROJECT_SOURCE_TEMPLATE_DIR}/config_manager.h.mako" -g "${PROJECT_SOURCE_TEMPLATE_DIR}/config_manager.cpp.mako"
    -l "H:${PROJECT_SOURCE_TEMPLATE_DIR}/config_set.h.mako" -l "S:${PROJECT_SOURCE_TEMPLATE_DIR}/config_set.cpp.mako" -g
    "${PROJECT_SOURCE_TEMPLATE_DIR}/config_easy_api.h.mako" -g "${PROJECT_SOURCE_TEMPLATE_DIR}/config_easy_api.cpp.mako"
    --pb-include-prefix "protocol/config/" --print-output-file
  OUTPUT_VARIABLE PROJECT_SERVER_FRAME_CONFIG_SET_SRC_LIST_STR
  RESULT_VARIABLE PROJECT_SERVER_FRAME_CONFIG_SET_RES
  ERROR_VARIABLE PROJECT_SERVER_FRAME_CONFIG_SET_ERR
  WORKING_DIRECTORY "${PROJECT_SERVER_FRAME_PROTOCOL_DIR}" COMMAND_ECHO STDOUT)

if(NOT ${PROJECT_SERVER_FRAME_CONFIG_SET_RES} EQUAL 0)
  message(FATAL_ERROR "${PROJECT_SERVER_FRAME_CONFIG_SET_ERR}")
endif()
unset(PROJECT_SERVER_FRAME_CONFIG_SET_RES)
unset(PROJECT_SERVER_FRAME_CONFIG_SET_ERR)

unset(PROJECT_SERVER_FRAME_CONFIG_SET_SRC_LIST)
string(REPLACE "\\" "/" PROJECT_SERVER_FRAME_CONFIG_SET_SRC_LIST_STR "${PROJECT_SERVER_FRAME_CONFIG_SET_SRC_LIST_STR}")
string(REGEX MATCHALL "[^\r\n]+" PROJECT_SERVER_FRAME_CONFIG_SET_SRC_LIST
             ${PROJECT_SERVER_FRAME_CONFIG_SET_SRC_LIST_STR})

set(PROJECT_SERVER_FRAME_CONFIG_SET_GENERATED_SRC_DIR "${CMAKE_CURRENT_BINARY_DIR}/_generated/config/excel")
file(MAKE_DIRECTORY "${PROJECT_SERVER_FRAME_CONFIG_SET_GENERATED_SRC_DIR}")
unset(PROJECT_SERVER_FRAME_CONFIG_SET_GENERATED_SRC_LIST)
foreach(SRC_ITEM ${PROJECT_SERVER_FRAME_CONFIG_SET_SRC_LIST})
  get_filename_component(CONFIG_SET_SRC_BASENAME "${SRC_ITEM}" NAME)
  list(APPEND PROJECT_SERVER_FRAME_CONFIG_SET_GENERATED_SRC_LIST
       "${PROJECT_SERVER_FRAME_CONFIG_SET_GENERATED_SRC_DIR}/${CONFIG_SET_SRC_BASENAME}")
endforeach()

add_custom_command(
  OUTPUT ${PROJECT_SERVER_FRAME_CONFIG_SET_SRC_LIST}
  COMMAND
    ${Python3_EXECUTABLE} ${PROJECT_THIRD_PARTY_XRESCODE_GENERATOR_PY} -i "${PROJECT_SOURCE_TEMPLATE_DIR}" -p
    "${PROJECT_INSTALL_RES_PBD_DIR}/config.pb" -o "${PROJECT_SERVER_FRAME_CONFIG_SET_GENERATED_SRC_DIR}" -g
    "${PROJECT_SOURCE_TEMPLATE_DIR}/config_manager.h.mako" -g "${PROJECT_SOURCE_TEMPLATE_DIR}/config_manager.cpp.mako"
    -l "H:${PROJECT_SOURCE_TEMPLATE_DIR}/config_set.h.mako" -l "S:${PROJECT_SOURCE_TEMPLATE_DIR}/config_set.cpp.mako" -g
    "${PROJECT_SOURCE_TEMPLATE_DIR}/config_easy_api.h.mako" -g "${PROJECT_SOURCE_TEMPLATE_DIR}/config_easy_api.cpp.mako"
    -c "custom_config_group:custom_group_fields.h.mako" -c "custom_config_include:custom_include_fields.h.mako"
    --pb-include-prefix "protocol/config/"
  COMMAND "${CMAKE_COMMAND}" -E copy_if_different ${PROJECT_SERVER_FRAME_CONFIG_SET_GENERATED_SRC_LIST}
          "${CMAKE_CURRENT_LIST_DIR}/config/excel"
  WORKING_DIRECTORY "${PROJECT_SERVER_FRAME_PROTOCOL_DIR}"
  DEPENDS "${PROJECT_INSTALL_RES_PBD_DIR}/config.pb"
          "${PROJECT_SOURCE_TEMPLATE_DIR}/config_manager.h.mako"
          "${PROJECT_SOURCE_TEMPLATE_DIR}/config_manager.cpp.mako"
          "${PROJECT_SOURCE_TEMPLATE_DIR}/custom_group_fields.h.mako"
          "${PROJECT_SOURCE_TEMPLATE_DIR}/custom_include_fields.h.mako"
          "${PROJECT_SOURCE_TEMPLATE_DIR}/config_set.h.mako"
          "${PROJECT_SOURCE_TEMPLATE_DIR}/config_set.cpp.mako"
          "${PROJECT_SOURCE_TEMPLATE_DIR}/config_easy_api.h.mako"
          "${PROJECT_SOURCE_TEMPLATE_DIR}/config_easy_api.cpp.mako"
  COMMENT "Generate [@${PROJECT_SERVER_FRAME_PROTOCOL_DIR}] ${PROJECT_SERVER_FRAME_CONFIG_SET_SRC_LIST}")

list(APPEND SRC_LIST ${PROJECT_SERVER_FRAME_CONFIG_SET_SRC_LIST})

add_custom_target(
  config-loader
  DEPENDS ${PROJECT_SERVER_FRAME_CONFIG_SET_SRC_LIST}
  SOURCES ${PROJECT_SERVER_FRAME_CONFIG_SET_SRC_LIST})

unset(PROJECT_SERVER_FRAME_CONFIG_SET_GENERATED_SRC_LIST)
unset(PROJECT_SERVER_FRAME_CONFIG_SET_GENERATED_SRC_DIR)
