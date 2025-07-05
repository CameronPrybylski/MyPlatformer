cmake_minimum_required(VERSION 3.15)
project(MyPlatformerGame)

add_executable(MyPlatformerGame
    src/main.cpp
    src/Level.cpp
    src/Player.cpp
    src/Obstacle.cpp
    # Add your game source files here
)

target_include_directories(MyPlatformerGame
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../engine/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include          #Game Headers   
)

target_link_libraries(MyPlatformerGame PRIVATE Engine)

