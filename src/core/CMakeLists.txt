add_library(${PROJECT_NAME}-Core
    "Engine.cpp"
    "Level.cpp"
)

target_link_libraries(${PROJECT_NAME}-Core
    PRIVATE
        Qt6::Core
)