cmake_minimum_required(VERSION 3.10)

project(Template)

# Generacion de binario de libreria .a 
add_library(Logger "${PROJECT_SOURCE_DIR}/src/logger.c")
# Agrego directorios de archivos .h
target_include_directories(Logger PUBLIC "${PROJECT_SOURCE_DIR}/include")

# FLAG de compilacion opcional de ejemplos
option(COMPILE_EXAMPLES "Compiles user examples for Logger library" OFF)

if(COMPILE_EXAMPLES)
    # Genero ejecutable
    add_executable(Example1 "${PROJECT_SOURCE_DIR}/examples/example1.c")
    # Le digo las librerias que nececita para compilar
    target_link_libraries(Example1 PUBLIC Logger)
endif()