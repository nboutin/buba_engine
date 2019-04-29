##### Configuration

cmake_minimum_required(VERSION 3.0.0)
project(comp_name_unittest_catch)

##### 3rd party

# Prepare "Catch" library for other executables
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE catch)
set(CMAKE_CXX_STANDARD 14)

##### Include

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

##### Source

set(SOURCE
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/test_template.cpp
)

##### Target

add_executable(${PROJECT_NAME} ${SOURCE})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra -Wpedantic -Wold-style-cast -Wshadow)

target_link_libraries(
	${PROJECT_NAME}
	Catch
)

##### install

#install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${OSS_TEST_UNIT_PATH})

