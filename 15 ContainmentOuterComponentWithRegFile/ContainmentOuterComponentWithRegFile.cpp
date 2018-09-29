#include "ContainmentInnerComponentWithRegFile.h"
#include "ContainmentOuterComponentWithRegFile.h"

class CSumStract :public ISum, ISubstract, IMultiplication, IDivision {
private:
	long m_cRef;
	IMultiplication *m_pIMultiplication;
	IDivision *m_pIDivision;
public:
	CSumStract(void);
	~CSumStract(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall SumOfTwoIntegers(int, int, int *);
	HRESULT __stdcall SubstractionOfTwoIntegers(int, int, int*);
	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *);
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *);

	HRESULT __stdcall InititializeInnerComponent(void);

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

	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);

};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:break;
	case DLL_THREAD_ATTACH:break;
	case DLL_THREAD_DETACH:break;
	case DLL_PROCESS_DETACH:break;
	}
	return(TRUE);
}

CSumStract::CSumStract(void)
{
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CSumStract::~CSumStract(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
	if (m_pIMultiplication) {
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
	}
	if (m_pIDivision)
	{
		m_pIDivision->Release();
		m_pIDivision = NULL;
	}

}

HRESULT __stdcall CSumStract::QueryInterface(REFIID riid, void ** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISubstract)
		*ppv = static_cast<ISubstract *>(this);
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

ULONG __stdcall CSumStract::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG __stdcall CSumStract::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT __stdcall CSumStract::SumOfTwoIntegers(int num1, int num2, int * pSum)
{
	*pSum = num1 + num2;
	return (S_OK);
}

HRESULT __stdcall CSumStract::SubstractionOfTwoIntegers(int num1, int num2, int *pSub)
{
	*pSub = num1 - num2;
	return (S_OK);
}

HRESULT __stdcall CSumStract::MultiplicationOfTwoIntegers(int num1, int num2, int *pMul)
{
	m_pIMultiplication->MultiplicationOfTwoIntegers(num1,num2,pMul);
	return (S_OK);
}

HRESULT __stdcall CSumStract::DivisionOfTwoIntegers(int num1, int num2, int *pDiv)
{
	m_pIDivision->DivisionOfTwoIntegers(num1, num2, pDiv);
	return (S_OK);
}

HRESULT __stdcall CSumStract::InititializeInnerComponent(void)
{
	HRESULT hr;
	
	hr = CoCreateInstance(CLSID_MultiplicationDivision, NULL, CLSCTX_INPROC_SERVER, IID_IMultiplication, (void **)&m_pIMultiplication);

	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("IMultiplication Interface Can Not Be Obtained From Inner Component."), TEXT("ERROR"), MB_OK);
		return(E_FAIL);
	}
	
	hr = m_pIMultiplication->QueryInterface(IID_IDivison, (void **)&m_pIDivision);
	if (FAILED(hr)) {
		MessageBox(NULL,TEXT("IDivison Interface Can Not Be Obtained From Inner Component."),TEXT("ERROR"),MB_OK);
		return(E_FAIL);
	}
	return(S_OK);
}

CSumSubstractClassFactory::CSumSubstractClassFactory(void)
{
	m_cRef = 1;
}

CSumSubstractClassFactory::~CSumSubstractClassFactory(void)
{
}

HRESULT __stdcall CSumSubstractClassFactory::QueryInterface(REFIID riid, void ** ppv)
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

ULONG __stdcall CSumSubstractClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG __stdcall CSumSubstractClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT __stdcall CSumSubstractClassFactory::CreateInstance(IUnknown * pUnkOuter, REFIID riid, void ** ppv)
{
	CSumStract *pCSumSubstract = NULL;

	HRESULT hr;
	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	pCSumSubstract = new CSumStract;

	if (pCSumSubstract == NULL)
		return(E_OUTOFMEMORY);

	hr = pCSumSubstract->InititializeInnerComponent();

	if (FAILED(hr)) {
		MessageBox(NULL,TEXT("Failed To Initialize Inner Component"),TEXT("ERROR"),MB_OK);
		pCSumSubstract->Release();
		return(hr);
	}

	hr = pCSumSubstract->QueryInterface(riid,ppv);

	pCSumSubstract->Release();
	return(hr);
}

HRESULT __stdcall CSumSubstractClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);

	return(S_OK);
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
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
		return(S_OK);
	else 
		return(S_FALSE);
}

