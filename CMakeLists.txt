cmake_minimum_required(VERSION 3.16)

# Project information
project(
    "Survive"
    VERSION 0.0.2
    LANGUAGES CXX
    DESCRIPTION "C++ survival game based on real world data."
    HOMEPAGE_URL https://github.com/DACA345/Survive
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CPack information
set(CPACK_PACKAGE_DESCRIPTION ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME})

set (CPACK_PACKAGE_ICON
     "${CMAKE_SOURCE_DIR}/textures/icon\\icon.png")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_FULL "${PROJECT_VERSION}${CPACK_PACKAGE_VERSION_STAGE}")

set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)

set (CPACK_NSIS_MUI_ICON
     "${CMAKE_SOURCE_DIR}/textures/icon\\icon.ico")
set (CPACK_NSIS_MUI_UNIICON
     "${CMAKE_SOURCE_DIR}/textures/icon\\icon.ico")

# CMake output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Dependencies
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Includes
include(FindLibCheck)

# Features
include(FeatureSummary)

option(BUILD_TESTS "Build the Google unit tests" ON)
option(BUILD_DOCUMENTATION "Build doxygen documentation - requires doxygen" ${DOXYGEN_FOUND})

add_feature_info(BUILD_TESTS BUILD_TESTS "Build the Google unit tests")
add_feature_info(BUILD_DOCUMENTATION BUILD_DOCUMENTATION "Build doxygen documentation - requires doxygen")

feature_summary(WHAT ALL)

add_subdirectory(src)

# Documentation
if (BUILD_DOCUMENTATION AND DOXYGEN_FOUND)
    set(DOXYGEN_IN "${CMAKE_SOURCE_DIR}/doc/doxy.config.in")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/doc/doxy.config")

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(Doxygen-Documentation ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc/"
        COMMENT "Building doxygen documentation."
        VERBATIM
    )

    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc/html"
        DESTINATION "${CMAKE_INSTALL_DOCDIR}"
    )
elseif(BUILD_DOCUMENTATION AND NOT DOXYGEN_FOUND)
    message(WARNING "Documentation was set on but doxygen was not found. Cannot build documentation.")
endif()

# Tests
if (BUILD_TESTS)
    # Download and install googletest
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_subdirectory(tests)
endif()