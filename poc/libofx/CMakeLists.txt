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

#message(STATUS "${OFX_FOUND}")
#message(STATUS "${OFX_LIBRARIES}")
#message(STATUS "${OFX_LINK_LIBRARIES}")
#message(STATUS "${OFX_INCLUDE_DIRS}")
#message(STATUS "${OFX_CFLAGS_OTHER}")
#message(STATUS "${OFX_LIBRARIES}")

target_include_directories(${PROJECT_NAME} PRIVATE ${OFX_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE ${OFX_CFLAGS_OTHER})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OFX_LIBRARIES})

#add_library(sqlite3 STATIC external/sqlite3/sqlite3.c)
#target_include_directories(sqlite3 PUBLIC external/sqlite3)
#target_compile_options(sqlite3 PRIVATE -fPIC)
#
#target_include_directories(${PROJECT_NAME} PUBLIC external/sqlite3)
#target_link_libraries(${PROJECT_NAME} sqlite3)
#
#find_package(Boost 1.58.0 REQUIRED)
#target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})

