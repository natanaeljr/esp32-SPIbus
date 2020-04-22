set(COMPONENT_ADD_INCLUDEDIRS "include")
file(GLOB COMPONENT_SRCS src/*.cc src/*.cpp src/*.c)

set(COMPONENT_REQUIRES
    driver
)

set(COMPONENT_PRIV_REQUIRES)

register_component()

component_compile_options(PUBLIC "-DSPIBUS_COMPONENT_TRUE=1")
