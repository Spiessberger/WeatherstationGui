find_package(Qt6 REQUIRED COMPONENTS QuickControls2)

qt_add_executable(weatherstation_gui
  main.cpp
  logging.h
  logging.cpp
  clockmodel.h
  clockmodel.cpp
  panoramamodel.h
  panoramamodel.cpp
)

qt_add_qml_module(weatherstation_gui
  URI app.weatherstation
  VERSION 1.0
  QML_FILES
    Main.qml
)

target_link_libraries(weatherstation_gui
  PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
    wsgui_core
    wsgui_quickplugin
)

include(GNUInstallDirs)
install(TARGETS weatherstation_gui
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
