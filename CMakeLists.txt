cmake_minimum_required(VERSION 3.0.0)
project(buba VERSION 0.1.0 LANGUAGES CXX)
	
##### Configuration

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/lib)

configure_file(config/README.in ${CMAKE_SOURCE_DIR}/README.md)

##### Source

add_subdirectory(source)

##### Test

#add_subdirectory(test)

##### Documentation

#add_subdirectory(doc)

##### Example

#add_subdirectory(example)
