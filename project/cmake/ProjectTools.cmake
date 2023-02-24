set(LOG_WRAPPER_CATEGORIZE_SIZE
    16
    CACHE STRING "全局日志分类个数限制")
add_compiler_define(LOG_WRAPPER_CATEGORIZE_SIZE=${LOG_WRAPPER_CATEGORIZE_SIZE})

set(PROJECT_INSTALL_EXPORT_NAME "${PROJECT_NAME}-target")
set(PROJECT_INSTALL_EXPORT_FILE
    "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}/${PROJECT_INSTALL_EXPORT_NAME}.cmake")
if(NOT EXISTS "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}")
  file(MAKE_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/${PROJECT_NAME}")
endif()
macro(project_install_and_export_targets)
  foreach(PROJECT_INSTALL_EXPORT_TARGET ${ARGN})
    install(
      TARGETS ${PROJECT_INSTALL_EXPORT_TARGET}
      EXPORT ${PROJECT_INSTALL_EXPORT_NAME}
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
      LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/${SERVER_FRAME_VCS_COMMIT_SHORT_SHA}"
      ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}/${SERVER_FRAME_VCS_COMMIT_SHORT_SHA}")
  endforeach()
  unset(PROJECT_INSTALL_EXPORT_TARGET)
endmacro()

unset(PROJECT_COMMON_PRIVATE_COMPILE_OPTIONS)
unset(PROJECT_COMMON_PRIVATE_LINK_OPTIONS)
if(COMPILER_STRICT_CFLAGS)
  list(APPEND PROJECT_COMMON_PRIVATE_COMPILE_OPTIONS ${COMPILER_STRICT_CFLAGS})
endif()
if(COMPILER_STRICT_EXTRA_CFLAGS)
  list(APPEND PROJECT_COMMON_PRIVATE_COMPILE_OPTIONS ${COMPILER_STRICT_EXTRA_CFLAGS})
endif()
if(COMPILER_STRICT_RECOMMEND_EXTRA_CFLAGS)
  list(APPEND PROJECT_COMMON_PRIVATE_COMPILE_OPTIONS ${COMPILER_STRICT_RECOMMEND_EXTRA_CFLAGS})
endif()
if(MSVC)
  list(REMOVE_ITEM PROJECT_COMMON_PRIVATE_COMPILE_OPTIONS /wd4100 /wd4127)
  list(APPEND PROJECT_COMMON_PRIVATE_COMPILE_OPTIONS /we6001 /we6244 /we6246)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
  list(REMOVE_ITEM PROJECT_COMMON_PRIVATE_COMPILE_OPTIONS -Wunused-but-set-variable)
endif()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  add_compiler_flags_to_inherit_var(CMAKE_CXX_FLAGS "-Wframe-larger-than=131072")
  if(PROJECT_ENABLE_SPLIT_DEBUG_INFORMATION
     AND NOT CMAKE_C_COMPILER_LAUNCHER
     AND NOT CMAKE_CXX_COMPILER_LAUNCHER)
    list(APPEND PROJECT_COMMON_PRIVATE_COMPILE_OPTIONS "$<$<CONFIG:Debug,RelWithDebInfo>:-gsplit-dwarf>")
  endif()
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  if(PROJECT_ENABLE_SPLIT_DEBUG_INFORMATION
     AND NOT CMAKE_C_COMPILER_LAUNCHER
     AND NOT CMAKE_CXX_COMPILER_LAUNCHER)
    list(APPEND PROJECT_COMMON_PRIVATE_COMPILE_OPTIONS "$<$<CONFIG:Debug,RelWithDebInfo>:-gsplit-dwarf=split>")
  endif()
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
  if(PROJECT_ENABLE_SPLIT_DEBUG_INFORMATION
     AND NOT CMAKE_C_COMPILER_LAUNCHER
     AND NOT CMAKE_CXX_COMPILER_LAUNCHER)
    list(APPEND PROJECT_COMMON_PRIVATE_COMPILE_OPTIONS "$<$<CONFIG:Debug,RelWithDebInfo>:-gsplit-dwarf=split>")
  endif()
endif()

if(PROJECT_ENABLE_COMPRESS_DEBUG_INFORMATION AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
  check_cxx_compiler_flag("-gz=zlib" PROJECT_COMPILER_CHECK_DEBUG_GZ_ZLIB)
  if(PROJECT_COMPILER_CHECK_DEBUG_GZ_ZLIB)
    list(APPEND PROJECT_COMMON_PRIVATE_COMPILE_OPTIONS "$<$<CONFIG:Debug,RelWithDebInfo>:-gz=zlib>")
    list(APPEND PROJECT_COMMON_PRIVATE_LINK_OPTIONS "$<$<CONFIG:Debug,RelWithDebInfo>:-gz=zlib>")
  else()
    check_cxx_compiler_flag("-gz" PROJECT_COMPILER_CHECK_DEBUG_GZ)
    if(PROJECT_COMPILER_CHECK_DEBUG_GZ)
      list(APPEND PROJECT_COMMON_PRIVATE_COMPILE_OPTIONS "$<$<CONFIG:Debug,RelWithDebInfo>:-gz>")
      list(APPEND PROJECT_COMMON_PRIVATE_LINK_OPTIONS "$<$<CONFIG:Debug,RelWithDebInfo>:-gz>")
    endif()
  endif()

  # Check if we support --compress-debug-sections=zlib
  if(NOT PROJECT_COMPILER_CHECK_DEBUG_GZ_ZLIB AND NOT PROJECT_COMPILER_CHECK_DEBUG_GZ)
    set(PROJECT_LINKER_CHECK_TEST_BAKCUP_CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_LINK_OPTIONS}")
    list(APPEND CMAKE_REQUIRED_LINK_OPTIONS "-Wl,--compress-debug-sections=zlib")
    check_cxx_source_compiles(
      "#include <iostream>
      int main() {
        std::cout<< __cplusplus<< std::endl;
        return 0;
      }
      "
      PROJECT_LINKER_CHECK_COMPRESS_DEBUG_SECTIONS_ZLIB)
    if(PROJECT_LINKER_CHECK_TEST_BAKCUP_CMAKE_REQUIRED_FLAGS)
      set(CMAKE_REQUIRED_LINK_OPTIONS "${PROJECT_LINKER_CHECK_TEST_BAKCUP_CMAKE_REQUIRED_FLAGS}")
    else()
      unset(CMAKE_REQUIRED_LINK_OPTIONS)
    endif()
    unset(PROJECT_LINKER_CHECK_TEST_BAKCUP_CMAKE_REQUIRED_FLAGS)
    if(PROJECT_LINKER_CHECK_COMPRESS_DEBUG_SECTIONS_ZLIB)
      list(APPEND PROJECT_COMMON_PRIVATE_LINK_OPTIONS "-Wl,--compress-debug-sections=zlib")
    endif()

  endif()
endif()

set(PROJECT_COMMON_PROTOCOL_SOURCE_COMPILE_OPTIONS ${PROJECT_COMMON_PRIVATE_COMPILE_OPTIONS})
if(MSVC)
  list(APPEND PROJECT_COMMON_PROTOCOL_SOURCE_COMPILE_OPTIONS /wd4100 /wd4127)
else()
  list(
    REMOVE_ITEM
    PROJECT_COMMON_PROTOCOL_SOURCE_COMPILE_OPTIONS
    -Wunused-but-set-variable
    -Wshadow
    -Wfloat-equal
    -Wdelete-non-virtual-dtor
    -Wsign-conversion
    -Woverloaded-virtual)
endif()

# Try to use static libs for gcc
if(PROJECT_STATIC_LINK_STANDARD_LIBRARIES AND ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  include(CheckCXXSourceCompiles)
  set(CMAKE_REQUIRED_LIBRARIES ${COMPILER_OPTION_EXTERN_CXX_LIBS})
  unset(PROJECT_LINK_LIBS_TEST_STATIC_LIBGCC CACHE)
  # 测试使用静态libgcc库
  set(CMAKE_REQUIRED_LINK_OPTIONS "-static-libgcc")
  check_cxx_source_compiles("#include<iostream>
    int main() { std::cout<< 1<< std::endl; return 0; }" PROJECT_LINK_LIBS_TEST_STATIC_LIBGCC)
  if(PROJECT_LINK_LIBS_TEST_STATIC_LIBGCC)
    add_linker_flags_for_runtime("-static-libgcc")
    set(PROJECT_LINK_STATIC_LIBS_LIBGCC ON)
    message(STATUS "Using static libgcc")
  else()
    message(STATUS "Using dynamic libgcc")
  endif()
  # 测试使用静态libstdc++库
  set(CMAKE_REQUIRED_LINK_OPTIONS "-static-libstdc++")
  unset(PROJECT_LINK_LIBS_TEST_STATIC_LIBSTDCXX CACHE)
  check_cxx_source_compiles("#include<iostream>
    int main() { std::cout<< 1<< std::endl; return 0; }" PROJECT_LINK_LIBS_TEST_STATIC_LIBSTDCXX)
  if(PROJECT_LINK_LIBS_TEST_STATIC_LIBSTDCXX)
    add_linker_flags_for_runtime("-static-libstdc++")
    set(PROJECT_LINK_STATIC_LIBS_LIBSTDCXX ON)
    message(STATUS "Using static libstdc++")
    list(APPEND COMPILER_OPTION_EXTERN_CXX_LIBS stdc++)
  else()
    message(STATUS "Using dynamic libstdc++")
  endif()

  unset(CMAKE_REQUIRED_LIBRARIES)
  unset(CMAKE_REQUIRED_LINK_OPTIONS)
  unset(PROJECT_LINK_LIBS_TEST_STATIC_LIBGCC CACHE)
  unset(PROJECT_LINK_LIBS_TEST_STATIC_LIBSTDCXX CACHE)
endif()

function(project_link_or_copy_files)
  set(FILE_LIST ${ARGN})
  list(POP_BACK FILE_LIST DESTINATION)
  if(NOT EXISTS "${DESTINATION}")
    file(MAKE_DIRECTORY "${DESTINATION}")
  endif()
  foreach(FILE_PATH IN LISTS FILE_LIST)
    if(IS_SYMLINK "${FILE_PATH}")
      get_filename_component(FILE_BASENAME "${FILE_PATH}" NAME)
      file(READ_SYMLINK "${FILE_PATH}" FILE_REALPATH)
      if(EXISTS "${DESTINATION}/${FILE_BASENAME}")
        file(REMOVE "${DESTINATION}/${FILE_BASENAME}")
      endif()
      file(
        CREATE_LINK "${FILE_REALPATH}" "${DESTINATION}/${FILE_BASENAME}"
        RESULT CREATE_LINK_RESULT
        COPY_ON_ERROR SYMBOLIC)
      if(NOT CREATE_LINK_RESULT EQUAL 0)
        echowithcolor(COLOR GREEN
                      "-- Try to link ${FILE_PATH} to ${DESTINATION}/${FILE_BASENAME} failed: ${CREATE_LINK_RESULT}")
      endif()
    elseif(IS_DIRECTORY "${FILE_PATH}")
      get_filename_component(FILE_BASENAME "${FILE_PATH}" NAME)
      file(
        GLOB FILES_IN_SUBDIRECTORY
        LIST_DIRECTORIES TRUE
        "${FILE_PATH}/*")
      if(FILES_IN_SUBDIRECTORY)
        project_link_or_copy_files(${FILES_IN_SUBDIRECTORY} "${DESTINATION}/${FILE_BASENAME}")
      endif()
    else()
      get_filename_component(FILE_BASENAME "${FILE_PATH}" NAME)
      if(EXISTS "${DESTINATION}/${FILE_BASENAME}")
        file(REMOVE "${DESTINATION}/${FILE_BASENAME}")
      endif()
      file(
        CREATE_LINK "${FILE_PATH}" "${DESTINATION}/${FILE_BASENAME}"
        RESULT CREATE_LINK_RESULT
        COPY_ON_ERROR)
      if(NOT CREATE_LINK_RESULT EQUAL 0)
        echowithcolor(COLOR GREEN
                      "-- Try to link ${FILE_PATH} to ${DESTINATION}/${FILE_BASENAME} failed: ${CREATE_LINK_RESULT}")
      endif()
    endif()
  endforeach()
endfunction()

if(PROJECT_TOOL_ENABLE_SPLIT_DEBUG_SYMBOL_SUFFIX)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    find_program(PROJECT_TOOL_OBJCOPY NAMES objcopy)
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "AppleClang|Clang")
    find_program(PROJECT_TOOL_OBJCOPY NAMES llvm-objcopy)
  endif()
endif()

function(project_tool_split_target_debug_sybmol)
  if(PROJECT_TOOL_ENABLE_SPLIT_DEBUG_SYMBOL_SUFFIX AND PROJECT_TOOL_OBJCOPY)
    foreach(TARGET_NAME ${ARGN})
      add_custom_command(
        TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND "${PROJECT_TOOL_OBJCOPY}" --only-keep-debug "$<TARGET_FILE:${TARGET_NAME}>"
                "$<TARGET_FILE:${TARGET_NAME}>${PROJECT_TOOL_ENABLE_SPLIT_DEBUG_SYMBOL_SUFFIX}"
        COMMAND "${PROJECT_TOOL_OBJCOPY}" --strip-debug --strip-unneeded "$<TARGET_FILE:${TARGET_NAME}>"
        COMMAND
          "${PROJECT_TOOL_OBJCOPY}" --add-gnu-debuglink
          "$<TARGET_FILE_NAME:${TARGET_NAME}>${PROJECT_TOOL_ENABLE_SPLIT_DEBUG_SYMBOL_SUFFIX}"
          "$<TARGET_FILE:${TARGET_NAME}>"
        WORKING_DIRECTORY "$<TARGET_FILE_DIR:${TARGET_NAME}>")
    endforeach()
  endif()
endfunction()
