#include <Windows.h>
#include <tchar.h>
#include "MyResource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int SplashScreen(HWND, HDC, HBITMAP);

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

	hwnd = CreateWindow(szAppName, TEXT("Science"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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
	static HBITMAP hBitMap;
	static BOOL showSplashWindow;
	switch (iMsg) {
	case WM_CREATE:
		hBitMap = LoadBitmap((HINSTANCE)(((LPCREATESTRUCT)lParam)->hInstance), MAKEINTRESOURCE(MY_BITMAP));
		showSplashWindow = true;
		break;
	case WM_PAINT:
		HDC hdc;
		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps);
		if(showSplashWindow)
		SplashScreen(hwnd, hdc, hBitMap);
		else
		{
			RECT rc;
			HBRUSH hbrush;
			hbrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hbrush);
			GetClientRect(hwnd, &rc);
			Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
			DeleteObject(hdc);
		}
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 13://On Enter Key Press
			if (showSplashWindow) {
				showSplashWindow = false;
				InvalidateRect(hwnd, NULL, true);
			}
			break;

		default:
			break;
		}

		break;

	case WM_DESTROY:
		DeleteObject(hBitMap);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}


int SplashScreen(HWND hwnd, HDC hdc, HBITMAP hBitMap) {
	HDC hdcBitMap;
	BITMAP bitMap;
	hdcBitMap = CreateCompatibleDC(hdc);

	if (!hdcBitMap)
	{
		MessageBox(hwnd, TEXT("CreateCompatibleDC has failed"), TEXT("Failed"), MB_OK);
		DestroyWindow(hwnd);

	}
	RECT rc;
	GetClientRect(hwnd, &rc);

	SelectObject(hdcBitMap, (HGDIOBJ)hBitMap);
	GetObject(hBitMap, sizeof(BITMAP), &bitMap);

	//if (!BitBlt(hdc,
	//	0, 0,
	//	rc.right - rc.left, rc.bottom - rc.top,
	//	hdcBitMap,
	//	0, 0,
	//	SRCCOPY))
	//{
	//	MessageBox(hwnd, TEXT("BitBLT has failed"), TEXT("Failed"), MB_OK);
	//		DestroyWindow(hwnd);
	//}
	if (!StretchBlt(hdc,
		0, 0,
		rc.right, rc.bottom,
		hdcBitMap,
		0, 0,
		bitMap.bmWidth,
		bitMap.bmHeight,
		SRCCOPY))
	{
		MessageBox(hwnd, TEXT("StretchBlt has failed"), TEXT("Failed"), MB_OK);
		DestroyWindow(hwnd);
	}

	TCHAR src[255];
	SetTextColor(hdc, RGB(255, 255, 0));
	SetBkMode(hdc,TRANSPARENT);
	wsprintf(src, TEXT("Press Enter Key To Continue"));

	TextOut(hdc, (rc.left + rc.right - (LONG)_tcslen(src)*8) / 2, 5, src, (int)_tcslen(src));
	
	
	SelectObject(hdcBitMap, hdc);
	DeleteDC(hdcBitMap);
	return(0);
}
