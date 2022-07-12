add_executable(pong
    ${CMAKE_CURRENT_SOURCE_DIR}/pong/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pong/sys.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pong/factories.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pong/collision.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pong/image.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pong/stb_image.cpp
)

target_include_directories(pong PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/pong)
target_link_libraries(pong PUBLIC EnTT::EnTT SDL2::SDL2 fmt LLGL)

add_library(plugin SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/plugin/plugin.cpp
)

target_include_directories(plugin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/plugin)
target_link_libraries(plugin PUBLIC sdk)
set_target_properties(plugin PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_executable(plugin_test
    ${CMAKE_CURRENT_SOURCE_DIR}/plugin/main.cpp
)

target_include_directories(plugin_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/plugin)
target_link_libraries(plugin_test PUBLIC sdk fmt)