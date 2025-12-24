qt_add_qml_module(wsgui_quick
  URI lib.wsgui_quick
  VERSION 1.0
  STATIC
  SOURCES
    imagetilesnode.h
    imagetilesnode.cpp
    panoramaview.h
    panoramaview.cpp
    imagetilesfileloader.h
    imagetilesfileloader.cpp
)

target_include_directories(wsgui_quick INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(wsgui_quick
  PUBLIC 
    Qt6::Core
    Qt6::Quick
    wsgui_core
)
