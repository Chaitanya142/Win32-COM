#include <Windows.h>

class ISum :public IUnknown {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;
};

class ISubstract :public IUnknown {
public:
	virtual HRESULT __stdcall SubstractionOfTwoIntegers(int, int, int *) = 0;
};

const CLSID CLSID_SumSubstract=// {1F93FD0C-72DF-4836-B79A-B157ED987C52}
{ 0x1f93fd0c, 0x72df, 0x4836, { 0xb7, 0x9a, 0xb1, 0x57, 0xed, 0x98, 0x7c, 0x52 } };

const IID IID_ISum=
// {ED10009E-FAC6-425E-A961-44294DDC5F35}
{ 0xed10009e, 0xfac6, 0x425e, { 0xa9, 0x61, 0x44, 0x29, 0x4d, 0xdc, 0x5f, 0x35 } };

const IID IID_ISubstract=
// {22C616A3-24D6-4765-849C-53860F3EA90B}
{ 0x22c616a3, 0x24d6, 0x4765, { 0x84, 0x9c, 0x53, 0x86, 0xf, 0x3e, 0xa9, 0xb } };
