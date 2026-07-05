cmake_minimum_required(VERSION 3.22)

project(WeatherStationGUI VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
  Core
  Gui
  Network
  Quick
)
qt_standard_project_setup(REQUIRES 6.11)

option(WSGUI_BUILD_EXAMPLES "Build example applications" OFF)

# read by Qt Creator's qml code model to locate the WsGui module
set(QML_IMPORT_PATH ${CMAKE_BINARY_DIR}/qml
    CACHE STRING "qml import path for the ide code model" FORCE)

# add_subdirectory(app)
add_subdirectory(lib)

if(WSGUI_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
