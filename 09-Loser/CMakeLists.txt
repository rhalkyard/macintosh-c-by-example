cmake_minimum_required(VERSION 3.16)

add_application(Loser
    DialogUtil.c
    FileUtil.c
    Loser.c
    MiscUtil.c
    WindowUtil.c
    ../ThinkCHelper/ThinkHelpers.c
    Loser.r
    )

# Enable -ffunction-sections and -gc-sections to make the app as small as possible
set_target_properties(Loser PROPERTIES COMPILE_OPTIONS -ffunction-sections)
set_target_properties(Loser PROPERTIES LINK_FLAGS "-Wl,-gc-sections")
