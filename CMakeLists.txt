cmake_minimum_required(VERSION 3.10)

project(BloodCrypt)

find_library(USER32 user32)
list(APPEND USBHID_LIB_DEPS ${USER32})

add_subdirectory(misc)

# entry point
add_subdirectory(core)