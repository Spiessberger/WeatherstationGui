find_package(Qt6 REQUIRED COMPONENTS 
  Core
  Quick
)

qt_add_library(wsgui_core
  STATIC
    imagetilesnode.h
    imagetilesnode.cpp
    imagetiles.h
    imagetiles.cpp
)

target_include_directories(wsgui_core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

qt_add_qml_module(wsgui_core
  URI lib.wsgui_core
  VERSION 1.0
  SOURCES
    qmlpanoramaview.h
    qmlpanoramaview.cpp
    qmlimagetilesfileloader.h
    qmlimagetilesfileloader.cpp
)

# if (NOT MSVC)
#   target_compile_options(wsgui_core
#     PRIVATE
#       -Wall
#       -Wextra
#       -Wpedantic
#       -Werror
#   )
# endif()

target_link_libraries(wsgui_core
  PUBLIC 
    Qt6::Core
    Qt6::Quick
)
