cmake_minimum_required(VERSION 3.12)

project(tetris)
set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)
find_package(PkgConfig REQUIRED) 
pkg_search_module(SDL2_TTF REQUIRED SDL2_ttf)

# set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -g")

add_executable(tetris 
    main.c
    grafic.c
    controller.c
)

target_include_directories(tetris PRIVATE 
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)

target_link_libraries(tetris 
    ${SDL2_LIBRARIES} 
    ${SDL2_TTF_LIBRARIES}
    m
#    -fsanitize=address 
)