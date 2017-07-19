cmake_minimum_required(VERSION 3.7)
project(captive_portal)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.c)
include_directories(~/.mos/modules/mongoose-os-1.9)

add_executable(captive_portal ${SOURCE_FILES})