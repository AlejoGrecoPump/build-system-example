cmake_minimum_required(VERSION 3.10)

project(Template)

## Libreria
# Generacion de binario de libreria .a 
add_library(Logger "${PROJECT_SOURCE_DIR}/src/logger.c")
# Agrego directorios de archivos .h
target_include_directories(Logger PUBLIC "${PROJECT_SOURCE_DIR}/include")

## Test
include(FetchContent)

FetchContent_Declare(
    cmocka
    GIT_REPOSITORY https://git.cryptomilk.org/projects/cmocka.git
    GIT_TAG        cmocka-1.1.5
    GIT_SHALLOW    1
)

FetchContent_MakeAvailable(cmocka)

# Compilo ejecutable del test
add_executable(test__logger test/utest/test__logger.c)
target_compile_features(test__logger PRIVATE c_std_99)
# Linkear el test con cmocka (no linkeo con logger por que incluyo el .c directo en el test)
target_link_libraries(test__logger PRIVATE cmocka::cmocka)
# Añadir directorio de los headers de la libreria
target_include_directories(test__logger PUBLIC include)

# Habilito ctest -> soporte para pruebas (cmake reconoce estos binarios como pruebas)
enable_testing()
# Agrego los ejecutables de pruebas
add_test(NAME test__logger COMMAND test__logger)    

## Examples
# FLAG de compilacion opcional de ejemplos
option(COMPILE_EXAMPLES "Compiles user examples for Logger library" OFF)

if(COMPILE_EXAMPLES)
    # Genero ejecutable
    add_executable(Example1 "${PROJECT_SOURCE_DIR}/examples/example1.c")
    # Le digo las librerias que nececita para compilar
    target_link_libraries(Example1 PUBLIC Logger)
endif()