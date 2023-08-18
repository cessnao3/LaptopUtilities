cmake_minimum_required(VERSION 3.5)

project(LaptopUtilities VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/windows/mainwindow.cpp
        src/windows/mainwindow.h
        src/windows/mainwindow.ui
)

qt_add_executable(LaptopUtilities
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(LaptopUtilities PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

qt_finalize_executable(LaptopUtilities)
