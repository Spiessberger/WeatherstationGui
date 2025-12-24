qt_add_executable(dynamic_scheme
  main.cpp
)

target_link_libraries(dynamic_scheme
  PRIVATE
    Qt6::Core
    Qt6::Gui
    material_color_utilities
)

include(GNUInstallDirs)
install(TARGETS dynamic_scheme
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
