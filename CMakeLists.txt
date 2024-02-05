cmake_minimum_required(VERSION 3.16)

project(WeatherstationGui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appWeatherstationGui
  src/main.cpp
)

qt_add_qml_module(appWeatherstationGui
  URI WeatherstationGui
  VERSION 1.0
  QML_FILES
    src/qml/Main.qml
)

set_target_properties(appWeatherstationGui PROPERTIES
  WIN32_EXECUTABLE TRUE
)

target_link_libraries(appWeatherstationGui
  PRIVATE Qt6::Quick
)

include_directories(src)
