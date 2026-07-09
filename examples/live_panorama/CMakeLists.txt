qt_add_executable(live_panorama
  main.cpp
  backend.h
  backend.cpp
)

qt_add_qml_module(live_panorama
  URI LivePanorama
  VERSION 1.0
  QML_FILES
    Main.qml
)

target_link_libraries(live_panorama
  PRIVATE
    Qt6::Quick
    wsgui_core
    wsgui_quickplugin
)

include(GNUInstallDirs)
install(TARGETS live_panorama
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
