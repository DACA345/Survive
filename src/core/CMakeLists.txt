add_library(${PROJECT_NAME}-Core
    "action.cpp"
    "animal.cpp"
    "bar.cpp"
    "day.cpp"
    "engine.cpp"
    "level.cpp"
    "plant.cpp"
)

target_link_libraries(${PROJECT_NAME}-Core
    PRIVATE
        Qt6::Core
)