# Using Google's test framework: https://github.com/google/googletest

# Setup testing
enable_testing()

# Add test executables

# Config tests
add_executable(${PROJECT_NAME}-config-test
    "config/files-test.cpp"
)

add_test(
    NAME ${PROJECT_NAME}-config-test
    COMMAND ${PROJECT_NAME}-config-test
)

target_include_directories(${PROJECT_NAME}-config-test
    PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
)

target_link_libraries(${PROJECT_NAME}-config-test
    PRIVATE
        ${PROJECT_NAME}-Gui
        GTest::gtest_main
        Qt6::Core
)

add_custom_command(
    TARGET ${PROJECT_NAME}-config-test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt6::Core>
        $<TARGET_FILE:Qt6::Core>
        $<TARGET_FILE:Qt6::Gui>
        $<TARGET_FILE:Qt6::Widgets>
        $<TARGET_FILE:Qt6::SvgWidgets>
        $<TARGET_FILE_DIR:${PROJECT_NAME}-config-test>
)

set_target_properties(${PROJECT_NAME}-config-test
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/test"
)

# Core tests
add_executable(${PROJECT_NAME}-core-test
    "core/day-test.cpp"
)

add_test(
    NAME ${PROJECT_NAME}-core-test
    COMMAND ${PROJECT_NAME}-core-test
)

target_include_directories(${PROJECT_NAME}-core-test
    PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
)

target_link_libraries(${PROJECT_NAME}-core-test
    PRIVATE
        ${PROJECT_NAME}-Core
        GTest::gtest_main
        Qt6::Core
)

add_custom_command(
    TARGET ${PROJECT_NAME}-core-test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt6::Core>
        $<TARGET_FILE_DIR:${PROJECT_NAME}-core-test>
)

set_target_properties(${PROJECT_NAME}-core-test
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/test"
)

# One target to build all tests
add_custom_target(${PROJECT_NAME}-Tests)
add_dependencies(${PROJECT_NAME}-Tests
    ${PROJECT_NAME}-config-test
    ${PROJECT_NAME}-core-test
)
set_target_properties(${PROJECT_NAME}-Tests
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/test"
)

# CMake test discovery
include(GoogleTest)
gtest_discover_tests(
    ${PROJECT_NAME}-core-test
)