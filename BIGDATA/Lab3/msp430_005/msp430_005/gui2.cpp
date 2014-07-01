#include "gui2.h"

void processEvents(handle gadget)
{
	if (gadget != NULL)
	{
		//processEvents(windowHandle(gadget));
		MSG msg;
		HWND window = windowHandle(gadget);
		while(PeekMessage(&msg,window,0,0,PM_REMOVE))
		{ 
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void setWindowLargeIconOnce(handle gadget, char* filename)
{
	HICON myIcon;

	myIcon = (HICON)LoadImageA(NULL,filename,IMAGE_ICON,32,32,LR_LOADFROMFILE);

	SendMessage(windowHandle(gadget),WM_SETICON,ICON_BIG,(LPARAM)myIcon);
}