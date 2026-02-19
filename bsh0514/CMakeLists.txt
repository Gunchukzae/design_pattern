cmake_minimum_required(VERSION 3.20)
project(BSH0514 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BSH0514
  src/main.cpp
  src/AbstractFactory/AbstractFactory.h
  src/AbstractFactory/AbstractFactory.cpp
  src/AbstractFactory/FireWorldFactory.h
  src/AbstractFactory/IceWorldFactory.h
)
