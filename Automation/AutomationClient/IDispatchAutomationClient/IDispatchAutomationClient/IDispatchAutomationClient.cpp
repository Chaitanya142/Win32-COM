#include "AutomationServer.h"
//#include <vcclr.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//IMyMath *pIMyMath = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("ComClient");
	HRESULT hr;
	hr = CoInitialize(NULL);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Library Can Not Be Initialized\nProgram Will Now Exit."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	wndclass.cbClsExtra = NULL;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.cbWndExtra = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(AppName, TEXT("Client Of COM Dll Server IDispatch"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);

	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	CoUninitialize();
	return((int)msg.wParam);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	void ComErrorDescriptionString(HWND, HRESULT);
	//void SafeInterfaceRelease(void);
	//static TCHAR szFunctionName1[]="";
	//static TCHAR szFunctionName2[] = "";
	//wsprintf(szFunctionName1, "SumOfTwoIntegers");
	//wsprintf(szFunctionName2, "SubstractionOfTwoIntegers");
	//static OLECHAR *a = (OLECHAR *)szFunctionName1;
	static OLECHAR * szFunctionName1 = (OLECHAR *)L"SumOfTwoIntegers";
	static OLECHAR * szFunctionName2 = (OLECHAR *)L"SubstractionOfTwoIntegers";

	//MessageBox(hwnd, (LPCTSTR)szFunctionName2, TEXT("COM Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);

	IDispatch *pIDispatch = NULL;
	HRESULT hr;
	DISPID dispid;
	VARIANT vArg[2], vRet;
	DISPPARAMS param = {vArg, 0, 2, NULL};

	//WCHAR* szFunctionName1 = TEXT("SumOfTwoIntegers");//PtrToStringChars("SumOfTwoIntegers");

	int iNum1, iNum2;//, iSum, iSubstraction;
	TCHAR str[255];

	switch (iMsg) {
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_MyMath, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void **)&pIDispatch);
		if (FAILED(hr)) {
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Component Can Not Be Created"), TEXT("COM Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			DestroyWindow(hwnd);
			exit(0);
		}

		iNum1 = 155;
		iNum2 = 145;

		//pIMyMath->SumOfTwoIntegers(iNum1, iNum2, &iSum);
		VariantInit(vArg);
		vArg[0].vt = VT_INT;
		vArg[0].intVal = iNum2;//Calling convention R to L
		vArg[1].vt = VT_INT;
		vArg[1].intVal = iNum1;
		param.cArgs = 2;
		param.cNamedArgs = 0;
		param.rgdispidNamedArgs = NULL;
		param.rgvarg = vArg;

		VariantInit(&vRet);

		hr = pIDispatch->GetIDsOfNames(IID_NULL, &szFunctionName1, 1, GetUserDefaultLCID(), &dispid);

		if (FAILED(hr)) {
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Can not get id for sum of two integers"), TEXT("Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}

		hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &param, &vRet, NULL, NULL);

		if (FAILED(hr)) {
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Can not invoke function"), TEXT("Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}
		else {
		wsprintf(str, TEXT("Sum of %d & %d =%d"), iNum1, iNum2, vRet.lVal);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);
		}

		hr = pIDispatch->GetIDsOfNames(IID_NULL, &szFunctionName2, 1, GetUserDefaultLCID(), &dispid);

		if (FAILED(hr)) {
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Can not get id for sub of two integers"), TEXT("Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}

		hr = pIDispatch->Invoke(dispid, IID_NULL, GetUserDefaultLCID(), DISPATCH_METHOD, &param, &vRet, NULL, NULL);

		if (FAILED(hr)) {
			ComErrorDescriptionString(hwnd, hr);
			MessageBox(hwnd, TEXT("Can not invoke function"), TEXT("Error"), MB_OK | MB_ICONERROR | MB_TOPMOST);
			pIDispatch->Release();
			DestroyWindow(hwnd);
		}
		else {
			wsprintf(str, TEXT("Substraction of %d & %d =%d"), iNum1, iNum2, vRet.lVal);
			MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);
		}



		//pIMyMath->SubstractionOfTwoIntegers(iNum1, iNum2, &iSubstraction);
		//wsprintf(str, TEXT("Substraction of %d & %d =%d"), iNum2, iNum2, iSubstraction);
		//MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		//pIMyMath->Release();
		//pIMyMath = NULL;


		VariantClear(vArg);
		VariantClear(&vRet);
		pIDispatch->Release();
		pIDispatch = NULL;
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		//SafeInterfaceRelease();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
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

//void SafeInterfaceRelease(void) {
//	if (pIMyMath) {
//		pIMyMath->Release();
//		pIMyMath = NULL;
//	}
//}
