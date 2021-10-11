# CMakeLists.txt

cmake_minimum_required(VERSION 2.6)
project(marius)

set(CMAKE_CXX_STANDARD 14)

# Bump up warning levels appropriately for clang, gcc & msvc and build in debug mode
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include_directories(src)

file(GLOB_RECURSE marius_SOURCES
	src/*.cpp
	)

add_executable(marius
	${marius_SOURCES}
	)

target_link_libraries(marius
	${SDL2_LIBRARIES}
	SDL2_image
	SDL2_mixer
	)

install(TARGETS marius
	RUNTIME DESTINATION
	bin
	)
