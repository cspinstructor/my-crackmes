#include <Windows.h>
#include "resource.h"

//page 40 HNP book

BOOL CALLBACK Callback(HWND, UINT, WPARAM, LPARAM);
HWND hDlg;

BOOL isRegistered = false;


int WINAPI
WinMain(HINSTANCE h, HINSTANCE p, LPSTR s, int n)
{
	hDlg = CreateDialog(h, MAKEINTRESOURCE(IDD_DIALOG1), 0, Callback);
	if (!isRegistered) {
		MessageBox(0, "I am a nag screen\nPlease remove me.", "Opening Nag", MB_OK);
	}
	ShowWindow(hDlg, SW_SHOWDEFAULT);
	
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))//0 is WM_QUIT
	{
		if (!IsDialogMessage(hDlg, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}

BOOL CALLBACK Callback(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char szIP[48] = { 0 };

	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		
		case IDABOUT:
			if (isRegistered) {
				MessageBox(0, "Status:\n\nREGISTERED", "About", MB_OK);
			}
			else {
				MessageBox(0, "Status:\n\nUnregistered\n\nPlease register me", "About", MB_OK);
			}

			break;
		case IDCANCEL:
			ShowWindow(hDlg, SW_HIDE);
			MessageBox(0, "I am a nag screen\nPlease remove me.", "Closing Nag", MB_OK);
			PostQuitMessage(0);
		}
		break;
	}
	return 0;
}



