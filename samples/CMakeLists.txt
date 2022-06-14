add_executable(pong
    ${CMAKE_CURRENT_SOURCE_DIR}/pong/main.cpp
)

target_include_directories(pong PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/pong)
target_link_libraries(pong PUBLIC EnTT::EnTT SDL2::SDL2)