# Copyright (c) 2024 Pyarelal Knowles, MIT License

cmake_minimum_required(VERSION 3.20)

project(indirect_view)

set(CMAKE_CXX_STANDARD 20)

add_library(indirect_view INTERFACE)
target_include_directories(indirect_view INTERFACE include)

if(BUILD_TESTING)
  option(BUILD_INDIRECT_VIEW_TESTING "Enable indirect view testing" ON)
  if(BUILD_INDIRECT_VIEW_TESTING)
    enable_testing()
    add_subdirectory(test)
  endif()
endif()
