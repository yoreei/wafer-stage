cmake_minimum_required(VERSION 3.29.1)
project(strypes_challenge VERSION 1.0 DESCRIPTION "Strypes Challenge" LANGUAGES CXX)

add_library(model.wafer)
target_compile_features(model.wafer PUBLIC cxx_std_20)
target_sources(model.wafer
  PUBLIC
    FILE_SET CXX_MODULES FILES
      modules/wafer/wafer.cpp
      modules/wafer/wafer_impl.cpp)

add_library(logger)
target_compile_features(logger PUBLIC cxx_std_20)
target_sources(logger
  PUBLIC
    FILE_SET CXX_MODULES FILES
      modules/logger.cpp)

add_library(coremem)
target_compile_features(coremem PUBLIC cxx_std_20)
target_sources(coremem
  PUBLIC
    FILE_SET CXX_MODULES FILES
      modules/coremem.cpp)

add_library(renderer)
target_compile_features(renderer PUBLIC cxx_std_20)
target_sources(renderer
  PUBLIC
    FILE_SET CXX_MODULES FILES
      modules/renderer/renderer.cpp
      modules/renderer/renderer_impl.cpp)

add_executable(main main.cpp)
target_compile_features(main PUBLIC cxx_std_20)

target_link_libraries(main PRIVATE model.wafer logger coremem renderer)
target_link_libraries(renderer PRIVATE coremem model.wafer logger)
target_link_libraries(model.wafer PRIVATE coremem logger)
target_link_libraries(coremem PRIVATE logger)
