cmake_minimum_required(VERSION 3.25)
project(untitled25)

set(CMAKE_CXX_STANDARD 17)

# Agrega estas líneas
set(SFML_STATIC_LIBRARIES TRUE)  # Si utilizas la versión estática de SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_executable(untitled24 Graph.cpp List.h main.cpp main.cpp)
target_link_libraries(untitled24 sfml-system sfml-window sfml-graphics)