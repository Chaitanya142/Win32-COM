#include <Windows.h>
#include <tchar.h>
#include <string.h>
#include <string>

#include "MyResource.h"
#include "MyDlgResource.h"
#include "PCMBIcon.h"
#include "ChemDllHeader.h"

//#import "Math.tlb"
//#include "PhysicsDll.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int SplashScreen(HWND, HDC, HBITMAP);
BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
void EnableControls(HWND, int);
void FreeLibraries(HMODULE, HMODULE);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("PCMB");

	HRESULT hrCOM;
	hrCOM = CoInitialize(NULL);
	if (FAILED(hrCOM)) {
		MessageBox(NULL, TEXT("COM Library Can Not Be Initialized\nProgram Will Now Exit."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(PCMBICON));//LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(PCMBICON));

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("PCMB"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

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

static BOOL showSplashWindow;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static HBITMAP hBitMap;
	static HINSTANCE hInst;
	switch (iMsg) {
	case WM_CREATE:
		hInst = (HINSTANCE)((LPCREATESTRUCT)lParam)->hInstance;
		//DialogBox(hInst, "DATAENTRY", hwnd, (DLGPROC)MyDlgProc);
		hBitMap = LoadBitmap((HINSTANCE)(((LPCREATESTRUCT)lParam)->hInstance), MAKEINTRESOURCE(MY_BITMAP));
		showSplashWindow = true;
		break;
	case WM_PAINT:
		HDC hdc;
		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps);
		if (showSplashWindow)
			SplashScreen(hwnd, hdc, hBitMap);
		else
		{
			/*	RECT rc;
				HBRUSH hbrush;
				hbrush = CreateSolidBrush(RGB(0, 0, 0));
				SelectObject(hdc, hbrush);
				GetClientRect(hwnd, &rc);
				Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
				DeleteObject(hdc);
			*/
			DialogBox(hInst, "PCMB", hwnd, (DLGPROC)MyDlgProc);
		}
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 32://On Enter Key Press
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
	SetBkMode(hdc, TRANSPARENT);
	wsprintf(src, TEXT("Press Space Key To Continue"));

	TextOut(hdc, (rc.left + rc.right - (LONG)_tcslen(src) * 8) / 2, 5, src, (int)_tcslen(src));


	SelectObject(hdcBitMap, hdc);
	DeleteDC(hdcBitMap);
	return(0);
}



BOOL CALLBACK MyDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdcStatic;
	static HBRUSH BkColorBrush;
	TEXTMETRIC lptm;
	char Colors[13][15] = { "Black","Brown","Red","Orange","Yellow","Green","Blue","Violet","Grey","White","Gold","Silver" };
	char * FirstBandValue = new char[20];
	char * SecondBandValue = new char[20];
	char * ThirdBandValue = new char[20];
	char * FourthBandValue = new char[20];
	char *ResistanceValue = new char[50];
	char *TolerenceValue = new char[50];
	typedef char *(*pfnGetResistance)(char *, char *, char *);
	typedef char *(*GetTolerenceValue)(char *);
	static pfnGetResistance pfnGR = NULL;
	static GetTolerenceValue pfnTV = NULL;
	static HMODULE hLib = NULL;
	static HMODULE hLibChemDllClient = NULL;
	static HRESULT hrTempChem = NULL;
	typedef HRESULT(*pfnCalculateInitialPressure)(double *, double, double, double);
	typedef HRESULT(*pfnCalculateInitialTemp)(double, double *, double, double);
	typedef HRESULT(*pfnCalculateFinalPressure)(double, double, double *, double);
	typedef HRESULT(*pfnCalculateFinalTemp)(double, double, double, double *);
	static pfnCalculateInitialPressure pfnICIP;
	static pfnCalculateInitialTemp pfnICIT;
	static pfnCalculateFinalPressure pfnICFP;
	static pfnCalculateFinalTemp pfnICFT;
	HRESULT hrChemDll;
	static int iSelectedCBChem;
	static int iSelectedCBMath;
	static ICIP *pICIP = NULL;
	char * PIValue = new char[255];
	char * TIValue = new char[255];
	char * PFValue = new char[255];
	char * TFValue = new char[255];
	double PI;
	double TI;
	double PF;
	double TF;
	int noOfItemsInComboBox = 0;
	TCHAR ChemValue[] = "";
	char * ChemVal = new char[255];

	char ChemDropDownOptions[4][50] = { "Initial Pressure(Pi)","Initial Temprature(Ti)","Final Pressure(Pf)","Final Temprature(Tf)" };

	//static Math::IMathPtr Mathptr;
	char MathDropDownOption[3][5] = { "+","-","*" };
	char * tempMathValue = new char[255];
	double tempMath;
	static int tempIndex = 0;
	TCHAR tempMathVal[] = "";

	//static SAFEARRAYBOUND sab[2];
	//sab[0].cElements = 4;
	//sab[0].lLbound = 0;

	//sab[1].cElements = 4;
	//sab[1].lLbound = 0;
	//static SAFEARRAY* sa1 = SafeArrayCreate(VT_I4, 2, sab);
	//static SAFEARRAY* sa2 = SafeArrayCreate(VT_I4, 2, sab);
	//static SAFEARRAY* sa3;

	static HMODULE hLibMathDll = NULL;

	static double mathInputArray1[4][4];
	static double mathInputArray2[4][4];
	static double mathOutputtArray[4][4];

	typedef int(*pfnAdditionOfInt2DArray)(double[][4], double[][4], double[][4]);
	static pfnAdditionOfInt2DArray pfnAddition;

	typedef int(*pfnSubstractionOfInt2DArray)(double[][4], double[][4], double[][4]);
	static pfnSubstractionOfInt2DArray pfnSub;

	typedef int(*pfnMultiplicationOfInt2DArray)(double[][4], double[][4], double[][4]);
	static pfnMultiplicationOfInt2DArray pfnMult;

	static HRESULT hresultMathAns;

	switch (iMsg) {
	case WM_INITDIALOG:
		//		SetFocus(GetDlgItem(hDlg, ID_RBPHYSICS));
				//SendDlgItemMessage(hDlg, ID_CBFBC,BM_SETCHECK , BST_CHECKED, (LPARAM)(LPCTSTR)0);

		EnableControls(hDlg, 0);
		//		SendMessage(GetDlgItem(hDlg, ID_RBPHYSICS), BM_SETCHECK, BST_CHECKED, 1);
				//SendDlgItemMessage(hDlg, ID_RBMARRIED, BM_SETCHECK, 1, 0);
		BkColorBrush = CreateSolidBrush(RGB(100, 100, 100));
		break;

	case WM_PAINT:
		//HDC hdc;
		//PAINTSTRUCT ps;
		//RECT rc;
		//hdc = BeginPaint(hDlg, &ps);
		//GetClientRect(hDlg, &rc);
		////SetTextColor(hdc, RGB(0, 255, 0));
		////SetBkColor(hdc, RGB(100, 100, 100));
		////DrawText(hdc, str, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		////SetBkMode(hdc, TRANSPARENT);
		////GetTextMetrics(hdc, &lptm);
		////Rectangle(hdc, MulDiv(10, lptm.tmAveCharWidth, 4), MulDiv(15, lptm.tmHeight, 4), 100, 100);
		////Rectangle(hdc, 15, 60, 300, 585);
		////HBRUSH hbr=
		////FillRect(hdc,&rc, (HBRUSH)BkColorBrush);
		//RECT newRc;
		//newRc.left = 15;
		//newRc.right = 300;
		//newRc.top = 60;
		//newRc.bottom = 585;
		//FrameRect(hdc, &newRc, (HBRUSH)(COLOR_WINDOW + 1));
		///*SetTextColor(hdc, RGB(0, 0, 0));
		//wsprintf(str, TEXT("Resistor Color Code"));
		//TextOut(hdc, 20, 50, str, (int)_tcslen(str));*/

		//EndPaint(hDlg, &ps);

		break;

	case WM_CTLCOLORDLG:
		//hdcStatic = (HDC)wParam;

		//SetTextColor(hdcStatic, RGB(255, 255, 255));
		//SetBkColor(hdcStatic, RGB(100, 100,100));

		//if ((HWND)lParam == GetDlgItem(hDlg, ID_RBPHYSICS))
		//{
		//	// we're about to draw the static
		//	// set the text colour in (HDC)lParam
		//	SetBkMode((HDC)wParam, RGB(100, 100, 100));
		//	//SetTextColor((HDC)wParam, RGB(100, 100, 100));
		//	// NOTE: per documentation as pointed out by selbie, GetSolidBrush would leak a GDI handle.
		//	return (BOOL)BkColorBrush;
		//}
		return (INT_PTR)(BkColorBrush);
		break;

		/*case WM_CTLCOLORBTN:
			return (INT_PTR)(BkColorBrush);
			break;
	*/
	case WM_CTLCOLORSTATIC:
		hdcStatic = (HDC)wParam;
		SetBkColor(hdcStatic, RGB(100, 100, 100));
		SetTextColor(hdcStatic, RGB(0, 0, 0));
		return (INT_PTR)(BkColorBrush);

	case WM_CTLCOLOREDIT:
		hdcStatic = (HDC)wParam;
		SetBkColor(hdcStatic, RGB(100, 100, 100));
		SetTextColor(hdcStatic, RGB(255, 255, 255));
		return (INT_PTR)(BkColorBrush);

		/*case WM_CTLCOLORSCROLLBAR:
			hdcStatic = (HDC)wParam;
			SetBkColor(hdcStatic, RGB(100, 100, 100));
			SetTextColor(hdcStatic, RGB(255, 255, 255));
			return (INT_PTR)(BkColorBrush);*/

	case WM_CLOSE:
		DeleteObject(BkColorBrush);
		DestroyWindow(hDlg);
		hDlg = NULL;

		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {

			//case ID_PBCONTINUE:
			//EndDialog(hDlg, 0);
			//break;
		//case IDOK:
			/*GetDlgItemText(hDlg, ID_ETNAME, in.name, 50);
			GetDlgItemText(hDlg, ID_ETADDRESS, in.address, 50);
			in.age = GetDlgItemInt(hDlg, ID_ETAGE, NULL, TRUE);
			GetDlgItemText(hDlg, ID_ETSALRS, salrs, 50);
			GetDlgItemText(hDlg, ID_ETSALPS, salps, 50);
			in.sal = atoi(salrs) + (float)atoi(salps) / 100;
			in.mstatus = SendDlgItemMessage(hDlg, ID_RBMARRIED, BM_GETCHECK, 0, 0);
			EndDialog(hDlg, 0);
			*/
			//break;

		case ID_PBEXIT:
			EndDialog(hDlg, 0);
			break;

		case ID_PBPCAL:

			GetDlgItemText(hDlg, ID_CBFBC, FirstBandValue, 20);
			GetDlgItemText(hDlg, ID_CBSBC, SecondBandValue, 20);
			GetDlgItemText(hDlg, ID_CBTBC, ThirdBandValue, 20);
			GetDlgItemText(hDlg, ID_CBFTHBC, FourthBandValue, 20);

			/*sprintf_s(Value1, sizeof(GetDlgItemText(hDlg, ID_CB, buf, 9)), GetDlgItemText(hwnd, IDC_COMBO1, buf, 9));
			sprintf_s(Value2, sizeof(Value2), Value2);
			sprintf_s(Value3, sizeof("silver"), "silver");
			sprintf_s(Value4, sizeof("Gold"), "Gold");*/

			//ResistanceValue=GetResistance(FirstBandValue, SecondBandValue, ThirdBandValue);
			ResistanceValue = pfnGR(FirstBandValue, SecondBandValue, ThirdBandValue);

			SetDlgItemText(hDlg, ID_ETRES, ResistanceValue);


			//TolerenceValue = GetTolerenceValue(FourthBandValue);
			TolerenceValue = pfnTV(FourthBandValue);
			SetDlgItemText(hDlg, ID_ETTOL, TolerenceValue);

			break;

		case ID_RBPHYSICS:
			EnableControls(hDlg, ID_RBPHYSICS);
			FreeLibraries(hLib, hLibChemDllClient);
			/*FreeLibrary(hLib);
			FreeLibrary(hLibChemDllClient);
			*/
			hLib = LoadLibrary(TEXT("PhysicsDll.dll"));
			if (hLib == NULL) {
				MessageBox(hDlg, TEXT("Required DLL cannot be loaded"), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_TOPMOST);
				//DestroyWindow(hwnd);
			}
			pfnGR = (pfnGetResistance)GetProcAddress(hLib, "GetResistance");
			pfnTV = (GetTolerenceValue)GetProcAddress(hLib, "GetTolerenceValue");

			for (int i = 114; i < 122; i++)
				EnableWindow(GetDlgItem(hDlg, i), TRUE);

			noOfItemsInComboBox = SendDlgItemMessage(hDlg, ID_CBFBC, CB_GETCOUNT, (WPARAM)0, (LPARAM)0);
			if (noOfItemsInComboBox == 0)
				for (int i = 0; i < 12; i++) {
					if (i != 0 && i != 10 && i != 11)
						SendDlgItemMessage(hDlg, ID_CBFBC, CB_ADDSTRING, (WPARAM)0, (LPARAM)(LPCTSTR)Colors[i]);
				}

			SendDlgItemMessage(hDlg, ID_CBFBC, CB_SETCURSEL, (WPARAM)0, (LPARAM)(LPCTSTR)0);

			noOfItemsInComboBox = SendDlgItemMessage(hDlg, ID_CBSBC, CB_GETCOUNT, (WPARAM)0, (LPARAM)0);
			if (noOfItemsInComboBox == 0)
				for (int i = 0; i < 12; i++) {
					if (i != 10 && i != 11)
						SendDlgItemMessage(hDlg, ID_CBSBC, CB_ADDSTRING, (WPARAM)0, (LPARAM)(LPCTSTR)Colors[i]);
				}
			SendDlgItemMessage(hDlg, ID_CBSBC, CB_SETCURSEL, (WPARAM)0, (LPARAM)(LPCTSTR)0);

			noOfItemsInComboBox = SendDlgItemMessage(hDlg, ID_CBTBC, CB_GETCOUNT, (WPARAM)0, (LPARAM)0);
			if (noOfItemsInComboBox == 0)
				for (int i = 0; i < 12; i++) {
					SendDlgItemMessage(hDlg, ID_CBTBC, CB_ADDSTRING, (WPARAM)0, (LPARAM)(LPCTSTR)Colors[i]);
				}
			SendDlgItemMessage(hDlg, ID_CBTBC, CB_SETCURSEL, (WPARAM)0, (LPARAM)(LPCTSTR)0);

			noOfItemsInComboBox = SendDlgItemMessage(hDlg, ID_CBFTHBC, CB_GETCOUNT, (WPARAM)0, (LPARAM)0);
			if (noOfItemsInComboBox == 0)
				for (int i = 0; i < 12; i++) {
					if (i != 0 && i != 9)
						SendDlgItemMessage(hDlg, ID_CBFTHBC, CB_ADDSTRING, (WPARAM)0, (LPARAM)(LPCTSTR)Colors[i]);
				}
			SendDlgItemMessage(hDlg, ID_CBFTHBC, CB_SETCURSEL, (WPARAM)0, (LPARAM)(LPCTSTR)0);


			//		EnableWindow(GetDlgItem(hDlg, ID_ETRES),FALSE);
			//		EnableWindow(GetDlgItem(hDlg, ID_ETTOL), FALSE);

					/*int a=SendMessage(hDlg,
						CB_ADDSTRING,
						0,
						reinterpret_cast<LPARAM>((LPCTSTR)Colors[0]));
					*/

					/*for (int i = 0; i < 12; i++) {
						SendDlgItemMessage(hDlg, ID_LBSBC, LB_ADDSTRING, (WPARAM)0, (LPARAM)(LPCTSTR)Colors[i]);
					}
					break;*/
			break;



		case ID_PBPSUB:
			EnableControls(hDlg, 0);
			break;
		case ID_RBCHEMISTRY:
			EnableControls(hDlg, ID_RBCHEMISTRY);
			FreeLibraries(hLib, hLibChemDllClient);

			hLibChemDllClient = LoadLibrary(TEXT("ChemDllClient.dll"));
			if (hLibChemDllClient == NULL) {
				MessageBox(hDlg, TEXT("Required DLL cannot be loaded"), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_TOPMOST);
				//DestroyWindow(hwnd);
			}

			iSelectedCBChem = 0;
			//EnableWindow(GetDlgItem(hDlg, ID_ETPI), FALSE);
			noOfItemsInComboBox = SendDlgItemMessage(hDlg, ID_CBCHEM, CB_GETCOUNT, (WPARAM)0, (LPARAM)0);
			if (noOfItemsInComboBox == 0)
				for (int i = 0; i < 4; i++) {
					SendDlgItemMessage(hDlg, ID_CBCHEM, CB_ADDSTRING, (WPARAM)0, (LPARAM)(LPCTSTR)ChemDropDownOptions[i]);
				}
			SendDlgItemMessage(hDlg, ID_CBCHEM, CB_SETCURSEL, (WPARAM)0, (LPARAM)(LPCTSTR)0);
			SendDlgItemMessage(hDlg, ID_ETPI, EM_SETREADONLY, (WPARAM)TRUE, 0);
			SendDlgItemMessage(hDlg, ID_ETTI, EM_SETREADONLY, (WPARAM)FALSE, 0);
			SendDlgItemMessage(hDlg, ID_ETPF, EM_SETREADONLY, (WPARAM)FALSE, 0);
			SendDlgItemMessage(hDlg, ID_ETTF, EM_SETREADONLY, (WPARAM)FALSE, 0);

			/*hrChemDll = CoCreateInstance(CLSID_GayLussacsLawCalculator, NULL, CLSCTX_INPROC_SERVER, IID_ICIP, (void **)&pICIP);
			if (FAILED(hrChemDll)) {
				MessageBox(NULL, TEXT("ICIP Interface Can Not Be Obtained"),TEXT("ERROR"), MB_OK);
				DestroyWindow(hDlg);
			}*/


			break;

		case ID_CBCHEM:
			switch (HIWORD(wParam)) {
			case CBN_SELCHANGE:
				//MessageBox(hDlg, (LPSTR)LOWORD(wParam), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_TOPMOST);
				//GetDlgItemText(hDlg, ID_CBFBC, FirstBandValue, 20);
				//double iSelect = SendDlgItemMessage(hDlg, ID_CBCHEM, CB_GETCURSEL, (WPARAM)0, (LPARAM)0); //LOWORD(wParam);
				//char * tempString = new char[20];
				//sprintf_s(tempString, 20,"%.2f", iSelect);
				//TCHAR str[] = "";
				//wsprintf(str, tempString);
				//MessageBox(hDlg, str, TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_TOPMOST);
				iSelectedCBChem = SendDlgItemMessage(hDlg, ID_CBCHEM, CB_GETCURSEL, (WPARAM)0, (LPARAM)0); //LOWORD(wParam);
				for (int i = 123; i < 127; i++)
					EnableWindow(GetDlgItem(hDlg, i), TRUE);

				SendDlgItemMessage(hDlg, ID_ETPI, EM_SETREADONLY, (WPARAM)FALSE, 0);
				SendDlgItemMessage(hDlg, ID_ETTI, EM_SETREADONLY, (WPARAM)FALSE, 0);
				SendDlgItemMessage(hDlg, ID_ETPF, EM_SETREADONLY, (WPARAM)FALSE, 0);
				SendDlgItemMessage(hDlg, ID_ETTF, EM_SETREADONLY, (WPARAM)FALSE, 0);

				switch (iSelectedCBChem) {
				case 0:
					SendDlgItemMessage(hDlg, ID_ETPI, EM_SETREADONLY, (WPARAM)TRUE, 0);
					//set readonly
					//	EnableWindow(GetDlgItem(hDlg, ID_ETPI), FALSE);
					break;
				case 1:
					SendDlgItemMessage(hDlg, ID_ETTI, EM_SETREADONLY, (WPARAM)TRUE, 0);
					//	EnableWindow(GetDlgItem(hDlg, ID_ETTI), FALSE);
					break;
				case 2:
					SendDlgItemMessage(hDlg, ID_ETPF, EM_SETREADONLY, (WPARAM)TRUE, 0);
					//	EnableWindow(GetDlgItem(hDlg, ID_ETPF), FALSE);
					break;
				case 3:
					SendDlgItemMessage(hDlg, ID_ETTF, EM_SETREADONLY, (WPARAM)TRUE, 0);
					//	EnableWindow(GetDlgItem(hDlg, ID_ETTF), FALSE);
					break;

				}

				break;
			}
			break;


		case ID_PBCCAL:
			GetDlgItemText(hDlg, ID_ETPI, PIValue, 255);
			GetDlgItemText(hDlg, ID_ETTI, TIValue, 255);
			GetDlgItemText(hDlg, ID_ETPF, PFValue, 255);
			GetDlgItemText(hDlg, ID_ETTF, TFValue, 255);
			PI = atof(PIValue);
			TI = atof(TIValue);
			PF = atof(PFValue);
			TF = atof(TFValue);
			switch (iSelectedCBChem) {
			case 0:
				pfnICIP = (pfnCalculateInitialPressure)GetProcAddress(hLibChemDllClient, "CalculateInitialPressure");
				hrTempChem = pfnICIP(&PI, TI, PF, TF);

				sprintf_s(ChemVal, 255, "%.2f", PI);
				wsprintf(ChemValue, ChemVal);
				SetDlgItemText(hDlg, ID_ETPI, ChemValue);

				break;
			case 1:
				pfnICIT = (pfnCalculateInitialTemp)GetProcAddress(hLibChemDllClient, "CalculateInitialTemp");
				hrTempChem = pfnICIT(PI, &TI, PF, TF);

				sprintf_s(ChemVal, 255, "%.2f", TI);
				wsprintf(ChemValue, ChemVal);
				SetDlgItemText(hDlg, ID_ETTI, ChemValue);

				break;
			case 2:
				pfnICFP = (pfnCalculateFinalPressure)GetProcAddress(hLibChemDllClient, "CalculateFinalPressure");
				hrTempChem = pfnICFP(PI, TI, &PF, TF);
				sprintf_s(ChemVal, 255, "%.2f", PF);
				wsprintf(ChemValue, ChemVal);
				SetDlgItemText(hDlg, ID_ETPF, ChemValue);

				break;
			case 3:
				pfnICFT = (pfnCalculateFinalTemp)GetProcAddress(hLibChemDllClient, "CalculateFinalTemp");
				hrTempChem = pfnICFT(PI, TI, PF, &TF);
				sprintf_s(ChemVal, 255, "%.2f", TF);
				wsprintf(ChemValue, ChemVal);
				SetDlgItemText(hDlg, ID_ETTF, ChemValue);

				break;

			}


			break;

		case ID_RBMATH:
			hLibMathDll = LoadLibrary(TEXT("MathDllWrapper.dll"));


			EnableControls(hDlg, ID_RBMATH);
			//ptr.CreateInstance(L"{72FA7FF1-D5A8-435D-AB92-943154E55B09}");
//			Mathptr.CreateInstance(L"MathLib.Math");
			noOfItemsInComboBox = SendDlgItemMessage(hDlg, ID_CBMATHOPR, CB_GETCOUNT, (WPARAM)0, (LPARAM)0);
			if (noOfItemsInComboBox == 0)
				for (int i = 0; i < 3; i++) {
					SendDlgItemMessage(hDlg, ID_CBMATHOPR, CB_ADDSTRING, (WPARAM)0, (LPARAM)(LPCTSTR)MathDropDownOption[i]);
				}
			SendDlgItemMessage(hDlg, ID_CBMATHOPR, CB_SETCURSEL, (WPARAM)0, (LPARAM)(LPCTSTR)0);

			for (int i = 163; i < 179; i++) {
				SendDlgItemMessage(hDlg, i, EM_SETREADONLY, (WPARAM)TRUE, 0);
			}
			


			/*if (Mathptr != nullptr)
			{

			}
			catch (_com_error const & e)
			{
				std::wcout << (wchar_t*)e.ErrorMessage() << std::endl;
			}
*/
			break;

		case ID_PBMCAL:
			iSelectedCBMath = SendDlgItemMessage(hDlg, ID_CBMATHOPR, CB_GETCURSEL, (WPARAM)0, (LPARAM)0); //LOWORD(wParam);

			tempIndex = 131;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					GetDlgItemText(hDlg, tempIndex, tempMathValue, 255);
					tempMath = atof(tempMathValue);
					mathInputArray1[i][j] = tempMath;
					tempIndex++;
				}
			}
			tempIndex = 147;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					GetDlgItemText(hDlg, tempIndex, tempMathValue, 255);
					tempMath = atof(tempMathValue);
					mathInputArray2[i][j] = tempMath;
					tempIndex++;

				}
			}

			/*GetDlgItemText(hDlg, ID_ETPI, PIValue, 255);
			GetDlgItemText(hDlg, ID_ETTI, TIValue, 255);
			GetDlgItemText(hDlg, ID_ETPF, PFValue, 255);
			GetDlgItemText(hDlg, ID_ETTF, TFValue, 255);
			PI = atof(PIValue);
			TI = atof(TIValue);
			PF = atof(PFValue);
			TF = atof(TFValue);*/
			//SafeArrayDestroy(sa3);

			if (hLibMathDll != nullptr) {
				switch (iSelectedCBMath) {
				case 0:
					pfnAddition = (pfnAdditionOfInt2DArray)GetProcAddress(hLibMathDll, "AdditionOfInt2DArray");
					hresultMathAns = pfnAddition(mathInputArray1,mathInputArray2,mathOutputtArray);					
					break;
				case 1:
					pfnSub = (pfnSubstractionOfInt2DArray)GetProcAddress(hLibMathDll, "SubstractionOfInt2DArray");
					hresultMathAns = pfnSub(mathInputArray1, mathInputArray2, mathOutputtArray);
					break;
				case 2:
					pfnMult = (pfnMultiplicationOfInt2DArray)GetProcAddress(hLibMathDll, "MultiplicationOfInt2DArray");
					hresultMathAns = pfnMult(mathInputArray1, mathInputArray2, mathOutputtArray);
					break;
				}
				tempIndex = 163;
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						sprintf_s(tempMathValue, 255, "%.2f", mathOutputtArray[i][j]);
						wsprintf(tempMathVal, tempMathValue);
						SetDlgItemText(hDlg, tempIndex, tempMathVal);
						tempIndex++;
					}
				}
						
			}

			break;
		case ID_RBBIO:
			//Mathptr.Release();
			EnableControls(hDlg, ID_RBBIO);


			/*for(int i=114;i<122;i++)
				EnableWindow(GetDlgItem(hDlg, i), FALSE);
			break;*/

		}
		return(TRUE);
	}
	return(FALSE);
}

void EnableControls(HWND hDlg, int flag) {
	for (int i = 114; i < 182; i++)
		EnableWindow(GetDlgItem(hDlg, i), FALSE);

	switch (flag)
	{
	case ID_RBPHYSICS:
		for (int i = 114; i < 122; i++)
			EnableWindow(GetDlgItem(hDlg, i), TRUE);
		break;
	case ID_RBCHEMISTRY:
		for (int i = 122; i < 129; i++)
			EnableWindow(GetDlgItem(hDlg, i), TRUE);
		break;
	case ID_RBMATH:
		for (int i = 129; i < 182; i++)
			EnableWindow(GetDlgItem(hDlg, i), TRUE);
		break;
	default:
		break;
	}

}


void FreeLibraries(HMODULE hLibPhy, HMODULE hLibChem) {
	FreeLibrary(hLibPhy);
	FreeLibrary(hLibChem);
}