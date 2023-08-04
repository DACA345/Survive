find_package(Doxygen)

# Add user defined Qt6 install prefix to CMAKE_PREFIX_PATH for find_package to work
list(APPEND CMAKE_PREFIX_PATH ${Qt6_INSTALL_PREFIX})
find_package(Qt6 6.3.2
    REQUIRED COMPONENTS
        Core
        Gui
        Widgets
        SvgWidgets
)
qt_standard_project_setup()