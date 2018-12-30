cmake_minimum_required(VERSION 3.12)
project(sfmlFireSim)

set(CMAKE_CXX_STANDARD 14)

# Extend the CMake module path to find the FindSFML.cmake
# file in {project root}/cmake/Modules
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

# Look for SFML >= 2.0, with the specific subcomponents listed below
FIND_PACKAGE(SFML 2 COMPONENTS system window graphics)

# Add include dirs for SFML
# (The SFML_INCLUDE_DIR variable is defined by FindSFML.cmake, if SFML was found)
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})

set(src main.cpp)

add_executable(sfmlFireSim ${src})

target_link_libraries(sfmlFireSim  ${SFML_LIBRARIES})