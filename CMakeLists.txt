cmake_minimum_required(VERSION 2.6)

add_subdirectory(contrib/msgpack-c)

# Rapidjson does not require any building, thus add_subdirectory is not necessary
# add_subdirectory(contrib/rapidjson)

project(supermarx-common)
list(APPEND msgpack_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/contrib/msgpack-c/include")
list(APPEND rapidjson_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/contrib/rapidjson/include")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/contrib/wubwubcmake/modules")

include("contrib/wubwubcmake/enable_cpp11.cmake")
include("contrib/wubwubcmake/warning_settings.cmake")
add_sane_warning_flags()

list(APPEND SuperMarx_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/src/")

add_subdirectory(src/supermarx)
add_subdirectory(src/supermarx-tests)

set(SuperMarx_INCLUDE_DIRS ${SuperMarx_INCLUDE_DIRS} PARENT_SCOPE)
