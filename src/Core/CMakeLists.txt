add_library(SurviveCore
    "Engine.cpp"
    "Level.cpp"
)

target_link_libraries(SurviveCore
    PRIVATE
        Qt6::Core
)