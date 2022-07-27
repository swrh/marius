# CMakeLists.txt

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(marius)

set(CMAKE_CXX_STANDARD 14)

# Bump up warning levels appropriately for clang, gcc & msvc and build in debug mode
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()

find_package(PkgConfig REQUIRED)

find_package(Boost 1.71.0 REQUIRED COMPONENTS
	log
	program_options
	stacktrace_backtrace
	)

pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED IMPORTED_TARGET sdl2_image)

file(GLOB_RECURSE marius_SOURCES
	include/*.hpp
	src/*.cpp
	)

file(COPY assets DESTINATION .)

add_executable(marius
	${marius_SOURCES}
	)

target_compile_definitions(marius
	PRIVATE
		BOOST_STACKTRACE_USE_BACKTRACE
	)

target_link_libraries(marius
	PUBLIC
		PkgConfig::SDL2
		PkgConfig::SDL2_IMAGE
		Boost::log
		Boost::program_options
		Boost::stacktrace_backtrace
		dl
	)

target_include_directories(marius
	PRIVATE
		${SDL2_INCLUDE_DIRS}
	PUBLIC
		include
	)

install(TARGETS marius
	RUNTIME DESTINATION bin
	)
