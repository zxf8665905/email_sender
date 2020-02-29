project(email)
cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++11)

include_directories(
	deps/curl-7.60.0/include
)

link_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/deps/curl-7.60.0/bin
)

set(SRC 
	src/sender.h
	src/sender.cpp
	src/config.h
	src/config.cpp
	src/main.cpp
)

add_executable(email ${SRC})
target_link_libraries(email 
	curl
)
