cmake_minimum_required(VERSION 3.16)

project(WeatherstationGui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appWeatherstationGui
  src/downloader.h
  src/downloader.cpp
  src/imagesize.h
  src/dayinfo.h
  src/dayinfodownloader.h
  src/dayinfodownloader.cpp
  src/imagedownloader.h
  src/imagedownloader.cpp
  src/adlserializerqstring.h
  src/jsonserializeimageresolution.h

  src/main.cpp
)

qt_add_qml_module(appWeatherstationGui
  URI WeatherstationGui
  VERSION 1.0
  QML_FILES
    src/qml/Main.qml
  SOURCES
    src/recentimage.h
    src/recentimage.cpp
    src/imageresolution.h
)

add_subdirectory(dependencies/nlohmann_json)

set_target_properties(appWeatherstationGui PROPERTIES
  WIN32_EXECUTABLE TRUE
)

target_link_libraries(appWeatherstationGui
  PRIVATE 
    Qt6::Quick
    nlohmann_json::nlohmann_json
)

include_directories(src)
