add_library(SurviveCore
    "Bar.cpp"
    "Day.cpp"
    "Engine.cpp"
    "Level.cpp"
 "Action.h" "Animal.cpp" "Plant.cpp" "Events.cpp" "Game.cpp")

target_link_libraries(SurviveCore
    PRIVATE
        Qt6::Core
)