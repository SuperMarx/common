find_package(arabica REQUIRED)

add_library(supermarx-scraper
			html_parser.cpp)

target_link_libraries(supermarx-scraper ${arabica_LIBRARIES})
list(APPEND SuperMarx_INCLUDE_DIRS ${arabica_INCLUDE_DIRS})

include_directories(SYSTEM ${SuperMarx_INCLUDE_DIRS})
set(SuperMarx_INCLUDE_DIRS ${SuperMarx_INCLUDE_DIRS} PARENT_SCOPE)
