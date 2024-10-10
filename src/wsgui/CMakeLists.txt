qt_add_library(wsgui
  adlserializerqstring.h
  downloader.h
  downloader.cpp
)

qt_add_qml_module(wsgui
  URI wsgui
  VERSION 1.0

  SOURCES
    iconprovider.h
    iconprovider.cpp
    imagesdirectory.h
    imagesdirectory.cpp
    panoramaimage.h
    panoramaimage.cpp
    settings.h
    settings.cpp
)

target_compile_options(wsgui
  PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)

target_link_libraries(wsgui
  PRIVATE 
    Qt6::Quick
    nlohmann_json::nlohmann_json
)

target_include_directories(wsgui PUBLIC ${CMAKE_CURRENT_LIST_DIR})
