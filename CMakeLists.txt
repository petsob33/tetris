cmake_minimum_required(VERSION 3.12)
project(tetris C)

set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(tetris 
    main.c
    grafic.c
    controller.c
)



target_include_directories(tetris PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(tetris PRIVATE 
    ${SDL2_LIBRARIES} 
    ${SDL2_TTF_LIBRARIES} 
    m
)