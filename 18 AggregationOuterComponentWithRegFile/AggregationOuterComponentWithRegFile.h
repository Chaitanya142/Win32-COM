#include <Windows.h>
class ISum :public IUnknown {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtraction :public IUnknown {
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

const CLSID CLSID_SumSubstract=
// {24A85C03-B1EC-4462-A44F-EE9917739BFD}
{ 0x24a85c03, 0xb1ec, 0x4462, { 0xa4, 0x4f, 0xee, 0x99, 0x17, 0x73, 0x9b, 0xfd } };

const IID IID_ISum=
// {DCD4026F-B234-48CC-8818-78EB1490E639}
{ 0xdcd4026f, 0xb234, 0x48cc, { 0x88, 0x18, 0x78, 0xeb, 0x14, 0x90, 0xe6, 0x39 } };

const IID IID_ISubtraction=
// {2C128E80-D918-4FA0-BBC1-BAEDE5EA76CC}
{ 0x2c128e80, 0xd918, 0x4fa0, { 0xbb, 0xc1, 0xba, 0xed, 0xe5, 0xea, 0x76, 0xcc } };
