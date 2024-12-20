cmake_minimum_required(VERSION 3.10)

# Укажите название проекта
project(Otis3Lab)

# Укажите стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавьте исполняемый файл
add_executable(otis3laba otis3laba.cpp)