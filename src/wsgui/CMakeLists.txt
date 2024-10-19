qt_add_library(wsgui
  wsgui_global.h

  colors/colorschemedata.h

  core/adlserializerqstring.h
  core/downloader.h
  core/downloader.cpp

  data/indoorclimatedata.cpp
  data/indoorclimatedata.h
  data/indoorclimatedataset.h
  data/measurement.h
  data/weatherstationdata.cpp
  data/weatherstationdata.h
  data/weatherstationdataset.h
  
  panomax/imagesize.h
  panomax/dayinfo.h
  panomax/dayinfodownloader.h
  panomax/dayinfodownloader.cpp
  panomax/imagedownloader.h
  panomax/imagedownloader.cpp
  panomax/jsonserializeimageresolution.h
  panomax/recentimageinfo.h
  panomax/recentimageinfo.cpp
)

qt_add_qml_module(wsgui
  URI wsgui
  VERSION 1.0

  SOURCES
    colors/colorscheme.h
    colors/colorscheme.cpp
    colors/colorschemeprovider.h
    colors/colorschemeprovider.cpp
    colors/theme.h
    colors/theme.cpp

    core/iconprovider.h
    core/iconprovider.cpp
    core/imagesdirectory.h
    core/imagesdirectory.cpp
    core/panoramaimage.h
    core/panoramaimage.cpp
    core/settings.h
    core/settings.cpp
    
    data/displaydata.cpp
    data/displaydata.h
    data/homescreendata.cpp
    data/homescreendata.h
    data/indoorclimatedatadisplay.cpp
    data/indoorclimatedatadisplay.h
    data/weatherstationdatadisplay.cpp
    data/weatherstationdatadisplay.h
    
    panomax/backgroundimage.h
    panomax/backgroundimage.cpp
    panomax/imageresolution.h
)

target_compile_options(wsgui
  PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)

target_compile_definitions(wsgui PRIVATE WSGUI_LIBRARY)

find_package(Qt6 REQUIRED COMPONENTS Quick Sql)
find_package(nlohmann_json REQUIRED)
find_package(material_color_utilities REQUIRED)

target_link_libraries(wsgui
  PRIVATE 
    Qt6::Quick
    Qt6::Sql
    nlohmann_json::nlohmann_json
    material_color_utilities::material_color_utilities
)

target_include_directories(wsgui
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}

  # needed to make qt_add_qml_module work with subdirectories
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/colors
    ${CMAKE_CURRENT_LIST_DIR}/core
    ${CMAKE_CURRENT_LIST_DIR}/data
    ${CMAKE_CURRENT_LIST_DIR}/panomax
)
