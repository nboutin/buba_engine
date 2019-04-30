##### Target

add_library(${PROJECT_NAME} SHARED
	src/buba.cpp
	src/database_project.cpp
	src/parser_ofx.cpp
)

target_include_directories(${PROJECT_NAME} 
	PUBLIC interface
	PRIVATE inc)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra -Wpedantic -Wold-style-cast -Wshadow)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR})
	
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)

# Headers
install(
  FILES
  interface/buba.h
  DESTINATION include/${PROJECT_NAME}
  PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)

# Pkgconfig
configure_file(
    ${PROJECT_NAME}.pc.in
    ${PROJECT_NAME}.pc
    @ONLY)

install(
    FILES ${CMAKE_BINARY_DIR}/source/${PROJECT_NAME}.pc
    DESTINATION pkgconfig
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)

##### 3rd party

add_library(sqlite3 STATIC external/sqlite3/sqlite3.c)
target_include_directories(sqlite3 PUBLIC external/sqlite3)
target_compile_options(sqlite3 PRIVATE -fPIC)

target_include_directories(${PROJECT_NAME} PUBLIC external/sqlite3)
target_link_libraries(${PROJECT_NAME} sqlite3)
