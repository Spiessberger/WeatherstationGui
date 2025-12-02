find_package(Qt6 REQUIRED COMPONENTS Core Network)

qt_add_executable(panomax_day_image_data
  main.cpp
)

target_link_libraries(panomax_day_image_data
  PRIVATE
    Qt6::Core
    Qt6::Network
    wsgui_core
)

include(GNUInstallDirs)
install(TARGETS panomax_day_image_data
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
