list(APPEND CMAKE_PREFIX_PATH ${Qt6_INSTALL_PREFIX})
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()