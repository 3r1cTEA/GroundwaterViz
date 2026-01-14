add_library(core STATIC
    Grid3D.cpp
    FlowModel.cpp
    ParticleTracker.cpp
)

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

