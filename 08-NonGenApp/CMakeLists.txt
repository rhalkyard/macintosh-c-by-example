cmake_minimum_required(VERSION 3.16)

add_application(NonGenApp
    AboutBox.c
    AppInit.c
    DialogUtil.c
    Display.c
    DocUtil.c
    FileUtil.c
    MenuUtil.c
    MiscUtil.c
    Shell.c
    WindowUtil.c
    ../ThinkCHelper/ThinkHelpers.c
    nonGenApp.r
    )

# Enable -ffunction-sections and -gc-sections to make the app as small as possible
set_target_properties(NonGenApp PROPERTIES COMPILE_OPTIONS -ffunction-sections)
set_target_properties(NonGenApp PROPERTIES LINK_FLAGS "-Wl,-gc-sections")

# This is old code (K&R function definitions, etc.), tell the compiler so for good measure
set_target_properties(NonGenApp PROPERTIES C_STANDARD 90)
