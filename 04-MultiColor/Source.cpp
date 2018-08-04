#include <Windows.h>

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

	hwnd = CreateWindow(szAppName, TEXT("Multi Color Display"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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
	static char PressedKey;
	switch (iMsg) {
	case WM_KEYDOWN:
		PressedKey = wParam;
		InvalidateRect(hwnd,NULL,true);
		break;
	case WM_PAINT:
		HDC hdc;
		PAINTSTRUCT ps;
		HBRUSH hbrush;
		hdc = BeginPaint(hwnd,&ps);
		RECT rc;
		switch (PressedKey)
		{
		case 'R':
			hbrush = CreateSolidBrush(RGB(255,0,0));
			break;
		case 'G':
			hbrush = CreateSolidBrush(RGB(0, 255, 0));
			break;
		case 'B':
			hbrush = CreateSolidBrush(RGB(0, 0, 255));
			break;
		case 'C':
			hbrush = CreateSolidBrush(RGB(0, 255, 255));
			break;
		case 'M':
			hbrush = CreateSolidBrush(RGB(255, 0, 255));
			break;
		case 'Y':
			hbrush = CreateSolidBrush(RGB(255, 255, 0));
			break;
		case 'W':
			hbrush = CreateSolidBrush(RGB(255, 255, 255));
			break;
		case 'K':
			hbrush = CreateSolidBrush(RGB(0, 0, 0));
			break;
		default:
			hbrush = CreateSolidBrush(RGB(128, 128, 128));

			break;
		}
		SelectObject(hdc,hbrush);
		GetClientRect(hwnd, &rc);
		Rectangle(hdc,rc.left,rc.top,rc.right,rc.bottom);
		DeleteObject(hdc);
		EndPaint(hwnd,&ps);
		break;
	case WM_DESTROY:PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}