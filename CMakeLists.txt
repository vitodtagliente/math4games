cmake_minimum_required(VERSION 3.2)
project(math4games)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib/)

include_directories( 
    include/ 
)

file(GLOB VENDORS_SOURCES 
	
)
file(GLOB PROJECT_HEADERS 
    include/math4games/*.h
)
file(GLOB PROJECT_SOURCES 
    src/*.cpp
)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_library(
    ${PROJECT_NAME} 
    STATIC
    ${PROJECT_SOURCES} 
    ${PROJECT_HEADERS}
    ${VENDORS_SOURCES}
)

target_link_libraries(
    ${PROJECT_NAME}  
)

export(PACKAGE math4games)