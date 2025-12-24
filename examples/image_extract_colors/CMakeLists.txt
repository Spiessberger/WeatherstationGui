qt_add_executable(image_extract_colors
  main.cpp
)

qt_add_resources(image_extract_colors
  "resources"
  FILES
    "21-00-00_thumb.jpg"
)

target_link_libraries(image_extract_colors
  PRIVATE
    Qt6::Core
    Qt6::Gui
    material_color_utilities
)

include(GNUInstallDirs)
install(TARGETS image_extract_colors
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
