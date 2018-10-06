#include "AggregationOuterComponentWithRegFile.h"
#include "AggregationInnerComponentWithRegFile.h"

class CSumSubstract :public ISum, ISubtraction
{
private:
	long m_cRef;
	IUnknown *m_pIUnknownInner;
	IMultiplication*m_pIMultiplication;
	IDivision *m_pIDivision;
public:
	CSumSubstract(void);
	~CSumSubstract(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int *);

	HRESULT __stdcall InitializeInnerComponent(void);
};

class CSumSubtractionClassFactory :public IClassFactory {
private:
	long m_cRef;
public:
	CSumSubtractionClassFactory(void);
	~CSumSubtractionClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

long glNumberOfActiveComponent = 0;
long glNumberServerLocks = 0;

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:break;
	case DLL_PROCESS_DETACH:break;
	case DLL_THREAD_ATTACH:break;
	case DLL_THREAD_DETACH:break;
	}

	return(TRUE);
}

CSumSubstract::CSumSubstract(void)
{
	m_pIUnknownInner = NULL;
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponent);
}

CSumSubstract::~CSumSubstract(void)
{
	InterlockedDecrement(&glNumberOfActiveComponent);
	if (m_pIMultiplication) {
		m_pIMultiplication->Release();
		m_pIMultiplication == NULL;
	}
	if (m_pIDivision) {
		m_pIDivision->Release();
		m_pIDivision = NULL;
	}
	if (m_pIUnknownInner) {
		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;
	}
}

HRESULT __stdcall CSumSubstract::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISubtraction)
		*ppv = static_cast<ISubtraction *>(this);
	else if (riid == IID_IMultiplication)
		return(m_pIUnknownInner->QueryInterface(riid, ppv));
	else if(riid == IID_IDivision)
		return(m_pIUnknownInner->QueryInterface(riid, ppv));
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG __stdcall CSumSubstract::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG __stdcall CSumSubstract::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT __stdcall CSumSubstract::SumOfTwoIntegers(int num1, int num2, int * pSum)
{
	*pSum = num1 + num2;
	return (S_OK);
}

HRESULT __stdcall CSumSubstract::SubtractionOfTwoIntegers(int num1, int num2, int *pSubtraction)
{
	*pSubtraction = num1 - num2;
	return (S_OK);
}

HRESULT __stdcall CSumSubstract::InitializeInnerComponent(void)
{
	HRESULT hr;
	hr = CoCreateInstance(CLSID_MultiplicationDivision, reinterpret_cast<IUnknown *>(this), CLSCTX_INPROC_SERVER, IID_IUnknown, (void **)&m_pIUnknownInner);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("IUnknown Interface Can Not Be Obtained From Inner Component."), TEXT("ERROR"), MB_OK);
		return(E_FAIL);
	}
	hr = m_pIUnknownInner->QueryInterface(IID_IMultiplication, (void **)&m_pIMultiplication);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("IMUltiplication Interface Can Not Be Obtained From Inner Component."), TEXT("ERROR"), MB_OK);
		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;
		return(E_FAIL);
	}

	hr = m_pIUnknownInner->QueryInterface(IID_IDivision, (void **)&m_pIDivision);

	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("IDivision Interface Can Not Be Obtained From Inner Component."), TEXT("ERROR"), MB_OK);
		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;
		return(E_FAIL);
	}
	return(S_OK);
}

CSumSubtractionClassFactory::CSumSubtractionClassFactory(void)
{
	m_cRef = 1;
}

CSumSubtractionClassFactory::~CSumSubtractionClassFactory(void)
{
}

HRESULT __stdcall CSumSubtractionClassFactory::QueryInterface(REFIID riid, void **ppv)
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

ULONG __stdcall CSumSubtractionClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG __stdcall CSumSubtractionClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT __stdcall CSumSubtractionClassFactory::CreateInstance(IUnknown * pUnkOuter, REFIID riid, void **ppv)
{
	CSumSubstract *pCSumSubstract = NULL;
	HRESULT hr;
	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);
	pCSumSubstract = new CSumSubstract;

	if (pCSumSubstract == NULL)
		return(E_OUTOFMEMORY);

	hr = pCSumSubstract->InitializeInnerComponent();

	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("Failed To Initialize Inner Component."), TEXT("ERROR"), MB_OK);
		pCSumSubstract->Release();
		pCSumSubstract = NULL;
	}

	hr = pCSumSubstract->QueryInterface(riid,ppv);
	pCSumSubstract->Release();
	return (hr);
}

HRESULT __stdcall CSumSubtractionClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberServerLocks);
	else
		InterlockedDecrement(&glNumberServerLocks);
	return (S_OK);
}

HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv) {
	CSumSubtractionClassFactory *pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_SumSubstract)
		return(CLASS_E_CLASSNOTAVAILABLE);

	pCSumSubtractClassFactory = new CSumSubtractionClassFactory;

	if (pCSumSubtractClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();

	return(hr);
}

HRESULT __stdcall DllCanUnloadNow(void) {
	if (glNumberOfActiveComponent == 0 && glNumberServerLocks == 0)
		return(S_OK);
	else
		return(S_FALSE);
}

