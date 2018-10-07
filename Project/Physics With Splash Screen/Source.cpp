#include <Windows.h>
#include <tchar.h>
#include <string.h>
#include <string>

#include "MyResource.h"
#include "MyDlgResource.h"
#include "PCMBIcon.h"
#include "PhysicsDll.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int SplashScreen(HWND, HDC, HBITMAP);
BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("PCMB");
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
	return((int)msg.wParam);

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static HBITMAP hBitMap;
	static BOOL showSplashWindow;
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
	char Colors[13][15] = { "Black","Brown","Red","Orange","Yellow","Green","Blue","Violet","Grey","White","Gold","Silver"};
	char * FirstBandValue = new char[20];
	char * SecondBandValue = new char[20];
	char * ThirdBandValue = new char[20];
	char * FourthBandValue = new char[20];
	char *ResistanceValue =new char[50];
	char *TolerenceValue = new char[50];

	switch (iMsg) {
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hDlg, ID_RBPHYSICS));
		//SendDlgItemMessage(hDlg, ID_CBFBC,BM_SETCHECK , BST_CHECKED, (LPARAM)(LPCTSTR)0);
		SendMessage(GetDlgItem(hDlg, ID_RBPHYSICS), BM_SETCHECK, BST_CHECKED, 1);
		//SendDlgItemMessage(hDlg, ID_RBMARRIED, BM_SETCHECK, 1, 0);
		BkColorBrush = CreateSolidBrush(RGB(100, 100, 100));
		break;

	case WM_PAINT:
		HDC hdc;
		PAINTSTRUCT ps;
		RECT rc;
		hdc = BeginPaint(hDlg, &ps);
		GetClientRect(hDlg, &rc);
		//SetTextColor(hdc, RGB(0, 255, 0));
		//SetBkColor(hdc, RGB(100, 100, 100));
		//DrawText(hdc, str, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//SetBkMode(hdc, TRANSPARENT);
		//GetTextMetrics(hdc, &lptm);
		//Rectangle(hdc, MulDiv(10, lptm.tmAveCharWidth, 4), MulDiv(15, lptm.tmHeight, 4), 100, 100);
		//Rectangle(hdc, 15, 60, 300, 585);
		//HBRUSH hbr=
		//FillRect(hdc,&rc, (HBRUSH)BkColorBrush);
		RECT newRc;
		newRc.left = 15;
		newRc.right = 300;
		newRc.top = 60;
		newRc.bottom = 585;
		FrameRect(hdc, &newRc, (HBRUSH)(COLOR_WINDOW + 1));
		/*SetTextColor(hdc, RGB(0, 0, 0));
		wsprintf(str, TEXT("Resistor Color Code"));
		TextOut(hdc, 20, 50, str, (int)_tcslen(str));*/

		EndPaint(hDlg, &ps);

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
		SetBkColor(hdcStatic, RGB(100,100,100));
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


		case IDOK:

			/*GetDlgItemText(hDlg, ID_ETNAME, in.name, 50);
			GetDlgItemText(hDlg, ID_ETADDRESS, in.address, 50);
			in.age = GetDlgItemInt(hDlg, ID_ETAGE, NULL, TRUE);
			GetDlgItemText(hDlg, ID_ETSALRS, salrs, 50);
			GetDlgItemText(hDlg, ID_ETSALPS, salps, 50);
			in.sal = atoi(salrs) + (float)atoi(salps) / 100;
			in.mstatus = SendDlgItemMessage(hDlg, ID_RBMARRIED, BM_GETCHECK, 0, 0);
			EndDialog(hDlg, 0);
			*/
			break;

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

			ResistanceValue=GetResistance(FirstBandValue, SecondBandValue, ThirdBandValue);
			SetDlgItemText(hDlg, ID_ETRES, ResistanceValue);
			
			
			TolerenceValue = GetTolerenceValue(FourthBandValue);
			SetDlgItemText(hDlg, ID_ETTOL, TolerenceValue);

			break;

		case ID_RBPHYSICS:
			for (int i = 114; i < 122; i++)
				EnableWindow(GetDlgItem(hDlg, i), TRUE);

			for (int i = 0; i < 12; i++) {
				if(i!=0 && i!=10 && i!=11)
				SendDlgItemMessage(hDlg, ID_CBFBC, CB_ADDSTRING, (WPARAM)0, (LPARAM)(LPCTSTR)Colors[i]);
			}
			SendDlgItemMessage(hDlg, ID_CBFBC, CB_SETCURSEL, (WPARAM)0, (LPARAM)(LPCTSTR)0);

			for (int i = 0; i < 12; i++) {
				if (i != 10 && i != 11)
				SendDlgItemMessage(hDlg, ID_CBSBC, CB_ADDSTRING, (WPARAM)0, (LPARAM)(LPCTSTR)Colors[i]);
			}
			SendDlgItemMessage(hDlg, ID_CBSBC, CB_SETCURSEL, (WPARAM)0, (LPARAM)(LPCTSTR)0);

			for (int i = 0; i < 12; i++) {
				SendDlgItemMessage(hDlg, ID_CBTBC, CB_ADDSTRING, (WPARAM)0, (LPARAM)(LPCTSTR)Colors[i]);
			}
			SendDlgItemMessage(hDlg, ID_CBTBC, CB_SETCURSEL, (WPARAM)0, (LPARAM)(LPCTSTR)0);

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
		case ID_RBCHEMISTRY:
		case ID_RBMATH:
		case ID_RBBIO:
			for(int i=114;i<122;i++)
				EnableWindow(GetDlgItem(hDlg, i), FALSE);
			break;
		}
		return(TRUE);
	}
	return(FALSE);
}

