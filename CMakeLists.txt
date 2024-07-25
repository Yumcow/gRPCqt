cmake_minimum_required(VERSION 3.28)
project(gRPCqt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(gRPC REQUIRED)
find_package(Qt5 COMPONENTS
        Core
        Widgets
        REQUIRED)

message("")

set(SOURCES
        main.cpp
        mainwindow.cpp
)

set(HEADERS
        mainwindow.h
)

add_executable(gRPCqt ${SOURCES} ${HEADERS})

target_link_libraries(gRPCqt
        gRPC::grpc++
        Qt5::Core
        Qt5::Widgets
)

