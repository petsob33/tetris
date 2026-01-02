cmake_minimum_required(VERSION 3.12)

project(tetris)

# 1. Nastavení standardu C
set(CMAKE_C_STANDARD 99)

# 2. Přidání vlajek překladače a linkeru
# ZDE JSEM TO SLOUČIL A PŘIDAL SANITIZER:
# -fsanitize=address musí být jak při kompilaci (C_FLAGS), tak při spojování (LINKER_FLAGS)
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra -fsanitize=address")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

# 3. Vyhledání knihovny SDL
find_package(SDL2 REQUIRED)

# 4. Vytvoření programu
add_executable(tetris 
    main.c
    grafic.c
    controller.c
)

# 5. Přidání hlavičkových souborů
target_include_directories(tetris PRIVATE ${SDL2_INCLUDE_DIRS})

# 6. Přilinkování knihoven
target_link_libraries(tetris ${SDL2_LIBRARIES} m)