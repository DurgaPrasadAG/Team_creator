cmake_minimum_required(VERSION 3.19)
project(Team_creator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Team_creator
        RandomUsnPicker.h
        Shuffle.h
        TeamCreator.cpp
        UsnListGenerator.h Shuffle.cpp RandomUsnPicker.cpp UsnListGenerator.cpp)
