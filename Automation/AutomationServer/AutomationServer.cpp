
#include<string>
#include<string.h>
#include "AutomationServer.h"

class CMyMath :public IMyMath {
private:
	long m_cRef;
	ITypeInfo *m_pITypeInfo = NULL;
public:
	CMyMath(void);
	~CMyMath(void);

	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall GetTypeInfoCount(UINT *);
	HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo **);
	HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR *, UINT, LCID, DISPID*);
	HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);

	HRESULT __stdcall SumOfTwoIntegers(int,int,int *);
	HRESULT __stdcall SubstractionOfTwoIntegers(int,int,int*);

	HRESULT InitInstance(void);
};


class CMyMathClassFactory :public IClassFactory {
private:
	long m_cRef;
public:
	CMyMathClassFactory();
	~CMyMathClassFactory();

	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

HMODULE ghModule = NULL;

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

const GUID LIBID_AutomationServer=
// {6F32F998-A5C2-4260-8F0A-ACEBB81C3F9F}
{ 0x6f32f998, 0xa5c2, 0x4260, { 0x8f, 0xa, 0xac, 0xeb, 0xb8, 0x1c, 0x3f, 0x9f } };

BOOL WINAPI DllMain(HINSTANCE hDll,DWORD dwReason,LPVOID Reserved) {
	switch(dwReason){
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

CMyMath::CMyMath(void)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CMyMath::~CMyMath(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT __stdcall CMyMath::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMyMath*>(this);
	else if(riid==IID_IDispatch)
		*ppv = static_cast<IMyMath*>(this);
	else if(riid==IID_IMyMath)
		*ppv = static_cast<IMyMath*>(this);
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return (S_OK);
}

ULONG __stdcall CMyMath::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG __stdcall CMyMath::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		m_pITypeInfo->Release();
		m_pITypeInfo = NULL;
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT __stdcall CMyMath::GetTypeInfoCount(UINT * pCountTypeInfo)
{
	*pCountTypeInfo = 1;
	return (S_OK);
}

HRESULT __stdcall CMyMath::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo **ppITypeInfo)
{
	*ppITypeInfo = NULL;
	if (iTypeInfo != 0)
		return(DISP_E_BADINDEX);

	m_pITypeInfo->AddRef();
	*ppITypeInfo = m_pITypeInfo;

	return (S_OK);
}

HRESULT __stdcall CMyMath::GetIDsOfNames(REFIID riid, LPOLESTR * rgszNames, UINT cNames, LCID lcid, DISPID * rgDispId)
{
	return (DispGetIDsOfNames(m_pITypeInfo,rgszNames,cNames,rgDispId));
}

HRESULT __stdcall CMyMath::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT * puArgErr)
{
	HRESULT hr;
	hr = DispInvoke(this,m_pITypeInfo,dispIdMember,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr);
	return (hr);
}

HRESULT __stdcall CMyMath::SumOfTwoIntegers(int num1, int num2, int *pSum)
{
	*pSum = num1 + num2;
	return (S_OK);
}

HRESULT __stdcall CMyMath::SubstractionOfTwoIntegers(int num1, int num2, int *pSub)
{
	*pSub = num1 - num2;
	return (S_OK);
}

HRESULT CMyMath::InitInstance(void)
{
	void ComErrorDescriptionString(HWND,HRESULT);

	HRESULT hr;
	ITypeLib *pITypeLib = NULL;

	if (m_pITypeInfo == NULL)
	{
		hr = LoadRegTypeLib(LIBID_AutomationServer, 1, 0, 0x00, &pITypeLib);
		if (FAILED(hr)) {
			ComErrorDescriptionString(NULL,hr);
			return(hr);
		}
		hr = pITypeLib->GetTypeInfoOfGuid(IID_IMyMath,&m_pITypeInfo);

		if (FAILED(hr)) {
			ComErrorDescriptionString(NULL, hr);
			pITypeLib->Release();
			return(hr);
		}
		pITypeLib->Release();
	}
	return(S_OK);
}

CMyMathClassFactory::CMyMathClassFactory()
{
	m_cRef = 1;
}

CMyMathClassFactory::~CMyMathClassFactory()
{
}

HRESULT __stdcall CMyMathClassFactory::QueryInterface(REFIID riid, void ** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if(riid==IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return (S_OK);
}

ULONG __stdcall CMyMathClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG __stdcall CMyMathClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0) {
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT __stdcall CMyMathClassFactory::CreateInstance(IUnknown * pUnkOuter, REFIID riid, void **ppv)
{
	CMyMath *pCMyMath = NULL;
	HRESULT hr;
	
	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	pCMyMath = new CMyMath;
	if (pCMyMath == NULL) {
		return(E_OUTOFMEMORY);
	}

	pCMyMath->InitInstance();

	hr=pCMyMath->QueryInterface(riid, ppv);
	pCMyMath->Release();
	return(hr);
}

HRESULT __stdcall CMyMathClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return (S_OK);
}

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv) {
	CMyMathClassFactory *pCMyMathClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_MyMath)
		return(CLASS_E_CLASSNOTAVAILABLE);
	pCMyMathClassFactory = new CMyMathClassFactory;
	if (pCMyMathClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCMyMathClassFactory->QueryInterface(riid,ppv);

	pCMyMathClassFactory->Release();
	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void) {
	if (glNumberOfActiveComponents == 0 && glNumberOfServerLocks == 0)
		return(S_OK);
	else
		return(S_FALSE);
}
void ComErrorDescriptionString(HWND hwnd, HRESULT hr) {
	TCHAR * szErrorMessage = NULL;
	
	TCHAR str[255];
	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);
	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&szErrorMessage, 0, NULL))
	{
		wsprintf(str, szErrorMessage);
		//swprintf_s(str1,255,"%#x : %s",hr,szErrorMessage,);
		LocalFree(szErrorMessage);
	}
	else
		wsprintf(str, szErrorMessage);
	//swprintf_s(str, TEXT("Could not find description for error # %#x"), hr);

	MessageBox(hwnd, str, TEXT("COM_EROOR"), MB_OK);
}