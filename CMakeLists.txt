cmake_minimum_required(VERSION 3.29.1)
project(strypes_challenge VERSION 1.0 DESCRIPTION "Strypes Challenge" LANGUAGES CXX)

add_library(sim)
target_compile_features(sim PUBLIC cxx_std_20)
target_sources(sim
  PUBLIC
    FILE_SET CXX_MODULES FILES
      modules/sim.cpp)

add_library(logger)
target_compile_features(logger PUBLIC cxx_std_20)
target_sources(logger
  PUBLIC
    FILE_SET CXX_MODULES FILES
      modules/logger.cpp)

add_library(input)
target_compile_features(input PUBLIC cxx_std_20)
target_sources(input
  PUBLIC
    FILE_SET CXX_MODULES FILES
      modules/input.cpp)

add_library(renderer)
target_compile_features(renderer PUBLIC cxx_std_20)
target_sources(renderer
  PUBLIC
    FILE_SET CXX_MODULES FILES
      modules/renderer/renderer.cpp
      modules/renderer/renderer_impl.cpp)

add_executable(main main.cpp)
target_compile_features(main PUBLIC cxx_std_20)

target_link_libraries(main PRIVATE sim logger input renderer)
target_link_libraries(renderer PRIVATE sim logger)
target_link_libraries(sim PRIVATE logger)
target_link_libraries(input PRIVATE logger)
