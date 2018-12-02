#include<Windows.h>
#include <string>
#include<string.h>
#include <stdlib.h>
#include "Header.h"
#import "Math.tlb" 
#include"Release\math.tlh"

static Math::IMath *app;
CLSID clsidMath;

static SAFEARRAYBOUND sab[2];
static SAFEARRAY* sa1;
static SAFEARRAY* sa2;
static SAFEARRAY* sa3;

static HRESULT hr;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

extern "C" HRESULT AdditionOfInt2DArray(double arr1[][4], double arr2[][4], double arr3[][4]) {
	hr = CLSIDFromProgID(L"MathLib.Math", &clsidMath);
	hr = CoCreateInstance(clsidMath, NULL, CLSCTX_INPROC_SERVER, __uuidof(Math::IMath), (VOID**)&app);
	
	sab[0].cElements = 4;
	sab[0].lLbound = 0;
	sab[1].cElements = 4;
	sab[1].lLbound = 0;

	static SAFEARRAY* sa1 = SafeArrayCreate(VT_I4, 2, sab);
	static SAFEARRAY* sa2 = SafeArrayCreate(VT_I4, 2, sab);
	static SAFEARRAY* sa3 ;
	

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			LONG index[2] = { i, j };
			int value = arr1[i][j];
			SafeArrayPutElement(sa1, index, &value);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			LONG index[2] = { i, j };
			int value = arr2[i][j];
			SafeArrayPutElement(sa2, index, &value);
		}
	}

	sa3 = app->AdditionOfInt2DArray(sa1, sa2);

	VARTYPE vt;
	SafeArrayGetVartype(sa3, &vt);

	if (vt == VT_I4)
	{
		LONG begin[2]{ 0 };
		LONG end[2]{ 0 };

		SafeArrayGetLBound(sa3, 1, &begin[0]);
		SafeArrayGetLBound(sa3, 2, &begin[1]);
		SafeArrayGetUBound(sa3, 1, &end[0]);
		SafeArrayGetUBound(sa3, 2, &end[1]);

		for (LONG i = begin[0]; i <= end[0]; ++i)
		{
			for (LONG j = begin[1]; j <= end[1]; ++j)
			{
				LONG index[2]{ i,j };
				int v;
				SafeArrayGetElement(sa3, index, &v);
				arr3[i][j] = v;
			}
		}
	}
	app->Release();
	
	return hr;
}

extern "C" HRESULT SubstractionOfInt2DArray(double arr1[][4], double arr2[][4], double arr3[][4]) {
	hr = CLSIDFromProgID(L"MathLib.Math", &clsidMath);
	hr = CoCreateInstance(clsidMath, NULL, CLSCTX_INPROC_SERVER, __uuidof(Math::IMath), (VOID**)&app);

	sab[0].cElements = 4;
	sab[0].lLbound = 0;
	sab[1].cElements = 4;
	sab[1].lLbound = 0;

	static SAFEARRAY* sa1 = SafeArrayCreate(VT_I4, 2, sab);
	static SAFEARRAY* sa2 = SafeArrayCreate(VT_I4, 2, sab);
	static SAFEARRAY* sa3;


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			LONG index[2] = { i, j };
			int value = arr1[i][j];
			SafeArrayPutElement(sa1, index, &value);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			LONG index[2] = { i, j };
			int value = arr2[i][j];
			SafeArrayPutElement(sa2, index, &value);
		}
	}

	sa3 = app->SubstractionOfInt2DArray(sa1, sa2);

	VARTYPE vt;
	SafeArrayGetVartype(sa3, &vt);

	if (vt == VT_I4)
	{
		LONG begin[2]{ 0 };
		LONG end[2]{ 0 };

		SafeArrayGetLBound(sa3, 1, &begin[0]);
		SafeArrayGetLBound(sa3, 2, &begin[1]);
		SafeArrayGetUBound(sa3, 1, &end[0]);
		SafeArrayGetUBound(sa3, 2, &end[1]);

		for (LONG i = begin[0]; i <= end[0]; ++i)
		{
			for (LONG j = begin[1]; j <= end[1]; ++j)
			{
				LONG index[2]{ i,j };
				int v;
				SafeArrayGetElement(sa3, index, &v);
				arr3[i][j] = v;
			}
		}
	}
	app->Release();

	return hr;
}

extern "C" HRESULT MultiplicationOfInt2DArray(double arr1[][4], double arr2[][4], double arr3[][4]) {
	hr = CLSIDFromProgID(L"MathLib.Math", &clsidMath);
	hr = CoCreateInstance(clsidMath, NULL, CLSCTX_INPROC_SERVER, __uuidof(Math::IMath), (VOID**)&app);

	sab[0].cElements = 4;
	sab[0].lLbound = 0;
	sab[1].cElements = 4;
	sab[1].lLbound = 0;

	static SAFEARRAY* sa1 = SafeArrayCreate(VT_I4, 2, sab);
	static SAFEARRAY* sa2 = SafeArrayCreate(VT_I4, 2, sab);
	static SAFEARRAY* sa3;


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			LONG index[2] = { i, j };
			int value = arr1[i][j];
			SafeArrayPutElement(sa1, index, &value);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			LONG index[2] = { i, j };
			int value = arr2[i][j];
			SafeArrayPutElement(sa2, index, &value);
		}
	}

	sa3 = app->MultiplicationOfInt2DArray(sa1, sa2);

	VARTYPE vt;
	SafeArrayGetVartype(sa3, &vt);

	if (vt == VT_I4)
	{
		LONG begin[2]{ 0 };
		LONG end[2]{ 0 };

		SafeArrayGetLBound(sa3, 1, &begin[0]);
		SafeArrayGetLBound(sa3, 2, &begin[1]);
		SafeArrayGetUBound(sa3, 1, &end[0]);
		SafeArrayGetUBound(sa3, 2, &end[1]);

		for (LONG i = begin[0]; i <= end[0]; ++i)
		{
			for (LONG j = begin[1]; j <= end[1]; ++j)
			{
				LONG index[2]{ i,j };
				int v;
				SafeArrayGetElement(sa3, index, &v);
				arr3[i][j] = v;
			}
		}
	}
	app->Release();

	return hr;
}


