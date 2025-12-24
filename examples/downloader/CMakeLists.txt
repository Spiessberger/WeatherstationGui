qt_add_executable(downloader
  main.cpp
)

target_link_libraries(downloader
  PRIVATE
    wsgui_core
)

include(GNUInstallDirs)
install(TARGETS downloader
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
