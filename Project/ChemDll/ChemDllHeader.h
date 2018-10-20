#include<Windows.h>
class ICIP :public IUnknown {
public:
	virtual HRESULT __stdcall CalculateInitialPressure(double *, double, double ,double ) = 0;
};

class ICIT :public IUnknown {
public:
	virtual HRESULT __stdcall CalculateInitialTemp(double, double *, double, double ) = 0;
};

class ICFP :public IUnknown {
public:
	virtual HRESULT __stdcall CalculateFinalPressure(double, double, double *, double) = 0;
};

class ICFT :public IUnknown {
public:
	virtual HRESULT __stdcall CalculateFinalTemp(double, double, double, double *) = 0;
};

const CLSID CLSID_GayLussacsLawCalculator =// {B8A96FF5-94C9-43FD-911C-D2C5E582C1E6}
{ 0xb8a96ff5, 0x94c9, 0x43fd, { 0x91, 0x1c, 0xd2, 0xc5, 0xe5, 0x82, 0xc1, 0xe6 } };

const IID IID_ICIP = // {3D6DF16E-396D-4665-8044-60840D14DA2E}
{ 0x3d6df16e, 0x396d, 0x4665, { 0x80, 0x44, 0x60, 0x84, 0xd, 0x14, 0xda, 0x2e } };

const IID IID_ICIT=// {AD338622-C6FE-40A7-87E5-9E6D107A2694}
{ 0xad338622, 0xc6fe, 0x40a7, { 0x87, 0xe5, 0x9e, 0x6d, 0x10, 0x7a, 0x26, 0x94 } };

const IID IID_ICFP=// {B96736B8-8261-4DBF-907C-DA9513334695}
{ 0xb96736b8, 0x8261, 0x4dbf, { 0x90, 0x7c, 0xda, 0x95, 0x13, 0x33, 0x46, 0x95 } };

const IID IID_ICFT=// {723814CC-A83C-48C2-8898-0E700A3C89BF}
{ 0x723814cc, 0xa83c, 0x48c2, { 0x88, 0x98, 0xe, 0x70, 0xa, 0x3c, 0x89, 0xbf } };
