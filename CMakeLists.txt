cmake_minimum_required(VERSION 3.23)

project(
    unnamed-game
    VERSION 0.0.1
    LANGUAGES CXX
)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_C_STANDARD 11)
# set(CMAKE_CXX_STANDARD 17)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/entt)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/fmt)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/llgl)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sdk)

add_subdirectory(samples)

# enable_testing()
# add_subdirectory(tests)
