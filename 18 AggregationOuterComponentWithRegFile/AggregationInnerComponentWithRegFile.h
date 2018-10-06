#include<Windows.h>

class IMultiplication :public IUnknown
{
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *) = 0;
};

class IDivision :public IUnknown {
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};


const CLSID CLSID_MultiplicationDivision=
// {2BDEEEA9-A64C-4958-BAFD-B827E0DD3BB6}
{ 0x2bdeeea9, 0xa64c, 0x4958, { 0xba, 0xfd, 0xb8, 0x27, 0xe0, 0xdd, 0x3b, 0xb6 } };

const IID IID_IMultiplication=
// {FBFB628C-F70C-4EBB-9DF8-1F62E1F1FB23}
{ 0xfbfb628c, 0xf70c, 0x4ebb, { 0x9d, 0xf8, 0x1f, 0x62, 0xe1, 0xf1, 0xfb, 0x23 } };

const IID IID_IDivision=
// {6D247BF5-5794-4451-BCFC-E522B94A5102}
{ 0x6d247bf5, 0x5794, 0x4451, { 0xbc, 0xfc, 0xe5, 0x22, 0xb9, 0x4a, 0x51, 0x2 } };
