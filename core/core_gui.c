#include "core_gui.h"

void core_gui_msgbox(unsigned char* msg)
{
	MessageBoxA(NULL, msg, "Bloodcrypt", MB_OK);
}

void core_gui_msgbox_err(unsigned char* msg)
{
	MessageBoxA(NULL, msg, "Bloodcrypt", MB_ICONERROR);
}