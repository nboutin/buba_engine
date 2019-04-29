##### Target

add_library(${PROJECT_NAME} SHARED
	src/template.cpp)

target_include_directories(${PROJECT_NAME} 
	PUBLIC interface
	PRIVATE inc)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra -Wpedantic -Wold-style-cast -Wshadow)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR})
	
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION usr/lib)

# Headers
install(
  FILES
  interface/interface_template.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
  PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)

# Pkgconfig
configure_file(
    ${PROJECT_NAME}.pc.in
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${PROJECT_NAME}.pc
    @ONLY)

install(
    FILES ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${PROJECT_NAME}.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ)

##### 3rd party

#find_package(PkgConfig REQUIRED)
#pkg_check_modules(MODULE_EXT REQUIRED sqlite3)
#
#target_include_directories(${PROJECT_NAME} PRIVATE ${MODULE_EXT_INCLUDE_DIRS})
#target_compile_options(${PROJECT_NAME} PRIVATE ${MODULE_EXT_CFLAGS_OTHER})
#target_link_libraries(${PROJECT_NAME} PRIVATE ${MODULE_EXT_LIBRARIES})
