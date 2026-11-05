cmake_minimum_required(VERSION 3.25)
project(nabla-control VERSION 0.0.9 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY  https://github.com/ocornut/imgui.git
    GIT_TAG v1.93.0
    GIT_SHALLOW TRUE
)

FetchContent_Declare(
    rlimgui
    GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
    GIT_TAG main
)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 6.0
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(imgui rlimgui raylib)

add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
)

add_library(rlimgui STATIC
    ${rlimgui_SOURCE_DIR}/rlImGui.cpp
)
target_include_directories(rlimgui PUBLIC ${rlimgui_SOURCE_DIR})
target_link_libraries(rlimgui PUBLIC imgui raylib)

target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})

set (SOURCES
    ../../collectors/DiskCollector.cpp
    ../../collectors/CPUCollector.cpp
    ../../collectors/ProcessCollector.cpp
    ../../collectors/NetworkCollector.cpp
    ../../collectors/TemperatureCollector.cpp
    ../../collectors/MemoryCollector.cpp
    ../../src/main.cpp
)

add_executable(nabla-control ${SOURCES})

target_link_libraries(nabla-control PRIVATE rlimgui)

target_include_directories(nabla-control PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

include(GNUInstallDirs)

install(TARGETS nabla-control 
     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

