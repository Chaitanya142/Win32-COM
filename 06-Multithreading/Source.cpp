#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND , UINT , WPARAM , LPARAM );

DWORD WINAPI MyThreadProcOne(LPVOID);
DWORD WINAPI MyThreadProcTwo(LPVOID);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow) {
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("Multithreading");

	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDI_HAND);
	wndclass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndclass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(AppName,"MultiThreading",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,NULL,NULL,hInstance,NULL);

	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg,NULL,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HANDLE hThread1 = NULL;
	HANDLE hThread2=NULL;
	switch(iMsg) {
	case WM_CREATE:
		hThread1 = CreateThread(NULL,0,MyThreadProcOne,(LPVOID)hwnd,0,NULL);
		if (hThread1 == NULL) {
			MessageBox(hwnd,"Thread1 Creation Failed","Error",MB_OK);
			DestroyWindow(hwnd);
		}

		hThread2 = CreateThread(NULL, 0, MyThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		if (hThread2 == NULL) {
			MessageBox(hwnd, "Thread2 Creation Failed", "Error", MB_OK);
			DestroyWindow(hwnd);
		}
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, "This is 4th thread", "Msg", MB_OK);

		break;
	case WM_DESTROY:
		CloseHandle(hThread1);
		CloseHandle(hThread1);

		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}


DWORD WINAPI MyThreadProcOne(LPVOID Param) {
	HDC hdc;
	int i;
	TCHAR src[255];
	hdc = GetDC((HWND)Param);
	SetBkColor(hdc,RGB(0,0,0));
	SetTextColor(hdc,RGB(0,255,0));
	for (i = 0; i < 32768; i++) {
		wsprintf(src,TEXT("Thread 1-> Increasing Order Output= %d"),i);
		TextOut(hdc,5,5,src,(int)_tcslen(src));
	}
	ReleaseDC((HWND)Param,hdc);
	return(0);
}



DWORD WINAPI MyThreadProcTwo(LPVOID Param) {
	HDC hdc;
	int i;
	TCHAR src[255];
	hdc = GetDC((HWND)Param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));
	for (i = 32767; i >= 0; i--) {
		wsprintf(src, TEXT("Thread 2-> Decreasing Order Output= %d"), i);
		TextOut(hdc, 5, 25, src, (int)_tcslen(src));
	}
	ReleaseDC((HWND)Param, hdc);
	return(0);
}