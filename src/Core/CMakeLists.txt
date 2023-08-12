add_library(SurviveCore
    "Bar.cpp"
    "Day.cpp"
    "Engine.cpp"
    "Level.cpp"
 "Action.h" "Animal.cpp" "Plant.cpp" "Event.cpp" "Game.cpp" "Game.h")

target_link_libraries(SurviveCore
    PRIVATE
        Qt6::Core
)