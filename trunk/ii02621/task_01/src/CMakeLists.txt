cmake_minimum_required(VERSION 3.10)

# Название проекта
project(ModelingSimulation)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавление исполняемого файла с именем main
add_executable(main main.cpp)