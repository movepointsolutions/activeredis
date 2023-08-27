cmake_minimum_required(VERSION 3.12)
project(activeredis)

include(FindPkgConfig)
pkg_search_module(HIREDIS REQUIRED hiredis)

add_library(ar_sync
	sync.c++
)
set_property(TARGET ar_sync PROPERTY CXX_STANDARD 17)
target_include_directories(ar_sync PUBLIC ${HIREDIS_INCLUDE_DIRS})
target_link_libraries(ar_sync PUBLIC ${HIREDIS_LINK_LIBRARIES})

add_executable(test_sync
	test_sync.cpp
)
set_property(TARGET test_sync PROPERTY CXX_STANDARD 17)
target_link_libraries(test_sync PUBLIC ar_sync)
