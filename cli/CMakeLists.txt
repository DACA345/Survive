# Build the command line version of the game

add_executable(${PROJECT_NAME}-cli
    "src/main.cpp"
)

target_include_directories(${PROJECT_NAME}-cli
    PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
)

target_link_libraries(${PROJECT_NAME}-cli
    PRIVATE
        ${PROJECT_NAME}-Core
        Qt6::Core
)

set_target_properties(${PROJECT_NAME}-cli
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/cli"
)

add_custom_command(
    TARGET ${PROJECT_NAME}-cli POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt6::Core>
        $<TARGET_FILE_DIR:${PROJECT_NAME}-cli>
)

# Copy data for cli
add_custom_command(
    TARGET ${PROJECT_NAME}-cli POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/levels"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}-cli>/levels"
)