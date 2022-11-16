cmake_minimum_required(VERSION 3.16)

add_application("Hey"
    Hey.c
    )

# Enable -ffunction-sections and -gc-sections to make the app as small as possible
set_target_properties("Hey" PROPERTIES COMPILE_OPTIONS -ffunction-sections)
set_target_properties("Hey" PROPERTIES LINK_FLAGS "-Wl,-gc-sections")
