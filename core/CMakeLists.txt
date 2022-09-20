cmake_minimum_required(VERSION 3.10)

add_executable(BloodCrypt WIN32 
	blood.c
	blood.h 
	core_gui.c
	core_gui.h
	stdafx.h
	wallpaper.rc
)

target_link_libraries(BloodCrypt libmisc)