cmake_minimum_required(VERSION 3.5)

project(otis_project)

set(SOURCES
    Source.cpp
    ConsoleApp.cpp
)

set(HEADERS
    GraphAlgorithms.h
)

add_executable(otis_project ${SOURCES} ${HEADERS})
