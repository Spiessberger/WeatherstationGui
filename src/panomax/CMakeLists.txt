qt_add_library(wsgui_panomax
  imagesize.h
  dayinfo.h
  dayinfodownloader.h
  dayinfodownloader.cpp
  imagedownloader.h
  imagedownloader.cpp
  jsonserializeimageresolution.h
  recentimageinfo.h
  recentimageinfo.cpp
)

qt_add_qml_module(wsgui_panomax
  URI wsgui.panomax
  VERSION 1.0

  SOURCES
    backgroundimage.h
    backgroundimage.cpp
    imageresolution.h
)

target_compile_options(wsgui_panomax
  PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)

target_link_libraries(wsgui_panomax
  PRIVATE 
    Qt6::Quick
    nlohmann_json::nlohmann_json
    wsgui
)

target_include_directories(wsgui_panomax PUBLIC ${CMAKE_CURRENT_LIST_DIR})
