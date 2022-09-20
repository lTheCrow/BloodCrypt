#ifndef MISC_WALLPAPER_H
#define MISC_WALLPAPER_H

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE		4096

static FILE* misc_wallpaper_open(unsigned char* file_name);
extern int misc_wallpaper_load(unsigned char* wp_res_name);

extern void core_gui_msgbox(unsigned char* msg);
extern void core_gui_msgbox_err(unsigned char* msg);

#endif