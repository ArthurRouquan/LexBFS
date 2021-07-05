cmake_minimum_required(VERSION 3.20.3)

project(lexbfs)
add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)