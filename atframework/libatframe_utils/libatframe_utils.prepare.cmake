﻿if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.10")
    include_guard(GLOBAL)
endif()

if(NOT ATFRAMEWORK_ATFRAME_UTILS_BASE_DIR)
    set (ATFRAMEWORK_ATFRAME_UTILS_BASE_DIR ${CMAKE_CURRENT_LIST_DIR})
endif()

# =========== 3rdparty atframe_utils ==================
if (ATFRAME_UTILS_ROOT)
    set (ATFRAMEWORK_ATFRAME_UTILS_REPO_DIR ${ATFRAME_UTILS_ROOT})
else()
    set (ATFRAMEWORK_ATFRAME_UTILS_REPO_DIR "${ATFRAMEWORK_ATFRAME_UTILS_BASE_DIR}/repo")
    set (ATFRAME_UTILS_ROOT ${ATFRAMEWORK_ATFRAME_UTILS_REPO_DIR})
    find_package(Git)
    if(NOT EXISTS ${ATFRAMEWORK_ATFRAME_UTILS_REPO_DIR})
        execute_process(COMMAND ${GIT_EXECUTABLE} config "remote.origin.url"
            OUTPUT_VARIABLE PROJECT_GIT_REMOTE_ORIGIN_URL
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        string(REGEX MATCH "^http(s?):" PROJECT_GIT_REMOTE_ORIGIN_USE_SSH "${PROJECT_GIT_REMOTE_ORIGIN_URL}")
        if (PROJECT_GIT_REMOTE_ORIGIN_USE_SSH)
            execute_process(COMMAND ${GIT_EXECUTABLE} clone --depth=100 -b master "git@github.com:atframework/atframe_utils.git" ${ATFRAMEWORK_ATFRAME_UTILS_REPO_DIR}
                WORKING_DIRECTORY ${ATFRAMEWORK_ATFRAME_UTILS_BASE_DIR}
            )
        else ()
            execute_process(COMMAND ${GIT_EXECUTABLE} clone --depth=100 -b master "https://github.com/atframework/atframe_utils.git" ${ATFRAMEWORK_ATFRAME_UTILS_REPO_DIR}
                WORKING_DIRECTORY ${ATFRAMEWORK_ATFRAME_UTILS_BASE_DIR}
            )
        endif()
    elseif(PROJECT_RESET_DENPEND_REPOSITORIES)
        execute_process(
            COMMAND ${GIT_EXECUTABLE} fetch -f --depth=100 origin
            COMMAND ${GIT_EXECUTABLE} reset --hard origin/master
            WORKING_DIRECTORY ${ATFRAMEWORK_ATFRAME_UTILS_REPO_DIR}
        )
    endif()
endif()

set (ATFRAMEWORK_ATFRAME_UTILS_INC_DIR "${ATFRAMEWORK_ATFRAME_UTILS_REPO_DIR}/include")
set (ATFRAMEWORK_ATFRAME_UTILS_SRC_DIR "${ATFRAMEWORK_ATFRAME_UTILS_REPO_DIR}/src")
set (ATFRAMEWORK_ATFRAME_UTILS_LINK_NAME atframe_utils)

set (3RD_PARTY_ATFRAME_UTILS_BASE_DIR ${ATFRAMEWORK_ATFRAME_UTILS_BASE_DIR})
set (3RD_PARTY_ATFRAME_UTILS_PKG_DIR ${ATFRAMEWORK_ATFRAME_UTILS_REPO_DIR})
set (3RD_PARTY_ATFRAME_UTILS_INC_DIR ${ATFRAMEWORK_ATFRAME_UTILS_INC_DIR})
set (3RD_PARTY_ATFRAME_UTILS_SRC_DIR ${ATFRAMEWORK_ATFRAME_UTILS_SRC_DIR})
set (3RD_PARTY_ATFRAME_UTILS_LINK_NAME ${ATFRAMEWORK_ATFRAME_UTILS_LINK_NAME})
