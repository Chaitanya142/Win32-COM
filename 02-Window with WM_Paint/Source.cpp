#include <Windows.h>

LRESULT CALLBACK WndProc(HWND , UINT , WPARAM , LPARAM );

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("My Window");
	WNDCLASSEX wndclass;

	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL,IDC_HAND);
	wndclass.hIcon = LoadIcon(NULL,IDI_SHIELD);
	wndclass.hIconSm = LoadIcon(NULL, IDI_SHIELD);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(AppName,TEXT("My WIndow with WM_PAINT"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	
	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, hwnd, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	return ((int)msg.wParam);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static TCHAR str[] = "Hello World";
	switch (iMsg) {
	case WM_PAINT:
		HDC hdc;
		PAINTSTRUCT ps;
		RECT rc;
		hdc = BeginPaint(hwnd,&ps);
		GetClientRect(hwnd,&rc);
		SetTextColor(hdc, RGB(0, 255, 0));
		SetBkColor(hdc,RGB(0,0,0));
		DrawText(hdc, str, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}