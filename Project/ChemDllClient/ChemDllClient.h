#include<Windows.h>
extern "C" HRESULT CalculateInitialPressure(double *, double, double, double);
extern "C" HRESULT CalculateInitialTemp(double, double *, double, double);
extern "C" HRESULT CalculateFinalPressure(double, double, double *, double);
extern "C" HRESULT CalculateFinalTemp(double, double, double, double *);

