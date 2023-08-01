add_library(SurviveCore
    "Bar.cpp"
    "Day.cpp"
    "Engine.cpp"
    "Level.cpp"
)

target_link_libraries(SurviveCore
    PRIVATE
        Qt6::Core
)