qt_add_library(wsgui_data
  indoorclimatedata.cpp
  indoorclimatedata.h
  indoorclimatedataset.h
  measurement.h
  weatherstationdata.cpp
  weatherstationdata.h
  weatherstationdataset.h
)

qt_add_qml_module(wsgui_data
  URI wsgui.data
  VERSION 1.0

  SOURCES
    displaydata.cpp
    displaydata.h
    homescreendata.cpp
    homescreendata.h
    indoorclimatedatadisplay.cpp
    indoorclimatedatadisplay.h
    weatherstationdatadisplay.cpp
    weatherstationdatadisplay.h
)

target_compile_options(wsgui_data
  PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)

target_link_libraries(wsgui_data
  PRIVATE 
    Qt6::Quick
    Qt6::Sql
)

target_include_directories(wsgui_data PUBLIC ${CMAKE_CURRENT_LIST_DIR})
