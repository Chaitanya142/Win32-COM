#include <windows.h>
#include"resource1.h"
#include <string>
#include <tchar.h>

BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);

struct INPUT1 {
	char name[50], address[50];
	int age, mstatus;
	float sal;
};
INPUT1 in;
LRESULT  CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("Dialogue_Box");

	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(AppName, TEXT("Dialogue_Box"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);

	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HINSTANCE hInst;
	switch (iMsg) {
	case WM_CREATE:
		//hInst = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);//Not Working for x64
		hInst = (HINSTANCE)((LPCREATESTRUCT)lParam)->hInstance;
		DialogBox(hInst, "DATAENTRY", hwnd, (DLGPROC)MyDlgProc);
		break;

	case WM_PAINT:
		HDC hdc;
		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps);		
		SetBkColor(hdc, RGB(0, 0, 0));
		SetTextColor(hdc, RGB(0, 255, 0)); 
		TCHAR src[255];
		wsprintf(src, TEXT("Entered Data"));
		TextOut(hdc, 5, 5, src, (int)_tcslen(src));
		wsprintf(src, TEXT("Name: %s"), in.name);
		TextOut(hdc, 5, 30, src, (int)_tcslen(src));
		wsprintf(src, TEXT("Address: %s"), in.address);
		TextOut(hdc, 5, 55, src, (int)_tcslen(src));
		wsprintf(src, TEXT("Address: %d"), in.age);
		TextOut(hdc, 5, 80, src, (int)_tcslen(src));
		static float salary = (float)in.sal;
		sprintf_s(src, TEXT("Salary = %f"), salary);
		TextOut(hdc, 5, 105, src, (int)_tcslen(src));
		EndPaint(hwnd, &ps);
		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

BOOL CALLBACK MyDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	
	char salrs[6], salps[3];
	switch (iMsg) {
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hDlg, ID_ETNAME));
		SendDlgItemMessage(hDlg, ID_RBMARRIED, BM_SETCHECK, 1, 0);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_PBCONTINUE:
			//EndDialog(hDlg, 0);
			break;


		case IDOK:

			GetDlgItemText(hDlg, ID_ETNAME, in.name, 50);
			GetDlgItemText(hDlg, ID_ETADDRESS, in.address, 50);
			in.age = GetDlgItemInt(hDlg, ID_ETAGE, NULL, TRUE);
			GetDlgItemText(hDlg, ID_ETSALRS, salrs, 50);
			GetDlgItemText(hDlg, ID_ETSALPS, salps, 50);
			in.sal = atoi(salrs) + (float)atoi(salps) / 100;
			in.mstatus = SendDlgItemMessage(hDlg, ID_RBMARRIED, BM_GETCHECK, 0, 0);
			EndDialog(hDlg, 0);
			break;

		case IDCANCEL:
			EndDialog(hDlg, 0);
			break;

		}
		return(TRUE);
	}
	return(FALSE);
}

