cmake_minimum_required(VERSION 3.12)
project(LWCL VERSION 1.0.0 HOMEPAGE_URL https://github.com/OpenCompileTools/lwcl)

option(LINK_32_BIT "Link the LWCL library for a 32-bit target" OFF)

list(APPEND HEADERS

)

add_library(${PROJECT_NAME} INTERFACE)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "${HEADERS}"
)

if(BUILD_32_BIT)
set_target_properties(${PROJECT_NAME} PROPERTIES
    COMPILE_FLAGS "-m32"
    LINK_FLAGS "-m32"
)
endif()

target_include_directories(${PROJECT_NAME} INTERFACE ./include)
