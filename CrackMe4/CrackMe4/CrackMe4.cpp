#include <Windows.h>
#include "resource.h"


//page 40 HNP book
// http://zetcode.com/gui/winapi/datetime/  [ date functions ]

BOOL CALLBACK Callback(HWND, UINT, WPARAM, LPARAM);
HWND hDlg;

BOOL isRegistered = true;
SYSTEMTIME lt = { 0 };
char daysRemainStr[64] = { 0 };
int daysRemainingInt = 0;

int WINAPI
WinMain(HINSTANCE h, HINSTANCE p, LPSTR s, int n)
{
	hDlg = CreateDialog(h, MAKEINTRESOURCE(IDD_DIALOG1), 0, Callback);
	ShowWindow(hDlg, SW_SHOWNORMAL);
	GetLocalTime(&lt);
	
	daysRemainingInt = 30 - lt.wDay;
	if (daysRemainingInt <= 0) {
		SetDlgItemText(hDlg, IDC_STATIC, "Trial Period has expired");
	}
	else {
		wsprintf(daysRemainStr, "%d days trial period remaining\n", daysRemainingInt);
		SetDlgItemText(hDlg, IDC_STATIC, daysRemainStr);
	}
	
	MSG msg;
	
	while (GetMessage(&msg, hDlg, 0, 0))//0 is WM_QUIT
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
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_ABOUT:
			if (daysRemainingInt <= 0) {
				MessageBox(0, "Trial Period Has Expired", "About", MB_OK);
			}
			else {
				MessageBox(0, daysRemainStr, "About", MB_OK);
			}

			break;
		case IDCANCEL:
			PostQuitMessage(0);
			break;

		}
		break;

	}

	return 0;
}



