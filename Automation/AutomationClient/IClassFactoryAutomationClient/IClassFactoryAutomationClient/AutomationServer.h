#include<Windows.h>

class IMyMath :public IDispatch {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int,int,int *)=0;
	virtual HRESULT __stdcall SubstractionOfTwoIntegers(int, int, int*) = 0;
};

const CLSID CLSID_MyMath=
// {3E86F9D9-166A-4010-8C19-10ACF823285E}
{ 0x3e86f9d9, 0x166a, 0x4010, { 0x8c, 0x19, 0x10, 0xac, 0xf8, 0x23, 0x28, 0x5e } };

const IID IID_IMyMath=
// {91A47FAE-9774-4086-BC98-20AE3B183426}
{ 0x91a47fae, 0x9774, 0x4086, { 0xbc, 0x98, 0x20, 0xae, 0x3b, 0x18, 0x34, 0x26 } };
