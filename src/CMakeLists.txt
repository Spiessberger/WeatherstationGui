add_subdirectory(wsgui)
add_subdirectory(panomax)
add_subdirectory(colors)
add_subdirectory(data)

qt_add_executable(weatherstation_gui
  ../resources/resources.qrc
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

target_compile_options(weatherstation_gui
  PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)

set_target_properties(weatherstation_gui PROPERTIES
  WIN32_EXECUTABLE TRUE
)

target_link_libraries(weatherstation_gui
  PRIVATE 
    Qt6::Quick
    Qt6::Sql
    nlohmann_json::nlohmann_json
    wsgui
    wsgui_panomax
    wsgui_colors
    wsgui_data
)
