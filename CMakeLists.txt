cmake_minimum_required(VERSION 3.5)

project(Projekt_cpp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_executable(Projekt_cpp
    main.cpp
    main_window.cpp
    main_window.h
    main_window.ui
    paint_area.cpp
    paint_area.h
)

file(GLOB MY_PUBLIC_HEADERS
  "resources/cursor/*.png"
)
file(COPY ${MY_PUBLIC_HEADERS} DESTINATION resources/cursor)

target_link_libraries(Projekt_cpp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
