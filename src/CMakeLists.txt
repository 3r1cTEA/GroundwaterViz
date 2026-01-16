add_subdirectory(core)
add_subdirectory(rendering)
add_subdirectory(ui)


add_executable(GroundwaterViz
    main.cpp
)



target_link_libraries(GroundwaterViz PRIVATE
    core
    ui
    Qt6::Widgets
    Qt6::OpenGLWidgets
    OpenGL::GL
)
