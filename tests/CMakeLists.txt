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
    "core/action-test.cpp"
    "core/animal-test.cpp"
    "core/bar-test.cpp"
    "core/day-test.cpp"
    "core/engine-test.cpp"
    "core/event-test.cpp"
    "core/explore-test.cpp"
    "core/game-test.cpp"
    "core/level-test.cpp"
    "core/plant-test.cpp"
    "core/season-test.cpp"
)

add_test(
    NAME ${PROJECT_NAME}-core-test
    COMMAND ${PROJECT_NAME}-core-test
)

set_target_properties(${PROJECT_NAME}-core-test
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests"
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

add_custom_command(
    TARGET ${PROJECT_NAME}-core-test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/levels"
        ${CMAKE_BINARY_DIR}/bin/levels
)

set_target_properties(${PROJECT_NAME}-core-test
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/test"
)

# Util tests
add_executable(${PROJECT_NAME}-util-test
    "util/resolution-test.cpp"
)

add_test(
    NAME ${PROJECT_NAME}-util-test
    COMMAND ${PROJECT_NAME}-util-test
)

target_include_directories(${PROJECT_NAME}-util-test
    PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
)

target_link_libraries(${PROJECT_NAME}-util-test
    PRIVATE
        ${PROJECT_NAME}-Gui
        GTest::gtest_main
        Qt6::Core
)

add_custom_command(
    TARGET ${PROJECT_NAME}-util-test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt6::Core>
        $<TARGET_FILE:Qt6::Gui>
        $<TARGET_FILE:Qt6::Widgets>
        $<TARGET_FILE:Qt6::SvgWidgets>
        $<TARGET_FILE_DIR:${PROJECT_NAME}-util-test>
)

set_target_properties(${PROJECT_NAME}-util-test
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
    ${PROJECT_NAME}-util-test
)

set_target_properties(${PROJECT_NAME}-Tests
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/test"
)

# Copy test data
add_custom_command(
    TARGET ${PROJECT_NAME}-core-test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/data"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}-core-test>/data"
)

add_custom_command(
    TARGET ${PROJECT_NAME}-Tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/data"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}-core-test>/data"
)

# CMake test discovery
include(GoogleTest)
gtest_discover_tests(
    ${PROJECT_NAME}-core-test
    ${PROJECT_NAME}-config-test
    ${PROJECT_NAME}-util-test
)

# Configure coverage
if(TEST_COVERAGE)
    set(GEN_COVERAGE_IN ${CMAKE_SOURCE_DIR}/tests/gen_coverage.sh.in)
    set(GEN_COVERAGE_OUT ${CMAKE_BINARY_DIR}/gen_coverage.sh)
    configure_file(${GEN_COVERAGE_IN} ${GEN_COVERAGE_OUT} @ONLY)

    add_custom_target(${PROJECT_NAME}-Coverage
        COMMAND chmod +x ${GEN_COVERAGE_OUT} && ${GEN_COVERAGE_OUT}
        DEPENDS ${PROJECT_NAME}-Tests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating coverage report..." VERBATIM
    )
endif()