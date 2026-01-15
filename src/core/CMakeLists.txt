file(GLOB CPP_FILES CONFIGURE_DEPENDS "*.cpp")
file(GLOB H_FILES CONFIGURE_DEPENDS "*.h")

add_library(core STATIC
    ${CPP_FILES}
    ${H_FILES}
)


target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

