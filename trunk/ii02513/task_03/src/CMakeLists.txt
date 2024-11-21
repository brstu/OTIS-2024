cmake_minimum_required (VERSION 3.0.0)

# Enable Hot Reload for MSVC compilers if supported.
project ("OTIS3_2513")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (${PROJECT_NAME} OTIS3.cpp)
