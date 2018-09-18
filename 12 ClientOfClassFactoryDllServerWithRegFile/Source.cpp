#include<Windows.h>
#include"Header.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

ISum *pISum = NULL;

ISubract *pISubstract = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{

	WNDCLASSEX wndclassex;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("ComClient");
	HRESULT hr;


	hr = CoInitialize(NULL);

	if (FAILED(hr)) {
		MessageBox(NULL,TEXT("COM Library Can Not Be Initialized\nProgram Will Now Exit."),TEXT("Program Error"),MB_OK);
		exit(0);
	}


	wndclassex.cbClsExtra = 0;
	wndclassex.cbSize = sizeof(WNDCLASSEX);
	wndclassex.cbWndExtra = 0;
	wndclassex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclassex.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclassex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclassex.hInstance = hInstance;
	wndclassex.lpfnWndProc = WndProc;
	wndclassex.lpszClassName = AppName;
	wndclassex.lpszMenuName = NULL;
	wndclassex.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndclassex);

	hwnd = CreateWindow(AppName,TEXT("Clent Of COM Dll Server"),
		WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,
		NULL,hInstance,NULL
		);


	ShowWindow(hwnd,iCmdShow);

	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	CoUninitialize();
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {

	void SafeInterfaceRelease(void);

	HRESULT hr;
	int iNum1, iNum2, iSum;
	TCHAR str[255];


	switch (iMsg) {
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubstract, NULL, CLSCTX_INPROC_SERVER,
			IID_ISum, (void **)&pISum);

		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("ISum Interface Can Not Be Obtained"),
				TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}


		iNum1 = 55;
		iNum2 = 45;
		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);
		wsprintf(str, TEXT("Sum Of %d and %d = %d"), iNum1, iNum2, iSum);

		MessageBox(hwnd,str,TEXT("Result"),MB_OK);

		hr = pISum->QueryInterface(IID_ISub, (void **)&pISubstract);

		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("ISub Interface Can Not Be Obtained"),
				TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}


		pISum->Release();
		pISum = NULL;
		iNum1 = 155;
		iNum2 = 145;
		pISubstract->SubstractionOfTwoIntegers(iNum1, iNum2, &iSum);


		pISubstract->Release();
		pISubstract = NULL;
		wsprintf(str, TEXT("Substraction Of %d and %d = %d"), iNum1, iNum2, iSum);

		MessageBox(hwnd, str, TEXT("Result"), MB_OK);
		DestroyWindow(hwnd);
		

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));

}


void SafeInterfaceRelease(void) {
	if (pISum) {
		pISum->Release();
		pISum = NULL;
	}
	if (pISubstract) {
		pISubstract->Release();
		pISubstract = NULL;
	}
}