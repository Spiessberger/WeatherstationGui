qt_add_executable(panomax_image
  main.cpp
)

target_link_libraries(panomax_image
  PRIVATE
    Qt6::Core
    wsgui_core
)

include(GNUInstallDirs)
install(TARGETS panomax_image
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
