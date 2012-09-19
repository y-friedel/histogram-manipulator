cmake_minimum_required(VERSION 2.8)

project(MMTI)

set(EXECUTABLE_OUTPUT_PATH bin)

add_definitions(-Wall -g -DPATH_DATA=\"data/\")

include_directories(src)

file(
	GLOB_RECURSE
	mmti_sources
	./src/*.cpp
	
)

add_executable(projet ${mmti_sources})	

