cmake_minimum_required(VERSION 3.16)
project(Module27_opp2_task_2)

set(CMAKE_CXX_STANDARD 11)

option(ENABLE_TESTING "Enable test emulation" OFF)

add_executable(Module27_opp2_task_2)

target_sources(Module27_opp2_task_2
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        )

target_include_directories(Module27_opp2_task_2
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

target_compile_definitions(Module27_opp2_task_2
        PRIVATE
        _USE_MATH_DEFINES
        ENABLE_TESTING=$<BOOL:${ENABLE_TESTING}>
        )

