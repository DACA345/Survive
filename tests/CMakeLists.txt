# Using Google's test framework: https://github.com/google/googletest

# Setup testing
enable_testing()

# Add test executable
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
        SurviveCore
        GTest::gtest_main
        Qt6::Core
)

add_custom_command(
    TARGET ${PROJECT_NAME}-core-test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt6::Core>
        $<TARGET_FILE_DIR:${PROJECT_NAME}-core-test>
)

# One target to build all tests
add_custom_target(${PROJECT_NAME}-Tests)
add_dependencies(${PROJECT_NAME}-Tests
    ${PROJECT_NAME}-core-test
)

# CMake test discovery
include(GoogleTest)
gtest_discover_tests(
    ${PROJECT_NAME}-core-test
)