cmake_minimum_required(VERSION 3.23)

project(
    plugin
    VERSION 0.0.1
)

add_library(plugin
    ${CMAKE_CURRENT_SOURCE_DIR}/src/plugin.cpp
)

target_include_directories(plugin
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(plugin PRIVATE -Wall -Wextra -Wconversion)