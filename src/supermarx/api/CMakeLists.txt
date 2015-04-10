add_library(supermarx-api
			client.cpp)

target_link_libraries(supermarx-api supermarx-downloader supermarx-serialization-msgpack)

include_directories(SYSTEM ${SuperMarx_INCLUDE_DIRS})
