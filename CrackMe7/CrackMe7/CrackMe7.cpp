#include <Windows.h>
#include "resource.h"

//page 40 HNP book

BOOL CALLBACK Callback(HWND, UINT, WPARAM, LPARAM);
HWND hDlg;
BOOL isRegistered = false;

int checkRegistration(int a, int c);
int doAssembly(int a, int c);
char outputStr[64] = { 0 };

int WINAPI
WinMain(HINSTANCE h, HINSTANCE p, LPSTR s, int n)
{
	hDlg = CreateDialog(h, MAKEINTRESOURCE(IDD_DIALOG1), 0, Callback);

	int r = checkRegistration(5,5);
	//wsprintf(outputStr, "ret value: %d\n", r);
	//OutputDebugString(outputStr);

	if (r!=0) {
		SetDlgItemText(hDlg, IDC_STATIC_STATUS, "Registered");
	}
	else {
		SetDlgItemText(hDlg, IDC_STATIC_STATUS, "Unregistered");
	}

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
	char szIP[48] = { 0 };

	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_ABOUT:
			MessageBox(0, "Coded by\ncrackinglessons.com", "About", MB_OK);
			break;
		case IDCANCEL:
			PostQuitMessage(0);
		}
		break;
	}
	return 0;
}

int checkRegistration(int a, int c) {
	return doAssembly(a, c);
}

int doAssembly(int a, int c) {
	__asm
	{
		mov eax, a;load first param
		mov ecx, c;load second param
		sub eax, ecx
		test eax, eax

		je label_exit
		mov eax, 2

		label_exit:
	}
}