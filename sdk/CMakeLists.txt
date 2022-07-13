cmake_minimum_required(VERSION 3.20)

project(
    sdk
    VERSION 0.0.1
)

set(SDK_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/windows/plugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/linux/plugin.cpp
)

add_library(sdk ${SDK_SRC})

target_link_libraries(sdk
    PUBLIC 
        EnTT::EnTT
        SDL2::SDL2
    PRIVATE
        fmt
)

target_include_directories(sdk
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)


if(MSVC)
    target_compile_options(sdk PRIVATE /utf-8 /W4 /permissive- /volatile:iso /Zc:preprocessor /EHsc /Zc:__cplusplus /Zc:externConstexpr /Zc:throwingNew)
endif()

if(UNIX AND NOT APPLE)
    target_compile_options(sdk PRIVATE -Wall -Wextra -Wconversion)
endif()