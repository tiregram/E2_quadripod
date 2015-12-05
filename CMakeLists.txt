cmake_minimum_required(VERSION 2.6)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../E3AF/cmake")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -g")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

project(prg)

include(FindCurses)

set(CURSES_USE_NCURSES  TRUE)

find_package(Curses)
find_package( OpenCV REQUIRED )

file (
	GLOB_RECURSE
	source_files
	src/*
	)

add_executable(
	prg	
	${source_files}
	)

add_definitions(-std=c++11)

target_link_libraries(prg ${OpenCV_LIBS} )
target_link_libraries(prg ${CURSES_LIBRARIES})
