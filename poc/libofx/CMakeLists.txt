##### Configuration

cmake_minimum_required(VERSION 3.0.0)
project(poc_libofx)

##### Target

add_executable(${PROJECT_NAME}
	src/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE inc)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra -Wpedantic -Wold-style-cast -Wshadow)

##### 3rd party

find_package(PkgConfig REQUIRED)

pkg_check_modules(OFX REQUIRED libofx>=0.9.12)

target_include_directories(${PROJECT_NAME} PRIVATE ${OFX_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE ${OFX_CFLAGS_OTHER})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OFX_LIBRARIES})
