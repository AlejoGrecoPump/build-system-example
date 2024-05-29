cmake_minimum_required(VERSION 3.10)

project(Template)

add_library(Logger "${PROJECT_SOURCE_DIR}/src/logger.c")
target_include_directories(Logger PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_executable(Template main.c)
target_link_libraries(Template PUBLIC Logger)