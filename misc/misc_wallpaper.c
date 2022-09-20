#include "misc_wallpaper.h"
#include <string.h>

unsigned char file_path[BUFFER_SIZE];

static FILE* misc_wallpaper_open(unsigned char *file_name)
{
	GetTempPathA(BUFFER_SIZE, file_path);
	strcat(file_path, file_name);

	return fopen(file_path, "wb");
}

int misc_wallpaper_load(unsigned char *wp_res_name)
{

	HRSRC res_handle = FindResourceA(NULL, wp_res_name, RT_RCDATA);
	if (!res_handle) {
		core_gui_msgbox_err("Error Finding Resource");
		return EXIT_FAILURE;
	}
		

	HGLOBAL res = LoadResource(NULL, res_handle);
	if (!res) {
		core_gui_msgbox_err("Error Loading Resource");
		return EXIT_FAILURE;
	}
		

	unsigned long size = SizeofResource(NULL, res_handle);
	unsigned char* raw_data = (unsigned char*)LockResource(res);

	FILE *tmp_file = misc_wallpaper_open("wp.jpg");
	

	fwrite(raw_data, 1, size, tmp_file);
	fclose(tmp_file);

	
	SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (void*)file_path, SPIF_UPDATEINIFILE);
	
	//remove(file_path);
	memset(file_path, 0, BUFFER_SIZE);
}