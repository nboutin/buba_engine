##### Configuration

cmake_minimum_required(VERSION 3.0.0)
project(doc)

##### 3rd party

find_package(Doxygen)

##### Target

if (DOXYGEN_FOUND)
    # note the option ALL which allows to build the docs together with the application
    add_custom_target(${PROJECT_NAME} ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/config.doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
	)
else()
  message("Doxygen need to be installed to generate the doxygen documentation")
endif()
