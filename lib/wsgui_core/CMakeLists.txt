find_package(Qt6 REQUIRED COMPONENTS 
  Core
  Gui
)

qt_add_library(wsgui_core
  STATIC
    imagetiles.h
    imagetiles.cpp
)

target_include_directories(wsgui_core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(wsgui_core
  PUBLIC 
    Qt6::Core
    Qt6::Gui
    glaze::glaze
)
