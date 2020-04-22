#include <Windows.h>
#include "resource.h"

//-- https://www.unknowncheats.me/forum/c-and-c-/84146-tls-callback-tutorial.html

// tls declaration
void NTAPI TLSCallbacks(PVOID DllHandle, DWORD dwReason, PVOID Reserved)
{
	MessageBox(0, "TLS Callback before main :)", "Debugger Owned!", 0);
	ExitProcess(0);
}
// end declaration

//linker spec
#ifdef _M_IX86
#pragma comment (linker, "/INCLUDE:__tls_used")
#pragma comment (linker, "/INCLUDE:__xl_b")
#else
#pragma comment (linker, "/INCLUDE:_tls_used")
#pragma comment (linker, "/INCLUDE:_xl_b")
#endif
#ifdef _M_X64
#pragma const_seg (".CRT$XLB")
const
#else
#pragma data_seg (".CRT$XLB")
#endif
//end linker


//tls import
EXTERN_C PIMAGE_TLS_CALLBACK _xl_b = TLSCallbacks;
#pragma data_seg ()
#pragma const_seg ()
//end 

BOOL CALLBACK Callback(HWND, UINT, WPARAM, LPARAM);
HWND hDlg;

char outputStr[64] = { 0 };

int WINAPI
WinMain(HINSTANCE h, HINSTANCE p, LPSTR s, int n)
{
	hDlg = CreateDialog(h, MAKEINTRESOURCE(IDD_DIALOG1), 0, Callback);

	//wsprintf(outputStr, "ret value: %d\n", r);
	//OutputDebugString(outputStr);

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
		case ID_ABOUT:
			MessageBox(0, "Coded by\ncrackinglessons.com", "About", MB_OK);
			break;
		case IDCANCEL:
			PostQuitMessage(0);
		}
		break;
	}
	return 0;
}
