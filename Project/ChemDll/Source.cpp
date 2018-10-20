#include "ChemDllHeader.h"

class CGayLussacsLawCalculator :public ICIP, ICIT, ICFP, ICFT {
private:
	long m_cRef;
public:
	CGayLussacsLawCalculator();
	~CGayLussacsLawCalculator();

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CalculateInitialPressure(double *, double, double, double );
	HRESULT __stdcall CalculateInitialTemp(double, double *, double, double );
	HRESULT __stdcall CalculateFinalPressure(double, double, double *, double);
	HRESULT __stdcall CalculateFinalTemp(double, double, double, double *);
};


class CGayLussacsLawCalculatorClassFactory :public IClassFactory {
private:
	long m_cRef;
public:
	CGayLussacsLawCalculatorClassFactory(void);
	~CGayLussacsLawCalculatorClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);

};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;
HMODULE ghModule;

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		ghModule = hDll;
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
}

CGayLussacsLawCalculator::CGayLussacsLawCalculator()
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CGayLussacsLawCalculator::~CGayLussacsLawCalculator()
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT __stdcall CGayLussacsLawCalculator::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ICIP*>(this);
	else if (riid == IID_ICIP)
		*ppv = static_cast<ICIP*>(this);
	else if (riid == IID_ICIT)
		*ppv = static_cast<ICIT*>(this);
	else if (riid == IID_ICFP)
		*ppv = static_cast<ICFP *>(this);
	else if (riid == IID_ICFT)
		*ppv = static_cast<ICFT *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG __stdcall CGayLussacsLawCalculator::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG __stdcall CGayLussacsLawCalculator::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return (m_cRef);
}

HRESULT __stdcall CGayLussacsLawCalculator::CalculateInitialPressure(double * Pi, double Ti, double Pf, double Tf)
{
	*Pi = Pf * Ti / Tf;
	return(S_OK);
}

HRESULT __stdcall CGayLussacsLawCalculator::CalculateInitialTemp(double Pi, double *Ti, double Pf, double Tf)
{
	*Ti = Pi * Tf / Pf;
	return (S_OK);
}

HRESULT __stdcall CGayLussacsLawCalculator::CalculateFinalPressure(double Pi, double Ti, double * Pf, double Tf)
{
	*Pf = Pi *Tf/ Ti;
	return (S_OK);
}

HRESULT __stdcall CGayLussacsLawCalculator::CalculateFinalTemp(double Pi, double Ti, double Pf, double *Tf)
{
	*Tf=Pf * Ti / Pi;
	return (S_OK);
}

CGayLussacsLawCalculatorClassFactory::CGayLussacsLawCalculatorClassFactory(void)
{
	m_cRef = 1;
}

CGayLussacsLawCalculatorClassFactory::~CGayLussacsLawCalculatorClassFactory(void)
{
}

HRESULT __stdcall CGayLussacsLawCalculatorClassFactory::QueryInterface(REFIID riid, void ** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if(riid==IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else {
		
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(this)->AddRef();
	return(S_OK);
}

ULONG __stdcall CGayLussacsLawCalculatorClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG __stdcall CGayLussacsLawCalculatorClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return m_cRef;
}

HRESULT __stdcall CGayLussacsLawCalculatorClassFactory::CreateInstance(IUnknown * pUnkOuter, REFIID riid, void **ppv)
{
	CGayLussacsLawCalculator * pCGayLussacsLawCalculator;
	HRESULT hr;
	if (pUnkOuter != NULL)
		return (CLASS_E_NOAGGREGATION);

	pCGayLussacsLawCalculator = new CGayLussacsLawCalculator();
	if (pCGayLussacsLawCalculator == NULL)
		return(E_OUTOFMEMORY);

	hr = pCGayLussacsLawCalculator->QueryInterface(riid, ppv);
	pCGayLussacsLawCalculator->Release();

	return(hr);
}

HRESULT __stdcall CGayLussacsLawCalculatorClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}

HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv) {
	CGayLussacsLawCalculatorClassFactory *pCGayLussacsLawCalculatorClassFactory = NULL;
	HRESULT hr;
	
	if (rclsid != CLSID_GayLussacsLawCalculator)
		return (CLASS_E_CLASSNOTAVAILABLE);

	pCGayLussacsLawCalculatorClassFactory = new CGayLussacsLawCalculatorClassFactory();
	
	if (pCGayLussacsLawCalculatorClassFactory == NULL)
		return(E_OUTOFMEMORY);
	
	hr = pCGayLussacsLawCalculatorClassFactory->QueryInterface(riid, ppv);
	pCGayLussacsLawCalculatorClassFactory->Release();

	return(hr);
}

HRESULT __stdcall DllCanUnloadNow(void) {
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}


STDAPI DllRegisterServer() {

	//MessageBox(NULL, "1", "E", MB_OK);
	HKEY hCLSIDKey = NULL,hInProcSvrKey=NULL;
	LONG lRet;
	TCHAR szModulePath[MAX_PATH];
	TCHAR szClassDescription[] = TEXT("Chem COM Dll");
	TCHAR szThreadingModel[] = TEXT("Apartment");
	__try {
		lRet = RegCreateKeyEx(HKEY_CLASSES_ROOT, TEXT("CLSID\\{B8A96FF5-94C9-43FD-911C-D2C5E582C1E6}"), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE | KEY_CREATE_SUB_KEY, NULL, &hCLSIDKey, NULL);
		
		if (ERROR_SUCCESS != lRet)
			return HRESULT_FROM_WIN32(lRet);
		
		lRet = RegSetValueEx(hCLSIDKey,NULL,0,REG_SZ,(const BYTE *)szClassDescription,sizeof(szClassDescription));

		if(ERROR_SUCCESS != lRet)
			return HRESULT_FROM_WIN32(lRet);

		lRet = RegCreateKeyEx(hCLSIDKey, TEXT("InProcServer32"), 0, NULL, REG_OPTION_VOLATILE, KEY_SET_VALUE, NULL, &hInProcSvrKey, NULL);

		if(ERROR_SUCCESS !=lRet)
			return HRESULT_FROM_WIN32(lRet);

		GetModuleFileName(ghModule, szModulePath, MAX_PATH);

		lRet = RegSetValueEx(hInProcSvrKey,NULL,0,REG_SZ,(const BYTE *)szModulePath,sizeof(TCHAR)* (lstrlen(szModulePath)+1));

		if(ERROR_SUCCESS != lRet)
			return HRESULT_FROM_WIN32(lRet);

		lRet = RegSetValueEx(hInProcSvrKey, TEXT("ThreadingModel"), 0, REG_SZ, (const BYTE *)szThreadingModel, sizeof(szThreadingModel));

		if (ERROR_SUCCESS != lRet)
			return HRESULT_FROM_WIN32(lRet);
	}
	__finally {
		if (NULL != hCLSIDKey)
			RegCloseKey(hCLSIDKey);
		if (NULL != hInProcSvrKey)
			RegCloseKey(hInProcSvrKey);
	}

	return(S_OK);
}


STDAPI DllUnregisterServer() {
	RegDeleteKey(HKEY_CLASSES_ROOT,TEXT("CLSID\\{B8A96FF5-94C9-43FD-911C-D2C5E582C1E6}\\InProcServer32"));
	RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CLSID\\{B8A96FF5-94C9-43FD-911C-D2C5E582C1E6}"));
	return S_OK;
}
