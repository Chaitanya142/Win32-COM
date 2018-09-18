#include <Windows.h>
#include "Header.h"

class CSumSubstract : public ISum, ISubract {
private:long m_cRef;
public:
	CSumSubstract(void);
	~CSumSubstract(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall SumOfTwoIntegers(int,int,int *);

	HRESULT __stdcall SubstractionOfTwoIntegers(int,int,int *);
};

class CSumSubstractClassFactory :public IClassFactory {
private:
	long m_cRef;
public:
	CSumSubstractClassFactory(void);
	~CSumSubstractClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown *,REFIID,void **);
	HRESULT __stdcall LockServer(BOOL);

};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
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

CSumSubstract::CSumSubstract(void)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumSubstract::~CSumSubstract(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT __stdcall CSumSubstract::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISub)
		*ppv = static_cast<ISubract *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return (S_OK);
}

ULONG __stdcall CSumSubstract::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG __stdcall CSumSubstract::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}

	return (m_cRef);
}

HRESULT __stdcall CSumSubstract::SumOfTwoIntegers(int num1, int num2, int * pSum)
{
	*pSum = num1 + num2;
	return (S_OK);
}

HRESULT __stdcall CSumSubstract::SubstractionOfTwoIntegers(int num1, int num2, int *pSubstract)
{
	*pSubstract = num1 - num2;
	return (S_OK);
}

CSumSubstractClassFactory::CSumSubstractClassFactory(void)
{
	m_cRef = 1;
}

CSumSubstractClassFactory::~CSumSubstractClassFactory(void)
{
}

HRESULT __stdcall CSumSubstractClassFactory::QueryInterface(REFIID riid, void **ppv)
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
	return (S_OK);
}

ULONG __stdcall CSumSubstractClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG __stdcall CSumSubstractClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return m_cRef;
}

HRESULT __stdcall CSumSubstractClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	CSumSubstract *pCSumSubstract = NULL;
	HRESULT hr;
	if (pUnkOuter != NULL) {
		return(CLASS_E_NOAGGREGATION);
	}
	pCSumSubstract = new CSumSubstract();

	if (pCSumSubstract == NULL)
		return(E_OUTOFMEMORY);

	hr = pCSumSubstract->QueryInterface(riid,ppv);
	pCSumSubstract->Release();

	return (hr);
}

HRESULT __stdcall CSumSubstractClassFactory::LockServer(BOOL fLock)
{

	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return (S_OK);
}


HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv) {
	CSumSubstractClassFactory *pCSumSubstractClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_SumSubstract)
		return(CLASS_E_CLASSNOTAVAILABLE);
	pCSumSubstractClassFactory = new CSumSubstractClassFactory;
	if (pCSumSubstractClassFactory == NULL)
		return(E_OUTOFMEMORY);
	hr = pCSumSubstractClassFactory->QueryInterface(riid, ppv);
	pCSumSubstractClassFactory->Release();
	return(hr);
}

HRESULT __stdcall DllCanUnloadNow(void) {
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}

