find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_add_executable(panorama_view
  main.cpp
)

qt_add_qml_module(panorama_view
  URI PanoramaView
  VERSION 1.0
  QML_FILES
    Main.qml
  RESOURCES
    tiles/tile_0.png
    tiles/tile_1.png
    tiles/tile_2.png
    tiles/tile_3.png
    tiles/tile_4.png
    tiles/tile_5.png
    tiles/tile_6.png
    tiles/tile_7.png
    tiles/tile_8.png
)

target_link_libraries(panorama_view
  PRIVATE
    Qt6::Quick
    wsgui_quickplugin
)

include(GNUInstallDirs)
install(TARGETS panorama_view
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
