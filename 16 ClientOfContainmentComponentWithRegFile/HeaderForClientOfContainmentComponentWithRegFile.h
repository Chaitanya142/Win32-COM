#include <Windows.h>

class IMultiplication :public IUnknown {
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *) = 0;

};

class IDivision : public IUnknown {
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *) = 0;

};

class ISum :public IUnknown {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;
};

class ISubstract :public IUnknown {
public:
	virtual HRESULT __stdcall SubstractionOfTwoIntegers(int, int, int *) = 0;
};

const CLSID CLSID_SumSubstract =// {1F93FD0C-72DF-4836-B79A-B157ED987C52}
{ 0x1f93fd0c, 0x72df, 0x4836, { 0xb7, 0x9a, 0xb1, 0x57, 0xed, 0x98, 0x7c, 0x52 } };

const IID IID_ISum =
// {ED10009E-FAC6-425E-A961-44294DDC5F35}
{ 0xed10009e, 0xfac6, 0x425e, { 0xa9, 0x61, 0x44, 0x29, 0x4d, 0xdc, 0x5f, 0x35 } };

const IID IID_ISubstract =
// {22C616A3-24D6-4765-849C-53860F3EA90B}
{ 0x22c616a3, 0x24d6, 0x4765, { 0x84, 0x9c, 0x53, 0x86, 0xf, 0x3e, 0xa9, 0xb } };


const IID IID_IMultiplication =
// {550BE6C4-9650-40E1-A9C9-D0C49A301970}
{ 0x550be6c4, 0x9650, 0x40e1, { 0xa9, 0xc9, 0xd0, 0xc4, 0x9a, 0x30, 0x19, 0x70 } };

const IID IID_IDivison =
// {5702C426-6E20-4C74-95FA-BC3A91A8369D}
{ 0x5702c426, 0x6e20, 0x4c74, { 0x95, 0xfa, 0xbc, 0x3a, 0x91, 0xa8, 0x36, 0x9d } };
