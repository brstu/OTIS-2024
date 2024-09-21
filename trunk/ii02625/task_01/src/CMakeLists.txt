
add_executable (CMake "task_01.cpp" "CMake.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMake PROPERTY CXX_STANDARD 20)
endif()

