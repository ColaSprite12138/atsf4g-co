include_guard(GLOBAL)

set(PROJECT_THIRD_PARTY_PYTHON_MODULE_DIR "${PROJECT_THIRD_PARTY_INSTALL_DIR}/.modules")
set(PROJECT_THIRD_PARTY_PYTHON_PIP_SOURCE "-i" "https://mirrors.tencent.com/pypi/simple/")

if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.15")
  cmake_policy(SET CMP0094 NEW)
endif()

find_package(Python3 COMPONENTS Interpreter)

# Patch for python3 binary
if(NOT Python3_Interpreter_FOUND AND UNIX)
  find_program(Python3_EXECUTABLE NAMES python3)
  if(Python3_EXECUTABLE)
    get_filename_component(Python3_BIN_DIR ${Python3_EXECUTABLE} DIRECTORY)
    get_filename_component(Python3_ROOT_DIR ${Python3_BIN_DIR} DIRECTORY CACHE)
    find_package(Python3 COMPONENTS Interpreter)
  endif()
endif()
if(NOT Python3_Interpreter_FOUND)
  message(FATAL_ERROR "Python is required but not found")
endif()

file(TO_CMAKE_PATH
     "${PROJECT_THIRD_PARTY_HOST_INSTALL_DIR}/python.modules/${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}"
     PROJECT_THIRD_PARTY_PYTHON_MODULE_DIR)

if(NOT EXISTS "${PROJECT_THIRD_PARTY_PYTHON_MODULE_DIR}")
  file(MAKE_DIRECTORY "${PROJECT_THIRD_PARTY_PYTHON_MODULE_DIR}")
endif()
message(STATUS "Install dependency python(${Python3_EXECUTABLE}) modules into ${PROJECT_THIRD_PARTY_PYTHON_MODULE_DIR}")

string(TIMESTAMP PROJECT_THIRD_PARTY_PYTHON_ENV_CURRENT_TIMESTAMP "%Y-%m-%d %H:00:00")
if(EXISTS "${PROJECT_THIRD_PARTY_PYTHON_MODULE_DIR}/update-time.txt")
  file(READ "${PROJECT_THIRD_PARTY_PYTHON_MODULE_DIR}/update-time.txt"
       PROJECT_THIRD_PARTY_PYTHON_ENV_PREVIOUS_TIMESTAMP)
  if(PROJECT_THIRD_PARTY_PYTHON_ENV_PREVIOUS_TIMESTAMP STREQUAL PROJECT_THIRD_PARTY_PYTHON_ENV_CURRENT_TIMESTAMP)
    set(PROJECT_THIRD_PARTY_PYTHON_ENV_NEED_UPDATE FALSE)
  else()
    set(PROJECT_THIRD_PARTY_PYTHON_ENV_NEED_UPDATE TRUE)
  endif()
else()
  set(PROJECT_THIRD_PARTY_PYTHON_ENV_NEED_UPDATE TRUE)
endif()

if(PROJECT_THIRD_PARTY_PYTHON_ENV_NEED_UPDATE)
  file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/_deps/python_env/${PROJECT_PREBUILT_PLATFORM_NAME}")
  execute_process(
    COMMAND ${Python3_EXECUTABLE} "-m" "pip" "install" ${PROJECT_THIRD_PARTY_PYTHON_PIP_SOURCE} "--upgrade" "--user"
            "pip" WORKING_DIRECTORY "${PROJECT_THIRD_PARTY_PYTHON_MODULE_DIR}" COMMAND_ECHO STDOUT)

  if(CMAKE_HOST_WIN32)
    set(PROJECT_THIRD_PARTY_PYTHON_MODULE_INSTALL_DIR ".")
  else()
    set(PROJECT_THIRD_PARTY_PYTHON_MODULE_INSTALL_DIR "${PROJECT_THIRD_PARTY_PYTHON_MODULE_DIR}")
  endif()
  execute_process(
    COMMAND
      "${Python3_EXECUTABLE}" "-m" "pip" "install" ${PROJECT_THIRD_PARTY_PYTHON_PIP_SOURCE} "--prefix"
      "${PROJECT_THIRD_PARTY_PYTHON_MODULE_INSTALL_DIR}" "--ignore-installed" "-r"
      "${CMAKE_CURRENT_LIST_DIR}/requirements.txt"
    WORKING_DIRECTORY "${PROJECT_THIRD_PARTY_PYTHON_MODULE_DIR}"
    RESULT_VARIABLE PROJECT_THIRD_PARTY_PYTHON_ENV_UPDATE_RESULT COMMAND_ECHO STDOUT)

  if(PROJECT_THIRD_PARTY_PYTHON_ENV_UPDATE_RESULT EQUAL 0)
    file(WRITE "${PROJECT_THIRD_PARTY_PYTHON_MODULE_DIR}/update-time.txt"
         "${PROJECT_THIRD_PARTY_PYTHON_ENV_CURRENT_TIMESTAMP}")
  endif()
endif()

unset(PROJECT_THIRD_PARTY_PYTHON_ENV_NEED_UPDATE)
