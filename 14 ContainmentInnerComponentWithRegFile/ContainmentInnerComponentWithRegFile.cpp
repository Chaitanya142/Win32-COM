#include "ContainmentInnerComponentWithRegFile.h"

class CMultiplicationDivison : public IMultiplication, IDivision {
private:
	long m_cRef;
public:
	CMultiplicationDivison(void);
	~CMultiplicationDivison(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *);
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *);

};



class CMultiplicationDivisonClassFactory :public IClassFactory {
private:
	long m_cRef;

public:
	CMultiplicationDivisonClassFactory(void);
	~CMultiplicationDivisonClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);

};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;


BOOL WINAPI DllMain(HINSTANCE hdll, DWORD dwReason, LPVOID Reserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:break;
	case DLL_THREAD_ATTACH:break;
	case DLL_THREAD_DETACH:break;
	case DLL_PROCESS_DETACH:break;
	}
	return(TRUE);
}

CMultiplicationDivison::CMultiplicationDivison(void)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CMultiplicationDivison::~CMultiplicationDivison(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT __stdcall CMultiplicationDivison::QueryInterface(REFIID riid, void ** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMultiplication *>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication *>(this);
	else if (riid == IID_IDivison)
		*ppv = static_cast<IDivision *>(this);
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG __stdcall CMultiplicationDivison::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

ULONG __stdcall CMultiplicationDivison::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return (0);
	}
	return(m_cRef);
}

HRESULT __stdcall CMultiplicationDivison::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication)
{
	*pMultiplication = num1 * num2;
	return (S_OK);
}

HRESULT __stdcall CMultiplicationDivison::DivisionOfTwoIntegers(int num1, int num2, int *pDivision)
{
	*pDivision = num1 / num2;
	return (S_OK);
}

CMultiplicationDivisonClassFactory::CMultiplicationDivisonClassFactory(void)
{
	m_cRef = 1;
}

CMultiplicationDivisonClassFactory::~CMultiplicationDivisonClassFactory(void)
{
}

HRESULT __stdcall CMultiplicationDivisonClassFactory::QueryInterface(REFIID riid, void ** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG __stdcall CMultiplicationDivisonClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return m_cRef;
}

ULONG __stdcall CMultiplicationDivisonClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return (m_cRef);
}

HRESULT __stdcall CMultiplicationDivisonClassFactory::CreateInstance(IUnknown * pUnkOuter, REFIID riid, void ** ppv)
{
	CMultiplicationDivison *pCMultiplicationDivision = NULL;
	HRESULT hr;
	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);
	pCMultiplicationDivision = new CMultiplicationDivison;
	if (pCMultiplicationDivision == NULL)
		return(E_OUTOFMEMORY);

	hr = pCMultiplicationDivision->QueryInterface(riid, ppv);
	pCMultiplicationDivision->Release();

	return(hr);

}

HRESULT __stdcall CMultiplicationDivisonClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return (S_OK);

}

HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv) {

	CMultiplicationDivisonClassFactory *pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;
	if (rclsid != CLSID_MultiplicationDivision)
		return(CLASS_E_CLASSNOTAVAILABLE);
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisonClassFactory;
	if (pCMultiplicationDivisionClassFactory == NULL)
		return (E_OUTOFMEMORY);
	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
	pCMultiplicationDivisionClassFactory->Release();
	return(hr);
}


HRESULT __stdcall DllCanUnloadNow(void) {
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
		return(S_OK);
	else
		return(S_FALSE);
}

