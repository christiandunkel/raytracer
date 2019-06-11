cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
cmake_policy(VERSION 2.8)

set(FRAMEWORK_NAME framework)

project(raytracer)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX14)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

if(CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)
  message(FATAL_ERROR "Source and binary directories must be different")
endif(CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_CURRENT_BINARY_DIR)

find_package(OpenGL REQUIRED)

# Add externals
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external)
add_definitions(-DGLEW_STATIC)

# build GLFW
set(GLFW_DIRECTORY glfw-3.2.1)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLFW_DIRECTORY}/include)

set(GLFW_INSTALL OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE STRING "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLFW_DIRECTORY})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLFW_DIRECTORY}/include)

set(NANOVG_DIRECTORY nanovg)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${NANOVG_DIRECTORY}/src)

add_library(nanovg STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/external/${NANOVG_DIRECTORY}/src/nanovg.c
)

# Quench warnings while compiling NanoVG
if (CMAKE_COMPILER_IS_GNUCC)
  set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/external/${NANOVG_DIRECTORY}/src/nanovg.c PROPERTIES COMPILE_FLAGS -Wno-unused-result)
elseif(MSVC)
  set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/external/${NANOVG_DIRECTORY}/src/nanovg.c PROPERTIES COMPILE_FLAGS "/wd4005 /wd4456 /wd4457")
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/external/${NANOVG_DIRECTORY}/example/Roboto-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/external/${NANOVG_DIRECTORY}/example/Roboto-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/source/)

# Use catch for testing
set(CATCH_DIRECTORY catch-1.5)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${CATCH_DIRECTORY})

set(GLM_DIRECTORY glm-0.9.5.3)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLM_DIRECTORY})

################################
# Add libraries to executables

set(LIBRARIES glfw ${GLFW_LIBRARIES})

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(MSVC)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/framework)
add_subdirectory(framework)

add_subdirectory(source)
