add_subdirectory(core)

# Configure Survive GUI as library
add_library(${PROJECT_NAME}-Gui STATIC
    "ui/widgets/game/notebook/history/journalday.cpp"
    "ui/widgets/game/notebook/actionmenu.cpp"
    "ui/widgets/game/notebook/historywidget.cpp"
    "ui/widgets/game/notebook/notebookwidget.cpp"
    "ui/widgets/game/notebook/resultwidget.cpp"
    "ui/widgets/game/notebook/sleepwidget.cpp"
    "ui/widgets/game/gameover.cpp"
    "ui/widgets/game/pausemenu.cpp"
    "ui/widgets/mainmenu/loadgamemenu.cpp"
    "ui/widgets/mainmenu/newgamemenu.cpp"
    "ui/widgets/mainmenu/settingsmenu.cpp"
    "ui/widgets/mainmenu/menu.cpp"
    "ui/widgets/draggablewidget.cpp"
    "ui/widgets/scalablelabel.cpp"
    "ui/widgets/scalablewidget.cpp"
    "ui/widgets/svgpushbutton.cpp"
    "ui/mainmenu.cpp"
    "ui/game.cpp"
    "util/resolution.cpp"
    "survivegame.cpp"
)

target_link_libraries(${PROJECT_NAME}-Gui
    PRIVATE
        ${PROJECT_NAME}-Core
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::SvgWidgets
)

# Create game executable

qt_add_executable(Survive
    "main.cpp"
    "survive.rc"
)

target_link_libraries(Survive
    PRIVATE
        ${PROJECT_NAME}-Gui
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::SvgWidgets
)

set_target_properties(Survive
    PROPERTIES
        WIN32_EXECUTABLE $<NOT:$<CONFIG:Debug>>
        MACOSX_BUNDLE ON
)

add_compile_definitions(Survive
    PRIVATE
        VERSION="${CMAKE_PROJECT_VERSION}"
)

# Qt bundling with runtimes
install(TARGETS Survive
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Qt version changes to deployment
if(Qt6_VERSION VERSION_LESS 6.5.0)
    qt_generate_deploy_app_script(
        TARGET Survive
        FILENAME_VARIABLE QT_DEPLOY_SCRIPT
        NO_UNSUPPORTED_PLATFORM_ERROR
    )
else()
    qt_generate_deploy_app_script(
        TARGET Survive
        OUTPUT_SCRIPT QT_DEPLOY_SCRIPT
        NO_UNSUPPORTED_PLATFORM_ERROR
    )
endif()

# Run Qt deploy Script
install(SCRIPT ${QT_DEPLOY_SCRIPT})

# Copy necessary directories
install(
    DIRECTORY
        "${CMAKE_SOURCE_DIR}/levels"
        "${CMAKE_SOURCE_DIR}/textures"
    DESTINATION
        # CMake install prefix causes CPack generator errors
        ${CMAKE_INSTALL_BINDIR}/..
)

# Include CPack for release packaging
include(CPack)