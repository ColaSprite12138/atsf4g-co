﻿
# =========== libatbus ==================
set (ATFRAMEWORK_ATBUS_BASE_DIR ${CMAKE_CURRENT_LIST_DIR})
# make 3rd party detect
set (3RD_PARTY_LIBATBUS_BASE_DIR ${ATFRAMEWORK_ATBUS_BASE_DIR})

if (LIBATBUS_ROOT)
    set (ATFRAMEWORK_ATBUS_REPO_DIR ${LIBATBUS_ROOT})
else()
    set (ATFRAMEWORK_ATBUS_REPO_DIR "${CMAKE_CURRENT_LIST_DIR}/repo")
    if(NOT EXISTS ${ATFRAMEWORK_ATBUS_REPO_DIR})
        find_package(Git)
        if(NOT GIT_FOUND)
            message(FATAL_ERROR "git not found")
        endif()

        file(RELATIVE_PATH ATFRAMEWORK_ATBUS_GIT_SUBMODULE_PATH ${CMAKE_SOURCE_DIR} ${ATFRAMEWORK_ATBUS_REPO_DIR})
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init ${ATFRAMEWORK_ATBUS_GIT_SUBMODULE_PATH}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        )
    endif()
endif()

set (ATFRAMEWORK_ATBUS_INC_DIR "${ATFRAMEWORK_ATBUS_REPO_DIR}/include")
set (ATFRAMEWORK_ATBUS_SRC_DIR "${ATFRAMEWORK_ATBUS_REPO_DIR}/src")
set (ATFRAMEWORK_ATBUS_LINK_NAME atbus)

include_directories(${ATFRAMEWORK_ATBUS_INC_DIR})