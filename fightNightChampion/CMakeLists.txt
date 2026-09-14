cmake_minimum_required(VERSION 3.25)
project(fight_night_champion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(generated/rexglue.cmake)
include(../cmake/Recomp.cmake)

recomp_add_game(fight_night_champion
    OUTPUT_NAME "Fight Night Champion"
    SOURCES
        src/main.cpp
    SETTINGS "${CMAKE_CURRENT_SOURCE_DIR}/settings/fight_night_champion.toml"
    ICON "${CMAKE_CURRENT_SOURCE_DIR}/metadata/fight_night_champion.ico"
    RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources/fight_night_champion.rc"
    DEVELOPMENT_GAME_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/assets"
)
