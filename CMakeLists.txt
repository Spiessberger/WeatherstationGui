cmake_minimum_required(VERSION 3.16)

project(WeatherstationGui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appWeatherstationGui
  src/main.cpp
  src/panomaximage.h
  src/panomaximage.cpp
  src/messagehandler.h
  src/messagehandler.cpp
  src/panomaximagesinfo.h
  src/panomaximagesinfo.cpp
  src/panomaximageprovider.h
  src/panomaximageprovider.cpp
)

include_directories(src)

qt_add_qml_module(appWeatherstationGui
  URI WeatherstationGui

  VERSION 1.0

  QML_FILES
    qml/Main.qml
    qml/PanoramaImage.qml
    qml/PanoramaView.qml

  SOURCES
    src/tiledimagemodel.h
    src/tiledimagemodel.cpp
    src/panomaximagesize.h
    src/panomaximagesize.cpp
    src/panomaxrecentimage.h
    src/panomaxrecentimage.cpp
)

set_target_properties(appWeatherstationGui PROPERTIES
  WIN32_EXECUTABLE TRUE
)

target_link_libraries(appWeatherstationGui
  PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appWeatherstationGui
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
