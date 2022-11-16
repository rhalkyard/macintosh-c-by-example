cmake_minimum_required(VERSION 3.16)

project("C By Example")

include_directories(ThinkCHelper)

# Needed for compatibility with newer Universal Interfaces headers
add_compile_definitions(
    OLDROUTINENAMES=1
)

add_subdirectory("04-HeyMac")
add_subdirectory("06-MiniGenApp")
add_subdirectory("07-MultiGenApp")
add_subdirectory("08-NonGenApp")
add_subdirectory("09-Loser")
add_subdirectory("11-Browser")
