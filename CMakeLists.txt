cmake_minimum_required(VERSION 3.26)
project(BouncingBalls)

set(CMAKE_CXX_STANDARD 14)

include_directories(core)

add_executable(BouncingBalls
        core/back-end.h
        core/config.h
        core/front-end.h
        main.cpp
)

target_link_libraries(${PROJECT_NAME} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer)