#include <Windows.h>
#include "resource.h"


//page 40 HNP book

BOOL CALLBACK Callback(HWND, UINT, WPARAM, LPARAM);
HWND hDlg;
void openKeyFile();
#define BUFFERSIZE 32
char   ReadBuffer[BUFFERSIZE] = { 0 };
OVERLAPPED ol = { 0 };
BOOL isRegistered = false;
char regStr[64] = "Registered to: ";

BOOL bRet;

int WINAPI
WinMain(HINSTANCE h, HINSTANCE p, LPSTR s, int n)
{
	hDlg = CreateDialog(h, MAKEINTRESOURCE(IDD_DIALOG1), 0, Callback);
	ShowWindow(hDlg, SW_SHOWNORMAL);
	openKeyFile();
	MSG msg;
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	//while (GetMessage(&msg, hDlg, 0, 0))//0 is WM_QUIT
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
		case ID_OK:
			//openKeyFile();
			PostQuitMessage(0);
			//DestroyWindow(hDlg);
			break;
		case IDC_ABOUT:
			if (isRegistered) {
				MessageBox(0, regStr, "About", MB_OK);
			}
			else {
				MessageBox(0, "Unregistered software\nPlease crack me.", "Unregistered", MB_OK);
			}
			
			break;
		case IDCANCEL:
			PostQuitMessage(0);
			//DestroyWindow(hDlg);
			break;
		
		}
		break;
	
	}
	
	return 0;
}

void openKeyFile() {
	HANDLE hFile = CreateFile("keyfile.txt",               // file to open
		GENERIC_READ,          // open for reading
		FILE_SHARE_READ,       // share for reading
		NULL,                  // default security
		OPEN_EXISTING,         // existing file only
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, // normal file
		NULL);                 // no attr. template


	if (hFile == INVALID_HANDLE_VALUE)
	{
		//MessageBox(0, "Unable to open file", "Error", MB_OK);
		return;
	}
	else {
		if (FALSE == ReadFileEx(hFile, ReadBuffer, BUFFERSIZE - 1, &ol, NULL))
		{
			//MessageBox(0, "Unable to read file.", "Error", MB_OK);
			//CloseHandle(hFile);
			//return;
		}
		else {
			//MessageBox(0, "REad file successfully", "Read", MB_OK);
			isRegistered = true;
			
			strcat_s(regStr, ReadBuffer);
			SetDlgItemText(hDlg, IDC_STATIC, regStr);
		}
	}
	CloseHandle(hFile);
	return;
}

