cmake_minimum_required(VERSION 3.10)

project(Template)

## Libreria
# Generacion de binario de libreria .a 
add_library(Logger "${PROJECT_SOURCE_DIR}/src/logger.c")
# Agrego directorios de archivos .h
target_include_directories(Logger PUBLIC "${PROJECT_SOURCE_DIR}/include")


## Test Framework cmocka
# Descargo el framework de cmocka
include(FetchContent)

FetchContent_Declare(
    cmocka
    GIT_REPOSITORY https://git.cryptomilk.org/projects/cmocka.git
    GIT_TAG        cmocka-1.1.5
    GIT_SHALLOW    1
)
# GIT SHALLOW: Indica que solo se descargará la última versión del historial (en lugar de todo el historial completo).

set(WITH_STATIC_LIB ON CACHE BOOL "CMocka: Build with a static library" FORCE) 
set(WITH_CMOCKERY_SUPPORT OFF CACHE BOOL "CMocka: Install a cmockery header" FORCE)
set(WITH_EXAMPLES OFF CACHE BOOL "CMocka: Build examples" FORCE)
set(UNIT_TESTING OFF CACHE BOOL "CMocka: Build with unit testing" FORCE)
set(PICKY_DEVELOPER OFF CACHE BOOL "CMocka: Build with picky developer flags" FORCE)
# FORCE sobreescribe si la variable ya fue definida
# CACHE guarda en la cache de cmack estas opciones para futuras invocaciones

# Descarga y hace disponible cmocka en el proyecto actual (si ya esta descargado solo lo hace disponible)
FetchContent_MakeAvailable(cmocka)


## Testing
# Compilo ejecutable del test
add_executable(test__logger "${PROJECT_SOURCE_DIR}/test/utest/test__logger.c")
target_compile_features(test__logger PRIVATE c_std_99)

# Ejemplo para usar mock cuando se llama a la funcion: logger_other_function -> indica al linker
# que llame a la funcion wrapper en lugar a la original
# target_link_options(test__logger PRIVATE -Wl,--wrap=logger_other_function)

# Linkear el test con cmocka (no linkeo con logger por que incluyo el .c directo en el test)
target_link_libraries(test__logger PRIVATE cmocka-static)

# Añadir directorio de los headers de logger (asi encuentra logger.h)
target_include_directories(test__logger PUBLIC include)

# Habilito ctest -> soporte para pruebas (cmake reconoce estos binarios como pruebas)
enable_testing()

# Agrego los ejecutables de test
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