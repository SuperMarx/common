cmake_minimum_required(VERSION 2.6)

project(SuperMarx-common)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/contrib/wubwubcmake/modules")

add_subdirectory(src/supermarx)

list(APPEND SuperMarx_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/src/")
set(SuperMarx_INCLUDE_DIRS ${SuperMarx_INCLUDE_DIRS} PARENT_SCOPE)
