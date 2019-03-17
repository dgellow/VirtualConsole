cmake_minimum_required(VERSION 3.9)
project(VirtualCPU VERSION 0.0.0 LANGUAGES CXX)

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

# —————————————————————————————
# create target for CPU library
# —————————————————————————————
add_library(virtualcpu_lib
	src/CPU.cpp
	src/Machine.cpp
	src/Memory.cpp
	src/Parser.cpp
	src/RAM.cpp
	src/RunFlags.cpp
	src/Screen.cpp
	src/Utils.cpp
)

target_include_directories(virtualcpu_lib
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(virtualcpu_lib PRIVATE cxx_std_17)
target_compile_options(virtualcpu_lib PRIVATE -Werror -Wno-switch)

# ————————————————————————————
# create target for CPU binary
# ————————————————————————————
add_executable(virtualcpu
	apps/virtualcpu-cli/main.cpp
)

target_include_directories(virtualcpu
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(virtualcpu virtualcpu_lib)
target_compile_features(virtualcpu PRIVATE cxx_std_17)
target_compile_options(virtualcpu PRIVATE -Werror)

# ————————————————————————————
# create target for unit tests
# ————————————————————————————
add_executable(virtualcpu_unit_test
	tests/unit/CPU_test.cpp
)

target_link_libraries(virtualcpu_unit_test virtualcpu_lib gtest_main)
target_compile_features(virtualcpu_unit_test PRIVATE cxx_std_17)
target_compile_options(virtualcpu_unit_test PRIVATE -Werror)

enable_testing()
add_test(unit_test virtualcpu_unit_test)

# ——————————————————————————————————
# create target for functional tests
# ——————————————————————————————————
add_executable(virtualcpu_functional_test tests/functional/functional_test.cpp)

target_link_libraries(virtualcpu_functional_test virtualcpu_lib)
target_compile_features(virtualcpu_functional_test PRIVATE cxx_std_17)
target_compile_options(virtualcpu_functional_test PRIVATE -Werror)

enable_testing()
add_test(functional_test virtualcpu_functional_test)
