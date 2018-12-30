project(kodi-nfo-cli CXX)
cmake_minimum_required(VERSION 3.11)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(3rdParty)
add_subdirectory(core)
add_subdirectory(cli)
