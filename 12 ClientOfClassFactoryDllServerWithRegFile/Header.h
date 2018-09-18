class ISum :public IUnknown {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *)=0;
};

class ISubract :public IUnknown {
public:
	virtual HRESULT __stdcall SubstractionOfTwoIntegers(int, int, int *) = 0;
};

const CLSID CLSID_SumSubstract=// {A50522C6-8321-4F58-877C-2FD894A65F35}
{ 0xa50522c6, 0x8321, 0x4f58, 0x87, 0x7c, 0x2f, 0xd8, 0x94, 0xa6, 0x5f, 0x35 };

const IID IID_ISum = // {866B0639-4F0A-40BE-9DD1-EF9886EDC0A7}
{ 0x866b0639, 0x4f0a, 0x40be,  0x9d, 0xd1, 0xef, 0x98, 0x86, 0xed, 0xc0, 0xa7 } ;

const IID IID_ISub = {// {3B09A508-F368-4618-B3AC-24F433296BE8}
 0x3b09a508, 0xf368, 0x4618,  0xb3, 0xac, 0x24, 0xf4, 0x33, 0x29, 0x6b, 0xe8 };

