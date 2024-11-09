# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(SocketProgrammingProject VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
file(GLOB SOURCES "src/*.cpp")

add_executable(server src/server.cpp)
add_executable(client src/client.cpp)

# Link the Winsock library on Windows
if(WIN32)
    target_link_libraries(server ws2_32)
    target_link_libraries(server ws2_32)
endif()

