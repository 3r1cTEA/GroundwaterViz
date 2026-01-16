file(GLOB CPP_FILES CONFIGURE_DEPENDS "*.cpp")
file(GLOB H_FILES CONFIGURE_DEPENDS "*.h")

add_library(ui STATIC
    ${CPP_FILES}
    ${H_FILES}
)

target_include_directories(ui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ui PUBLIC
    Qt6::Widgets
    Qt6::OpenGLWidgets
    rendering
)
