#include<Windows.h>
#include <string>
#include<string.h>
#include <stdlib.h>
#include "ChemDllHeader.h"

HRESULT hr;
ICIP *pICIP;
ICIT *pICIT;
ICFP *pICFP;
ICFT *pICFT;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		hr = CoCreateInstance(CLSID_GayLussacsLawCalculator,NULL, CLSCTX_INPROC_SERVER, IID_ICIP, (void **)&pICIP);
		if (FAILED(hr)) {
			MessageBox(NULL, TEXT("ICIP Interface Can Not Be Obtained"), TEXT("ERROR"), MB_OK);
		}

		break;

	case DLL_THREAD_ATTACH:

		break;

	case DLL_THREAD_DETACH:
		pICIP->Release();
		pICIP = NULL;

		break;

	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;

}


extern "C" HRESULT CalculateInitialPressure(double * Pi, double Ti, double Pf, double Tf) {
	pICIP->CalculateInitialPressure(Pi,Ti,Pf,Tf);
	return hr;
}

extern "C" HRESULT CalculateInitialTemp(double Pi, double *Ti, double Pf, double Tf) {
	hr=pICIP->QueryInterface(IID_ICIT,(void**)&pICIT);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("ICIT Interface Can Not Be Obtained"), TEXT("ERROR"), MB_OK);
	}
	pICIT->CalculateInitialTemp(Pi, Ti, Pf, Tf);
	pICIT->Release();
	pICIT = NULL;
	return hr;
}

extern "C" HRESULT CalculateFinalPressure(double Pi, double Ti, double *Pf, double Tf) {
	hr = pICIP->QueryInterface(IID_ICFP, (void**)&pICFP);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("ICFP Interface Can Not Be Obtained"), TEXT("ERROR"), MB_OK);
	}
	pICFP->CalculateFinalPressure(Pi, Ti, Pf, Tf);
	pICFP->Release();
	pICFP = NULL;
	return hr;
}

extern "C" HRESULT CalculateFinalTemp(double Pi, double Ti, double Pf, double *Tf) {
	hr = pICIP->QueryInterface(IID_ICFT, (void**)&pICFT);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("ICFT Interface Can Not Be Obtained"), TEXT("ERROR"), MB_OK);
	}
	pICFT->CalculateFinalTemp(Pi, Ti, Pf, Tf);
	pICFT->Release();
	pICFT = NULL;
	return hr;
}

