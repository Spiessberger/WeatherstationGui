qt_add_library(wsgui_core
  STATIC
    colorschemedata.h
    imagetiles.h
    imagetiles.cpp
    loadcolorscheme.h
    loadcolorscheme.cpp
    downloader.h
    downloader.cpp
    panomax/dayimagedata.h
    panomax/dayimagedatadownloader.h
    panomax/dayimagedatadownloader.cpp
    panomax/imagedownloader.h
    panomax/imagedownloader.cpp
)

target_include_directories(wsgui_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(wsgui_core
  PUBLIC 
    Qt6::Core
    Qt6::Gui
    Qt6::Network
    qtpromise
  PRIVATE
    glaze::glaze
    material_color_utilities
)
