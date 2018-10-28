#include "AutomationServer.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

IMyMath *pIMyMath = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("ComClient");
	HRESULT hr;
	hr = CoInitialize(NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL,TEXT("COM Library Can Not Be Initialized\nProgram Will Now Exit."),TEXT("Program Error"),MB_OK);
		exit(0);
	}

	wndclass.cbClsExtra = NULL;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.cbWndExtra = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hIconSm= LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(AppName,TEXT("Client Of COM Dll Server"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	
	ShowWindow(hwnd,nCmdShow);

	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	CoUninitialize();
	return((int)msg.wParam);

}

LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam) {
	void ComErrorDescriptionString(HWND,HRESULT);
	void SafeInterfaceRelease(void);

	HRESULT hr;
	int iNum1,iNum2, iSum, iSubstraction;
	TCHAR str[255];

	switch (iMsg) {
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_MyMath,NULL,CLSCTX_INPROC_SERVER,IID_IMyMath,(void **)&pIMyMath);
		if (FAILED(hr)) {
			ComErrorDescriptionString(hwnd,hr);
			DestroyWindow(hwnd);
		}
		iNum1 = 155;
		iNum2 = 145;

		pIMyMath->SumOfTwoIntegers(iNum1,iNum2,&iSum);

		wsprintf(str, TEXT("Sum of %d & %d =%d"), iNum2, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		pIMyMath->SubstractionOfTwoIntegers(iNum1,iNum2,&iSubstraction);
		wsprintf(str, TEXT("Substraction of %d & %d =%d"), iNum2, iNum2, iSubstraction);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		pIMyMath->Release();
		pIMyMath = NULL;
		DestroyWindow(hwnd);

		break;
	case WM_DESTROY:
		SafeInterfaceRelease();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd,iMsg,wParam,lParam);
}


void ComErrorDescriptionString(HWND hwnd, HRESULT hr) {
	TCHAR * szErrorMessage = NULL;

	TCHAR str[255];
	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);
	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&szErrorMessage, 0, NULL))
	{
		wsprintf(str, szErrorMessage);
		//swprintf_s(str1,255,"%#x : %s",hr,szErrorMessage,);
		LocalFree(szErrorMessage);
	}
	else
		wsprintf(str, szErrorMessage);
	//swprintf_s(str, TEXT("Could not find description for error # %#x"), hr);

	MessageBox(hwnd, str, TEXT("COM_EROOR"), MB_OK);
}

void SafeInterfaceRelease(void) {
	if (pIMyMath) {
		pIMyMath->Release();
		pIMyMath = NULL;
	}
}
