add_subdirectory(Core)

qt_add_executable(Survive
    "UI/Widgets/MainMenu/LoadGameMenu.cpp"
    "UI/Widgets/MainMenu/NewGameMenu.cpp"
    "UI/Widgets/MainMenu/SettingsMenu.cpp"
    "UI/Widgets/ScalableWidget.cpp"
    "UI/MainMenu.cpp"
    "SurviveGame.cpp"
    "main.cpp"
)

target_link_libraries(Survive
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        SurviveCore
)

set_target_properties(Survive
    PROPERTIES
        WIN32_EXECUTABLE $<NOT:$<CONFIG:Debug>>
        MACOSX_BUNDLE ON
)

add_compile_definitions(Survive
    PRIVATE
        VERSION="${CMAKE_PROJECT_VERSION}"
        DIRECTORY_PATH="${CMAKE_INSTALL_PREFIX}"
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
        ${CMAKE_INSTALL_PREFIX}
)

# Include CPack for release packaging
include(CPack)