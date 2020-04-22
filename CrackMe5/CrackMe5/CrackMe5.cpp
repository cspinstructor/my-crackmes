#include <Windows.h>
#include "resource.h"

//page 40 HNP book

BOOL CALLBACK Callback(HWND, UINT, WPARAM, LPARAM);
HWND hDlg;
SYSTEMTIME lt = { 0 };

int WINAPI
WinMain(HINSTANCE h, HINSTANCE p, LPSTR s, int n)
{
	hDlg = CreateDialog(h, MAKEINTRESOURCE(IDD_DIALOG1), 0, Callback);

	ShowWindow(hDlg, SW_SHOWNORMAL);
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
	char fname[48] = { 0 };
	char genRegStr[64] = { 0 };
	char serialKey[64] = { 0 };

	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_CHECK:
			GetDlgItemText(hDlg, IDC_EDIT_FNAME, fname, 48);
			GetDlgItemText(hDlg, IDC_EDIT_SERIAL, serialKey, 48);
			GetLocalTime(&lt);

			wsprintf(genRegStr, "%s-%d%d%d", fname, lt.wYear+1234, lt.wMonth, lt.wDay);
			OutputDebugString(genRegStr);
			if (strcmp(serialKey, genRegStr) == 0) {
				MessageBox(0, "Well done!", "Congrats!", MB_OK);
			}
			else {
				MessageBox(0, "Wrong serial key. Try again.", "Sorry", MB_OK);
			}

			break;
		case IDC_BUTTON_ABOUT:
			MessageBox(0, "Coded by\n crackinglessons.com", "About", MB_OK);
			break;
		case IDCANCEL:
			PostQuitMessage(0);
		}
		break;
	}
	return 0;
}

