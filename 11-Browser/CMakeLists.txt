cmake_minimum_required(VERSION 3.16)

add_application(Browser
    AboutBox.c
    AppInit.c
    Browser.c
    BufMgr.c
    DialogUtil.c
    Display.c
    DocUtil.c
    FileErr.c
    FileUtil.c
    MenuUtil.c
    MiscUtil.c
    WindowTbl.c
    WindowUtil.c
    ../ThinkCHelper/ThinkHelpers.c
    Browser.r
    )

# Enable -ffunction-sections and -gc-sections to make the app as small as possible
set_target_properties(Browser PROPERTIES COMPILE_OPTIONS -ffunction-sections)
set_target_properties(Browser PROPERTIES LINK_FLAGS "-Wl,-gc-sections")

# This is old code (K&R function definitions, etc.), tell the compiler so for good measure
set_target_properties(Browser PROPERTIES C_STANDARD 90)
