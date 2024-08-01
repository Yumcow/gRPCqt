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

set(SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/proto_reflection_descriptor_database.cpp
)

set(HEADERS
        src/mainwindow.h
        src/proto_reflection_descriptor_database.h
)

# Generate Proto
set(PROTO_DIR "${CMAKE_SOURCE_DIR}/src/proto")
file(GLOB MSG_PROTO ${PROTO_DIR}/*.proto)
set(_gRPC_CPP_PLUGIN_EXECUTABLE "$<TARGET_FILE:gRPC::grpc_cpp_plugin>")
foreach (msg ${MSG_PROTO})
    get_filename_component(FIL_WE ${msg} NAME_WE)

    list(APPEND SOURCES "${PROTO_DIR}/${FIL_WE}.pb.cc")
    list(APPEND SOURCES "${PROTO_DIR}/${FIL_WE}.grpc.pb.cc")
    list(APPEND HEADERS "${PROTO_DIR}/${FIL_WE}.pb.h")
    list(APPEND HEADERS "${PROTO_DIR}/${FIL_WE}.grpc.pb.h")

    add_custom_command(
            OUTPUT "${PROTO_DIR}/${FIL_WE}.pb.cc" "${PROTO_DIR}/${FIL_WE}.pb.h" "${PROTO_DIR}/${FIL_WE}.grpc.pb.cc" "${PROTO_DIR}/${FIL_WE}.grpc.pb.h"
            COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
            ARGS --proto_path=${PROTO_DIR} --cpp_out=${PROTO_DIR} --grpc_out=${PROTO_DIR} --plugin=protoc-gen-grpc=${_gRPC_CPP_PLUGIN_EXECUTABLE} ${msg}
            DEPENDS ${msg}
    )
endforeach ()

add_executable(gRPCqt ${SOURCES} ${HEADERS})

target_link_libraries(gRPCqt
        gRPC::grpc++
        gRPC::grpc++_reflection
        Qt5::Core
        Qt5::Widgets
)

