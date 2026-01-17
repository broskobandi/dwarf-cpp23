cmake_minimum_required(VERSION 3.30)

if (WIN)
	set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-clang++)
	set(SDL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SDL2-2.32.8/x86_64-w64-mingw32)
else()
	set(CMAKE_CXX_COMPILER clang++)
endif()
message("COMPILER = ${CMAKE_CXX_COMPILER}")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(STD_DIR /usr/lib/llvm/21/share/libc++/v1)
file(GLOB SRC src/*.cpp)
file(GLOB MOD src/*.cppm ${STD_DIR}/std.cppm)

project(dwarf CXX)

add_executable(${PROJECT_NAME} ${SRC})
if (WIN)
	target_link_directories(${PROJECT_NAME} PRIVATE ${SDL_DIR}/lib)
	target_include_directories(${PROJECT_NAME} PRIVATE ${SDL_DIR}/include)
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/libs
		${CMAKE_CURRENT_BINARY_DIR}
	)
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wunused-result -Wconversion)
target_sources(${PROJECT_NAME} PRIVATE FILE_SET modules TYPE CXX_MODULES
	BASE_DIRS ${STD_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
	FILES ${MOD}
)
