##### Target

add_executable(poc_libofx
	src/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE inc)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra -Wpedantic -Wold-style-cast -Wshadow)

##### 3rd party

#add_library(sqlite3 STATIC external/sqlite3/sqlite3.c)
#target_include_directories(sqlite3 PUBLIC external/sqlite3)
#target_compile_options(sqlite3 PRIVATE -fPIC)
#
#target_include_directories(${PROJECT_NAME} PUBLIC external/sqlite3)
#target_link_libraries(${PROJECT_NAME} sqlite3)
#
#find_package(Boost 1.58.0 REQUIRED)
#target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})

