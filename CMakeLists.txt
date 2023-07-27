########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 3.0)
project(LEO VERSION 1.0)

set(CMAKE_GENERATOR MinGW Makefiles)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)

message( STATUS "CMAKE_SYSTEM: " ${CMAKE_SYSTEM} )
message( STATUS "CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR} )
message( STATUS "CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER} )

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(DEPENDENCIES_DIR ${PROJECT_SOURCE_DIR}/dependencies)
set(DEPENDENCIES_INCLUDE_DIR ${DEPENDENCIES_DIR}/include)
set(DLL_DIR ${PROJECT_SOURCE_DIR}/libs)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# stk-debug
set(STK_DEBUG_LIB ${DEPENDENCIES_DIR}/stk/Debug/AgConnect.lib)
set(STK_DEBUG_DLL ${DLL_DIR}/Debug/AgConnect.dll)
include_directories(${STK_DEBUG_INCLUDE_DIR})

# include
include_directories(${DEPENDENCIES_INCLUDE_DIR})

# src
add_subdirectory(${SOURCE_DIR})
aux_source_directory(${SOURCE_DIR} SRC_LIST)
add_executable(LEO ${SRC_LIST})

# link
target_link_libraries(LEO ${STK_DEBUG_LIB})
target_link_libraries(LEO ${STK_DEBUG_DLL})
target_link_libraries(LEO demo)