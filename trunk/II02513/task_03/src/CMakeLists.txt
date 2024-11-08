# CMakeList.txt: проект CMake для OTIS3; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
project ("OTIS3")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (OTIS3 OTIS3.cpp)
