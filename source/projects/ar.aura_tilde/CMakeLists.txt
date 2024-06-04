cmake_minimum_required(VERSION 3.20)

set(C74_MIN_API_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../min-api)
include(${C74_MIN_API_DIR}/script/min-pretarget.cmake)

include_directories(
        "${C74_INCLUDES}"
        "${CMAKE_CURRENT_LIST_DIR}/../airfx"
)

set(SOURCE_FILES
        ${PROJECT_NAME}.cpp
)

add_library(
        ${PROJECT_NAME}
        MODULE
        ${SOURCE_FILES}
)

# Use the system flag in order to suppress warnings from the external library code
# (in particular, the unused-variable warning for airwindohhs)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/../../airwindohhs/include/"
)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DAIRFX_NO_DOC_GEN=1)
endif ()

include(${C74_MIN_API_DIR}/script/min-posttarget.cmake)
