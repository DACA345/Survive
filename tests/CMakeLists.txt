# Using Google's test framework: https://github.com/google/googletest

# Setup testing
enable_testing()

# Add test executable
add_executable(${PROJECT_NAME}-core-test
    "core/day-test.cpp"
 "core/animal-test.cpp" "core/animal-test.cpp" "core/plant-test.cpp" "core/event-test.cpp")

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
        SurviveCore
        GTest::gtest_main
        Qt6::Core
)

# Copy DLLs
add_custom_command(
    TARGET ${PROJECT_NAME}-core-test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt6::Core>
        $<TARGET_FILE_DIR:${PROJECT_NAME}-core-test>
)

# Copy test data
add_custom_command(
    TARGET ${PROJECT_NAME}-core-test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/data"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}-core-test>/data"
)

# CMake test discovery
include(GoogleTest)
gtest_discover_tests(
    ${PROJECT_NAME}-core-test
)