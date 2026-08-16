cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

set(PRODUCTION_BUILD OFF CACHE BOOL "Make this a production build" FORCE)

if(MSVC)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
add_compile_options(/arch:AVX2)
else()
    add_compile_options(-mavx2 -mfma)
endif()

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build RayLib as static libraries" FORCE)

project(mygame)

add_subdirectory(thirdParty/raylib-6.0)
add_subdirectory(thirdParty/imgui-master)
add_subdirectory(thirdParty/rlImGui-Raylib_6_0)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}")

if(PRODUCTION_BUILD)
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources")
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)

else()
set(CMAKE_BUILD_TYPE Debug)
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)
endif()

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES})
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/platform)
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/gameLayer)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE raylib_static imgui rlimgui)
