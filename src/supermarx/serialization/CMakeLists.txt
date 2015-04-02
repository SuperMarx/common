#FindPackage(SuperMarx COMPONENTS common serialization-msgpack serialization-json serialization-xml)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/contrib/wubwubcmake/modules")

find_package(msgpack REQUIRED)
find_package(tinyxml2 REQUIRED)
find_package(jsoncpp REQUIRED)

add_library(supermarx-serialization
			serializer.cpp
			deserializer.cpp)

add_library(supermarx-serialization-msgpack
			msgpack_serializer.cpp
			msgpack_compact_serializer.cpp
			msgpack_deserializer.cpp)

target_link_libraries(supermarx-serialization-msgpack supermarx-serialization ${msgpack_LIBRARIES})

list(APPEND SuperMarx_INCLUDE_DIRS ${msgpack_INCLUDE_DIRS})	

add_library(supermarx-serialization-xml
			xml_serializer.cpp)

target_link_libraries(supermarx-serialization-xml supermarx-serialization ${tinyxml2_LIBRARIES})

list(APPEND SuperMarx_INCLUDE_DIRS ${tinyxml2_INCLUDE_DIRS})

add_library(supermarx-serialization-json
			json_serializer.cpp)

target_link_libraries(supermarx-serialization-json supermarx-serialization ${jsoncpp_LIBRARIES})

list(APPEND SuperMarx_INCLUDE_DIRS ${jsoncpp_INCLUDE_DIRS})

include_directories(SYSTEM ${SuperMarx_INCLUDE_DIRS})
set(SuperMarx_INCLUDE_DIRS ${SuperMarx_INCLUDE_DIRS} PARENT_SCOPE)
