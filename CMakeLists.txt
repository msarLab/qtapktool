cmake_minimum_required(VERSION 3.10)
project(qtapktool)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)



add_executable(qtapktool main.cpp mainwindow.cpp mainwindow.ui console.cpp AboutMe.cpp AboutMe.h Command.cpp Command.h)

target_link_libraries(qtapktool Qt5::Core)
target_link_libraries(qtapktool Qt5::Widgets)