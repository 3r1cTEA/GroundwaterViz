file(GLOB CPP_FILES CONFIGURE_DEPENDS "*.cpp")
file(GLOB H_FILES CONFIGURE_DEPENDS "*.h")

add_library(rendering STATIC
    ${CPP_FILES}
    ${H_FILES}
)

target_include_directories(rendering
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(rendering PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(rendering PUBLIC
    Qt6::Widgets
    Qt6::OpenGLWidgets
)
