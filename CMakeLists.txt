cmake_minimum_required(VERSION 3.16)
project(OopProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(OopProject main.cpp Domain.cpp Domain.h Repository.cpp Repository.h Tests.cpp Tests.h Controller.h UI.h)
