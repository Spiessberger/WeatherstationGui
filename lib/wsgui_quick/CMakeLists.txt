qt_add_qml_module(wsgui_quick
  URI wsgui.quick
  VERSION 1.0
  STATIC
  # mirror the uri in the build tree so ide code models can resolve
  # the import (see QML_IMPORT_PATH in the top-level CMakeLists.txt)
  OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml/wsgui/quick
  SOURCES
    wsguiforeign.h
    imagetilesnode.h
    imagetilesnode.cpp
    panoramaview.h
    panoramaview.cpp
    imagetilesfileloader.h
    imagetilesfileloader.cpp
    colorscheme.h
    colorscheme.cpp
    colorschemeloader.h
    colorschemeloader.cpp
)

target_include_directories(wsgui_quick INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(wsgui_quick
  PUBLIC 
    Qt6::Core
    Qt6::Quick
    wsgui_core
)
