add_subdirectory(Core)

qt_add_executable(Survive
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
        WIN32_EXECUTABLE ON
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

install(SCRIPT ${QT_DEPLOY_SCRIPT})

include(CPack)