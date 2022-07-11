cmake_minimum_required(VERSION 3.23)

project(
    sdk
    VERSION 0.0.1
)

if(UNIX AND NOT APPLE)
    set(SDK_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/plugin_linux.cpp
    )
endif()

add_library(sdk ${SDK_SRC})

target_link_libraries(sdk PUBLIC EnTT::EnTT)

target_include_directories(sdk
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(sdk INTERFACE -Wall -Wextra -Wconversion)