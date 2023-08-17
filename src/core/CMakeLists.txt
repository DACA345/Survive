add_library(${PROJECT_NAME}-Core
    "action.cpp"
    "animal.cpp"
    "bar.cpp"
    "day.cpp"
    "engine.cpp"
    "event.cpp"
    "game.cpp"
    "level.cpp"
    "plant.cpp"
 "explore.cpp" "explore.h")

target_link_libraries(${PROJECT_NAME}-Core
    PRIVATE
        Qt6::Core
)