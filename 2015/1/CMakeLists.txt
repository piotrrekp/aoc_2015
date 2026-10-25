cmake_minimum_required(VERSION 3.21)
project(AoC2015)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(solution
	src/main.cc)


add_custom_target(
	symlink-compile-commands ALL
	COMMAND ${CMAKE_COMMAND} -E create_symlink
	${CMAKE_BINARY_DIR}/compile_commands.json
	${CMAKE_SOURCE_DIR}/compile_commands.json
)
