add_executable(pong
    ${CMAKE_CURRENT_SOURCE_DIR}/pong/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pong/sys.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pong/factories.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pong/collision.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pong/image.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pong/stb_image.cpp
)

target_include_directories(pong PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/pong)
target_link_libraries(pong PUBLIC EnTT::EnTT SDL2::SDL2 fmt)