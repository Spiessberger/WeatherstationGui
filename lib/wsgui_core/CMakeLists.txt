qt_add_library(wsgui_core
  STATIC
    wsguienums.h
    logging.h
    logging.cpp
    colorschemedata.h
    imagetiles.h
    imagetiles.cpp
    colorschemegenerator.h
    colorschemegenerator.cpp
    downloader.h
    downloader.cpp
    appsettings.h
    appsettingsloader.h
    appsettingsloader.cpp
    panomax/dayimagedata.h
    panomax/dayimagedatadownloader.h
    panomax/dayimagedatadownloader.cpp
    panomax/imagedownloader.h
    panomax/imagedownloader.cpp
    panomax/panoramaupdater.h
    panomax/panoramaupdater.cpp
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
