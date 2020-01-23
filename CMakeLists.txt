cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME "EZBench")
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(SOURCES "src/main.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "include")
target_link_libraries(${PROJECT_NAME})