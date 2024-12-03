cmake_minimum_required(VERSION 3.27)
project(M123)

set(CMAKE_CXX_STANDARD 14)

add_executable(M123 vacuumClean.cpp
        board.cpp
        game.cpp
        helper.cpp
        player.cpp)
