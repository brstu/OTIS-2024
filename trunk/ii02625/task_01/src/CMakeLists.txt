cmake_minimum_required (VERSION 3.0.0)

project (lab_01_ii02625)
add_executable ( ${PROJECT_NAME} task_01.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMake PROPERTY CXX_STANDARD 20)
endif()

