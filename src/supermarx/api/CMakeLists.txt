add_library(supermarx-api
			client.cpp)

find_package(scrypt REQUIRED)

target_link_libraries(supermarx-api
	supermarx-downloader
	supermarx-serialization-msgpack
	${scrypt_LIBRARIES}
	)

include_directories(SYSTEM ${SuperMarx_INCLUDE_DIRS})
