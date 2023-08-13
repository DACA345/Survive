add_library(SurviveCore
    "Action.cpp"
    "Bar.cpp"
    "Day.cpp"
    "Engine.cpp"
    "Level.cpp"
    "Animal.cpp"
    "Plant.cpp"
    "Event.cpp"
    "Game.cpp"
)

target_link_libraries(SurviveCore
    PRIVATE
        Qt6::Core
)