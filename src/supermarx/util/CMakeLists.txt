find_package(CURL REQUIRED)
include_directories(SYSTEM ${CURL_INCLUDE_DIRS})

add_library(supermarx-downloader
			downloader.cpp)

target_link_libraries(supermarx-downloader ${CURL_LIBRARIES})

include_directories(SYSTEM ${SuperMarx_INCLUDE_DIRS})
