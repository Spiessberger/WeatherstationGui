qt_add_library(wsgui_core
  STATIC
    imagetiles.h
    imagetiles.cpp
    panomax/dayimagedata.h
    panomax/dayimagedatadownloader.h
    panomax/dayimagedatadownloader.cpp
    downloader.h
    downloader.cpp
    panomax/imagedownloader.h
    panomax/imagedownloader.cpp
)

target_include_directories(wsgui_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(wsgui_core
  PUBLIC 
    Qt6::Core
    Qt6::Gui
    Qt6::Network
    glaze::glaze
    qtpromise
)
target_link_libraries(wsgui_core PRIVATE Qt6::Core)
target_link_libraries(wsgui_core PRIVATE Qt6::Core)
