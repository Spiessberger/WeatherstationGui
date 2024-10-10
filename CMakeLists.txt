cmake_minimum_required(VERSION 3.16)

project(WeatherstationGui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Sql)
find_package(nlohmann_json REQUIRED)
find_package(material_color_utilities REQUIRED)

qt_standard_project_setup(REQUIRES 6.7)

add_subdirectory(src)

