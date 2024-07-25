cmake_minimum_required(VERSION 3.28)
project(gRPCqt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        REQUIRED)

add_executable(gRPCqt main.cpp)
target_link_libraries(gRPCqt
        Qt5::Core
)

