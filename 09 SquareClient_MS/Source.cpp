#include <Windows.h>
#include <tchar.h>
#include "MyDLL.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyAPP");
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("My Application"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static int no;
	static int squareNo;

	switch (iMsg) {
	case WM_PAINT:
		HDC hdc;
		
		TCHAR src[255];
		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps);
		SetBkColor(hdc, RGB(0, 0, 0));
		SetTextColor(hdc, RGB(0, 255, 0));
		
		wsprintf(src, TEXT("Enter number & press enter to get Square %d"),no);
		TextOut(hdc, 5, 5, src, (int)_tcslen(src));
		
		EndPaint(hwnd, &ps);
		break;
		case WM_KEYDOWN:
			TCHAR msgScr[255];
		switch (wParam)
		{
		case 13://On Enter Key Press
			squareNo = MakeSquare(no);		
			wsprintf(msgScr, TEXT("Square of %d is %d"), no,squareNo);
			MessageBox(hwnd, msgScr, "Square", MB_ICONINFORMATION | MB_TOPMOST | MB_OK);
			squareNo = 0;
			no = 0;
			InvalidateRect(hwnd, NULL, true);
			break;
		case 48:
		case 49:
		case 50:
		case 51:
		case 52:
		case 53:
		case 54:
		case 55:
		case 56:
		case 57:
			no = no * 10 + (wParam - 48);
			InvalidateRect(hwnd, NULL, true);
			break;
		case 96:
		case 97:
		case 98:
		case 99:
		case 100:
		case 101:
		case 102:
		case 103:
		case 104:
		case 105:
			no = no * 10 + (wParam - 96);
			InvalidateRect(hwnd, NULL, true);
			break;
		}

		break;
	case WM_DESTROY:PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
