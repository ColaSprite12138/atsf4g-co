﻿
# =========== libatapp ==================
set (ATFRAMEWORK_ATAPP_BASE_DIR ${CMAKE_CURRENT_LIST_DIR})
# make 3rd party detect
set (3RD_PARTY_LIBATAPP_BASE_DIR ${ATFRAMEWORK_ATAPP_BASE_DIR})

if (LIBATAPP_ROOT)
    set (ATFRAMEWORK_ATAPP_REPO_DIR ${LIBATAPP_ROOT})
else()
    set (ATFRAMEWORK_ATAPP_REPO_DIR "${CMAKE_CURRENT_LIST_DIR}/repo")
    if(NOT EXISTS ${ATFRAMEWORK_ATAPP_REPO_DIR})
        find_package(Git)
        if(NOT GIT_FOUND)
            message(FATAL_ERROR "git not found")
        endif()

        file(RELATIVE_PATH ATFRAMEWORK_ATAPP_GIT_SUBMODULE_PATH ${CMAKE_SOURCE_DIR} ${ATFRAMEWORK_ATAPP_REPO_DIR})
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init ${ATFRAMEWORK_ATAPP_GIT_SUBMODULE_PATH}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        )
    endif()

    set(LIBATAPP_ROOT ${ATFRAMEWORK_ATAPP_REPO_DIR})
endif()

set (ATFRAMEWORK_ATAPP_INC_DIR "${ATFRAMEWORK_ATAPP_REPO_DIR}/include")
set (ATFRAMEWORK_ATAPP_SRC_DIR "${ATFRAMEWORK_ATAPP_REPO_DIR}/src")
set (ATFRAMEWORK_ATAPP_LINK_NAME atapp)

include_directories(${ATFRAMEWORK_ATAPP_INC_DIR})