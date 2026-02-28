qt_add_executable(color_scheme_viewer
  main.cpp
)

qt_add_qml_module(color_scheme_viewer
  URI ColorSchemeViewer
  VERSION 1.0
  QML_FILES
    Main.qml
)

target_link_libraries(color_scheme_viewer
  PRIVATE
    Qt6::Quick
    wsgui_quickplugin
)

include(GNUInstallDirs)
install(TARGETS color_scheme_viewer
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
