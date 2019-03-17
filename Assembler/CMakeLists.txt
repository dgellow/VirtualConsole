cmake_minimum_required(VERSION 3.9)
project(VirtualAssembler VERSION 0.0.0 LANGUAGES CXX)

# ————————————————————————————————————
# download and build test dependencies
# ————————————————————————————————————
configure_file(
	${CMAKE_HOME_DIRECTORY}/../cmake/TestsDependencies.cmake.in
	googletest-download/CMakeLists.txt
)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
	RESULT_VARIABLE result
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download
)
if (result)
	message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download
)
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

add_subdirectory(
	${CMAKE_CURRENT_BINARY_DIR}/googletest-src
	${CMAKE_CURRENT_BINARY_DIR}/googletest-build
	EXCLUDE_FROM_ALL
)

# ———————————————————————————————————
# create target for assembler library
# ———————————————————————————————————
add_library(virtualassembler_lib
	src/Compiler.cpp
	src/Lexer.cpp
	src/Parser.cpp
)

target_include_directories(virtualassembler_lib
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(virtualassembler_lib PRIVATE cxx_std_17)
target_compile_options(virtualassembler_lib PRIVATE -Werror)

# ——————————————————————————————————
# create target for assembler binary
# ——————————————————————————————————
add_executable(virtualassembler
	apps/virtualassembler-cli/main.cpp
)

target_include_directories(virtualassembler
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(virtualassembler virtualassembler_lib)
target_compile_features(virtualassembler PRIVATE cxx_std_17)
target_compile_options(virtualassembler PRIVATE -Werror)
