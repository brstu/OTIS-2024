cmake_minimum_required(VERSION 3.10)

# Укажите имя вашего проекта
project(GraphProject)

# Укажите стандарт C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавьте исполняемый файл
add_executable(GraphProject main.cpp)