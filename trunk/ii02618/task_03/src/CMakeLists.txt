# CMakeList.txt: проект CMake для OTIS3; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required(VERSION 3.10...3.26) # Укажите диапазон поддерживаемых версий

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT 
        "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("OTIS3" VERSION 1.0 LANGUAGES CXX)

# Убедитесь, что стандарт C++ установлен
set(CMAKE_CXX_STANDARD 17) # Укажите стандарт C++
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Добавьте источник в исполняемый файл этого проекта.
add_executable(OTIS3 OTIS3.cpp)
