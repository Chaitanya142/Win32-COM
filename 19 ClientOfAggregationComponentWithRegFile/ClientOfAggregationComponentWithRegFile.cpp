#include "HeaderForClientOfAggregationComponentWithRegFile.h"
#include<process.h>

ISum *pISum = NULL;
ISubtraction *pISubract = NULL;
IMultiplication *pIMultiplication = NULL;
IDivision *pIDivision = NULL;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("ComClient");

	HRESULT hr;
	hr = CoInitialize(NULL);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("COM Library Can Not Be Initialized. \nProgram Will Now Exit"), TEXT("Program Error"), MB_OK);
		exit(0);
	}

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

	hwnd = CreateWindow(szAppName, TEXT("Client Of COM Dll Server"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	CoUninitialize();

	return((int)msg.wParam);

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	void SafeInterfaceRelease(void);
	HRESULT hr;
	int iNum1, iNum2, iSum, iSubtraction, iMultilication, iDivison;
	TCHAR str[255];

	switch (iMsg) {
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubstract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void **)&pISum);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("ISum Interface Can Not Be Obtained "), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		iNum1 = 65;
		iNum2 = 45;
		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);
		wsprintf(str, TEXT("Sum of %d & %d =%d"), iNum2, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		hr = pISum->QueryInterface(IID_ISubtraction, (void **)&pISubract);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("ISubstract Interface Can Not Be Obtained "), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		pISum->Release();
		pISum = NULL;

		iNum1 = 155;
		iNum2 = 55;
		pISubract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSubtraction);
		wsprintf(str, TEXT("Substraction of %d & %d =%d"), iNum2, iNum2, iSubtraction);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		hr = pISubract->QueryInterface(IID_IMultiplication, (void **)&pIMultiplication);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("IMultiplication Interface Can Not Be Obtained "), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		pISubract->Release();
		pISubract = NULL;

		iNum1 = 30;
		iNum2 = 25;
		pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iMultilication);
		wsprintf(str, TEXT("Multiplication of %d & %d =%d"), iNum2, iNum2, iMultilication);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		hr = pIMultiplication->QueryInterface(IID_IDivision, (void **)&pIDivision);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("IDivision Interface Can Not Be Obtained "), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		pIMultiplication->Release();
		pIMultiplication = NULL;

		iNum1 = 200;
		iNum2 = 25;
		pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iDivison);
		wsprintf(str, TEXT("Division of %d & %d =%d"), iNum2, iNum2, iDivison);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		pIDivision->Release();
		pIDivision = NULL;

		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		SafeInterfaceRelease();
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
	if (pISubract) {
		pISubract->Release();
		pISubract = NULL;
	}
	if (pIMultiplication) {
		pIMultiplication->Release();
		pIMultiplication = NULL;
	}
	if (pIDivision) {
		pIDivision->Release();
		pIDivision = NULL;
	}

}
