#include <Windows.h>
class ISum :public IUnknown {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtraction :public IUnknown {
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

const CLSID CLSID_SumSubstract =
// {24A85C03-B1EC-4462-A44F-EE9917739BFD}
{ 0x24a85c03, 0xb1ec, 0x4462, { 0xa4, 0x4f, 0xee, 0x99, 0x17, 0x73, 0x9b, 0xfd } };

const IID IID_ISum =
// {DCD4026F-B234-48CC-8818-78EB1490E639}
{ 0xdcd4026f, 0xb234, 0x48cc, { 0x88, 0x18, 0x78, 0xeb, 0x14, 0x90, 0xe6, 0x39 } };

const IID IID_ISubtraction =
// {2C128E80-D918-4FA0-BBC1-BAEDE5EA76CC}
{ 0x2c128e80, 0xd918, 0x4fa0, { 0xbb, 0xc1, 0xba, 0xed, 0xe5, 0xea, 0x76, 0xcc } };

class IMultiplication :public IUnknown
{
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *) = 0;
};

class IDivision :public IUnknown {
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};

const CLSID CLSID_MultiplicationDivision =
// {2BDEEEA9-A64C-4958-BAFD-B827E0DD3BB6}
{ 0x2bdeeea9, 0xa64c, 0x4958, { 0xba, 0xfd, 0xb8, 0x27, 0xe0, 0xdd, 0x3b, 0xb6 } };

const IID IID_IMultiplication =
// {FBFB628C-F70C-4EBB-9DF8-1F62E1F1FB23}
{ 0xfbfb628c, 0xf70c, 0x4ebb, { 0x9d, 0xf8, 0x1f, 0x62, 0xe1, 0xf1, 0xfb, 0x23 } };

const IID IID_IDivision =
// {6D247BF5-5794-4451-BCFC-E522B94A5102}
{ 0x6d247bf5, 0x5794, 0x4451, { 0xbc, 0xfc, 0xe5, 0x22, 0xb9, 0x4a, 0x51, 0x2 } };


