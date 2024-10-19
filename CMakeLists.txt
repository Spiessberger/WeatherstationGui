cmake_minimum_required(VERSION 3.16)

project(WeatherstationGui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Core)

set(CMAKE_AUTORCC ON)
qt_add_library(wsgui_resources STATIC
    resources/resources.qrc
)
target_link_libraries(wsgui_resources
  PRIVATE 
    Qt6::Core
)

add_subdirectory(src)
