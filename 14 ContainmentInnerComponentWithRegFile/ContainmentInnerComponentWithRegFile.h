#include <Windows.h>

class IMultiplication :public IUnknown {
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int *) = 0;

};

class IDivision : public IUnknown {
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int *) = 0;

};

const CLSID CLSID_MultiplicationDivision =
// {E5F37C87-FD59-46B5-B355-E34EA7541FA1}
{ 0xe5f37c87, 0xfd59, 0x46b5, { 0xb3, 0x55, 0xe3, 0x4e, 0xa7, 0x54, 0x1f, 0xa1 } };

const IID IID_IMultiplication =
// {550BE6C4-9650-40E1-A9C9-D0C49A301970}
{ 0x550be6c4, 0x9650, 0x40e1, { 0xa9, 0xc9, 0xd0, 0xc4, 0x9a, 0x30, 0x19, 0x70 } };

const IID IID_IDivison =
// {5702C426-6E20-4C74-95FA-BC3A91A8369D}
{ 0x5702c426, 0x6e20, 0x4c74, { 0x95, 0xfa, 0xbc, 0x3a, 0x91, 0xa8, 0x36, 0x9d } };
