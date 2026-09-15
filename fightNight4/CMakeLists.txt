cmake_minimum_required(VERSION 3.25)
project(fight_night_round_4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(generated/rexglue.cmake)
include(../framework/cmake/Recomp.cmake)

recomp_add_game(fight_night_round_4
    OUTPUT_NAME "Fight Night Round 4"
    SOURCES
        src/main.cpp
    SETTINGS "${CMAKE_CURRENT_SOURCE_DIR}/settings/fight_night_round_4.toml"
    ICON "${CMAKE_CURRENT_SOURCE_DIR}/metadata/fight_night_round_4.ico"
    RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/fight_night_round_4.rc"
    DEVELOPMENT_GAME_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/assets"
)
