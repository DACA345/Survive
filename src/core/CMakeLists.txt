add_library(${PROJECT_NAME}-Core
    "engine.cpp"
    "level.cpp"
)

target_link_libraries(${PROJECT_NAME}-Core
    PRIVATE
        Qt6::Core
)