# =========== 3rdparty xres-code-generator ==================
set(PROJECT_THIRD_PARTY_XRESCODE_GENERATOR_VERSION "main")
set(PROJECT_THIRD_PARTY_XRESCODE_GENERATOR_REPO_DIR
    "${PROJECT_THIRD_PARTY_PACKAGE_DIR}/xres-code-generator-${PROJECT_THIRD_PARTY_XRESCODE_GENERATOR_VERSION}")
set(PROJECT_THIRD_PARTY_XRESCODE_GENERATOR_PY "${PROJECT_THIRD_PARTY_XRESCODE_GENERATOR_REPO_DIR}/xrescode-gen.py")

if(NOT EXISTS ${PROJECT_THIRD_PARTY_XRESCODE_GENERATOR_PY})
  project_git_clone_repository(
    URL
    "https://github.com/xresloader/xres-code-generator.git"
    REPO_DIRECTORY
    ${PROJECT_THIRD_PARTY_XRESCODE_GENERATOR_REPO_DIR}
    DEPTH
    100
    BRANCH
    ${PROJECT_THIRD_PARTY_XRESCODE_GENERATOR_VERSION}
    WORKING_DIRECTORY
    ${PROJECT_THIRD_PARTY_PACKAGE_DIR}
    CHECK_PATH
    "xrescode-gen.py")
endif()
