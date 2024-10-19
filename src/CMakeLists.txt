find_package(Qt6 REQUIRED COMPONENTS Quick Sql)

qt_standard_project_setup(REQUIRES 6.7)

add_subdirectory(wsgui)

qt_add_executable(weatherstation_gui
  main.cpp
)

qt_add_qml_module(weatherstation_gui
  URI WeatherstationGui
  VERSION 1.0

  QML_FILES
    qml/Background.qml
    qml/PanoramaView.qml
    qml/HomeScreen.qml
    qml/Main.qml
    qml/ValueControl.qml
    qml/WindControl.qml
    qml/DigitalClock.qml
    qml/SettingsScreen.qml
    qml/AppearanceSettings.qml
)

if (NOT MSVC)
  target_compile_options(weatherstation_gui
    PRIVATE
      -Wall
      -Wextra
      -Wpedantic
      -Werror
  )
endif()

set_target_properties(weatherstation_gui PROPERTIES
  WIN32_EXECUTABLE TRUE
)

target_link_libraries(weatherstation_gui
  PRIVATE 
    Qt6::Quick
    Qt6::Sql
    wsgui
    wsgui_resources
)
