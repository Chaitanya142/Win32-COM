#include "AggregationInnerComponentWithRegFile.h"

interface INoAggregationIUnkonwn {
	virtual HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void **) = 0;
	virtual ULONG __stdcall AddRef_NoAggregation(void) = 0;
	virtual ULONG __stdcall Release_NoAggregation(void) = 0;
};

class CMultiplicationDivision :public INoAggregationIUnkonwn, IMultiplication, IDivision
{
private:
	long m_cRef;
	IUnknown *m_pIUnkonwnOuter;
public:
	CMultiplicationDivision(IUnknown *);
	~CMultiplicationDivision(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void **);
	ULONG __stdcall AddRef_NoAggregation(void);
	ULONG __stdcall Release_NoAggregation(void);

	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *);
};


class CMultiplicationDivisionClassFactory :public IClassFactory {
private:
	long m_cRef;
public:
	CMultiplicationDivisionClassFactory(void);
	~CMultiplicationDivisionClassFactory(void);

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID Reserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:break;
	case DLL_PROCESS_DETACH:break;
	case DLL_THREAD_ATTACH:break;
	case DLL_THREAD_DETACH:break;
	}
	return (TRUE);
}

CMultiplicationDivision::CMultiplicationDivision(IUnknown * pIUnkownOuter)
{
	m_cRef = 1;
	if (pIUnkownOuter != NULL)
		m_pIUnkonwnOuter = pIUnkownOuter;
	else
		m_pIUnkonwnOuter = reinterpret_cast<IUnknown *>
		(static_cast<INoAggregationIUnkonwn *>(this));
}

CMultiplicationDivision::~CMultiplicationDivision(void)
{
	InterlockedIncrement(&glNumberOfActiveComponents);
}

HRESULT __stdcall CMultiplicationDivision::QueryInterface(REFIID riid, void **ppv)
{
	return (m_pIUnkonwnOuter->QueryInterface(riid, ppv));
}

ULONG __stdcall CMultiplicationDivision::AddRef(void)
{
	return (m_pIUnkonwnOuter->AddRef());
}

ULONG __stdcall CMultiplicationDivision::Release(void)
{
	return (m_pIUnkonwnOuter->Release());
}

HRESULT __stdcall CMultiplicationDivision::QueryInterface_NoAggregation(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<INoAggregationIUnkonwn *>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication *>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision *>(this);
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return (S_OK);
}

ULONG __stdcall CMultiplicationDivision::AddRef_NoAggregation(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG __stdcall CMultiplicationDivision::Release_NoAggregation(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT __stdcall CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication)
{
	*pMultiplication = num1 * num2;
	return (S_OK);
}

HRESULT __stdcall CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int * pDivision)
{
	*pDivision = num1 / num2;
	return (S_OK);
}

CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	m_cRef = 1;
}

CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{
}

HRESULT __stdcall CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(this)->AddRef();
	return (S_OK);
}

ULONG __stdcall CMultiplicationDivisionClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG __stdcall CMultiplicationDivisionClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}
HRESULT __stdcall CMultiplicationDivisionClassFactory::CreateInstance(IUnknown * pUnkOuter, REFIID riid, void ** ppv)
{
	CMultiplicationDivision *pCmultiplicationDivision = NULL;
	HRESULT hr;

	if ((pUnkOuter != NULL) && (riid != IID_IUnknown))
		return(CLASS_E_NOAGGREGATION);

	pCmultiplicationDivision = new CMultiplicationDivision(pUnkOuter);

	if (pCmultiplicationDivision == NULL)
		return(E_OUTOFMEMORY);

	hr = pCmultiplicationDivision->QueryInterface_NoAggregation(riid, ppv);
	pCmultiplicationDivision->Release_NoAggregation();

	return(hr);
}
HRESULT __stdcall CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}

HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	CMultiplicationDivisionClassFactory *pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_MultiplicationDivision)
		return(CLASS_E_CLASSNOTAVAILABLE);
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;

	if (pCMultiplicationDivisionClassFactory == NULL)
		return(E_OUTOFMEMORY);

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