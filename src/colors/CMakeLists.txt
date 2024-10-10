qt_add_library(wsgui_colors
  colorschemedata.h
)

qt_add_qml_module(wsgui_colors
  URI wsgui.colors
  VERSION 1.0

  SOURCES
    colorscheme.h
    colorscheme.cpp
    colorschemeprovider.h
    colorschemeprovider.cpp
    theme.h
    theme.cpp
)

target_compile_options(wsgui_panomax
  PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)

target_link_libraries(wsgui_colors
  PRIVATE 
    Qt6::Quick
    material_color_utilities::material_color_utilities
)

target_include_directories(wsgui_colors PUBLIC ${CMAKE_CURRENT_LIST_DIR})
