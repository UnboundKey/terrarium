cmake_minimum_required(VERSION 3.16)
project(imgui)

add_library(imgui)

file(GLOB SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

target_sources(imgui PRIVATE ${SOURCES})

target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
