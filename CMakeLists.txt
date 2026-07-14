cmake_minimum_required(VERSION 3.25)

set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "macOS architecture")

option(EXPORT_COMPILE_COMMANDS "Export compile commands for LSP" ON)
if (EXPORT_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif ()

include(FetchContent)

message(STATUS "Fetching max-sdk-base")
FetchContent_Declare(
    max-sdk-base
    GIT_REPOSITORY https://github.com/Cycling74/max-sdk-base.git
    GIT_TAG main
)
FetchContent_MakeAvailable(max-sdk-base)

if (NOT DEFINED MAX_SDK_PACKAGE_OUT_OF_TREE)
    set(MAX_SDK_PACKAGE_OUT_OF_TREE ON)
endif ()

project(Airfx)

# max-sdk-base's Once.cmake (run as a CMAKE_PROJECT_TOP_LEVEL_INCLUDES hook
# during the project() call above) already staged README.md into the
# build-tree package. Overwrite it with the public-facing README instead.
file(COPY_FILE "${CMAKE_SOURCE_DIR}/README-public.md" "${CMAKE_BINARY_DIR}/package/README.md")

# Package version comes from the latest "v*" git tag (stripped of its "v"),
# so a release build's package-info.json always matches the tag it ships as.
# Falls back to 0.0.0 for untagged dev builds.
set(PACKAGE_VERSION "0.0.0")
find_package(Git QUIET)
if (GIT_FOUND)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --tags --match "v*" --abbrev=0
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        OUTPUT_VARIABLE _airfx_git_tag
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
        RESULT_VARIABLE _airfx_git_describe_result
    )
    if (_airfx_git_describe_result EQUAL 0 AND _airfx_git_tag)
        string(REGEX REPLACE "^v" "" PACKAGE_VERSION "${_airfx_git_tag}")
    endif ()
endif ()
message(STATUS "Package version: ${PACKAGE_VERSION}")
configure_file(
    "${CMAKE_SOURCE_DIR}/package-info.json.in"
    "${CMAKE_BINARY_DIR}/package/package-info.json"
    @ONLY
)

set(AUTHOR_DOMAIN "com.isabelgk.max")

# TODO: Fetch isabelgk/airwindohhs

# add_subdirectory(source/...)
