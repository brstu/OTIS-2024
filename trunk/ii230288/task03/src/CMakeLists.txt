cmake_minimum_required(VERSION 3.10)

# Название проекта
project(lab_03_230288)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Добавление исполняемого файла
add_executable(${PROJECT_NAME} lab3.cpp)