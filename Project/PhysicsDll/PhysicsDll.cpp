#include<Windows.h>
#include "PhysicsDll.h"
#include <string>
#include<string.h>
#include <stdlib.h>

TCHAR str[] = "";

TCHAR str1[] = "";

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:

		break;

	case DLL_THREAD_ATTACH:

		break;

	case DLL_THREAD_DETACH:

		break;

	case DLL_PROCESS_DETACH:

		break;
	}
	return TRUE;

}

extern "C" char * GetValue(char *);
extern "C" char * GetMultiplier(char *);
extern "C" char * GetTolerence(char *);

extern "C" char * GetResistance(char * FirstDigit, char *  SecondDigit, char * Multiplier) {//, char * Tolerence

	char* context = NULL;
	const char splitString[4] = " ";

	char * FDigit = GetValue(FirstDigit);
	char * SDigit = GetValue(SecondDigit);
	double Resistance = atof(FDigit) * 10 + atof(SDigit);

	//wsprintf(str, FDigit);
	//MessageBox(NULL, str, TEXT("Message Box"), MB_OK);
	//wsprintf(str, SDigit);
	//MessageBox(NULL, str, TEXT("Message Box"), MB_OK);


	//delete FDigit;
	//delete SDigit;

	char * Mult = GetMultiplier(Multiplier);

	//char * MultPart1 = strtok_s(Mult, splitString, &context);
	//char * MultPart2 = strtok_s(0, splitString, &context);



	char * copyMultPart = new char[sizeof(Mult)+1];
	sprintf_s(copyMultPart, sizeof(Mult)+1, Mult);

	char * MultPart1 = strtok_s(copyMultPart, splitString, &context);
	char * MultPart2 = strtok_s(NULL, splitString, &context);


	//wsprintf(str, MultPart1);
	//MessageBox(NULL, str, TEXT("Message Box"), MB_OK);

	//delete Mult;
	Resistance = Resistance * atof(MultPart1);
	//delete MultPart1;
	char * strResistance = new char[sizeof(Resistance)];
	sprintf_s(strResistance, sizeof(Resistance), "%.2f", Resistance);
	//wsprintf(strResistance, "%.2f", Resistance);

	char ResistanceValue[500] = "";


	/*wsprintf(str, strResistance);
	MessageBox(NULL, str, TEXT("Message Box"), MB_OK);

	wsprintf(str, ResistanceValue);
	MessageBox(NULL, str, TEXT("Message Box"), MB_OK);*/

	//wsprintf(str, (LPSTR)strlen(strResistance));
	//MessageBox(NULL, str, TEXT("Message Box"), MB_OK);

	strcat_s(ResistanceValue, 100, strResistance);
	strcat_s(ResistanceValue, 10, " ");
	//     if(strcmp(MultPart2,NULL)!=0)
	if (MultPart2 != NULL)
		strcat_s(ResistanceValue, 100, MultPart2);
	//strcat_s(ResistanceValue, sizeof(MultPart2), MultPart2);

	//strcat_s(ResistanceValue, 15, " ±");

	/*wsprintf(str, ResistanceValue);
	MessageBox(NULL, str, TEXT("Message Box"), MB_OK);
*/
	//char * Tol = GetTolerence(Tolerence);
	//strcat_s(ResistanceValue, 100, Tol);
	//strcat_s(ResistanceValue, 20, "%%");


	wsprintf(str, ResistanceValue);
	//MessageBox(NULL, str, TEXT("Message Box"), MB_OK);
	//delete Tol;
	//delete MultPart2;

	return str;

}

extern "C"  char * GetValue(char * Color) {
	char * Value = new char[5];
	if (_strcmpi(Color, "Black") == 0)
		sprintf_s(Value, sizeof("0"), "0");
	else if (_strcmpi(Color, "Brown") == 0)
		sprintf_s(Value, sizeof("1"), "1");
	else if (_strcmpi(Color, "Red") == 0)
		sprintf_s(Value, sizeof("2"), "2");
	else if (_strcmpi(Color, "Orange") == 0)
		sprintf_s(Value, sizeof("3"), "3");
	else if (_strcmpi(Color, "Yellow") == 0)
		sprintf_s(Value, sizeof("4"), "4");
	else if (_strcmpi(Color, "Green") == 0)
		sprintf_s(Value, sizeof("5"), "5");
	else if (_strcmpi(Color, "Blue") == 0)
		sprintf_s(Value, sizeof("6"), "6");
	else if (_strcmpi(Color, "Violet") == 0)
		sprintf_s(Value, sizeof("7"), "7");
	else if (_strcmpi(Color, "Grey") == 0)
		sprintf_s(Value, sizeof("8"), "8");
	else if (_strcmpi(Color, "White") == 0)
		sprintf_s(Value, sizeof("9"), "9");
	return Value;
}

extern "C"  char * GetMultiplier(char * Color) {
	char * Value = new char[25];
	if (_strcmpi(Color, "Black") == 0)
		sprintf_s(Value, sizeof("1 "), "1 ");
	else if (_strcmpi(Color, "Brown") == 0)
		sprintf_s(Value, sizeof("10 "), "10 ");
	else if (_strcmpi(Color, "Red") == 0)
		sprintf_s(Value, sizeof("100 "), "100 ");
	else if (_strcmpi(Color, "Orange") == 0)
		sprintf_s(Value, sizeof("1 K"), "1 K");
	else if (_strcmpi(Color, "Yellow") == 0)
		sprintf_s(Value, sizeof("10 K"), "10 K");
	else if (_strcmpi(Color, "Green") == 0)
		sprintf_s(Value, sizeof("100 K"), "100 K");
	else if (_strcmpi(Color, "Blue") == 0)
		sprintf_s(Value, sizeof("1 M"), "1 M");
	else if (_strcmpi(Color, "Violet") == 0)
		sprintf_s(Value, sizeof("10 M"), "10 M");
	else if (_strcmpi(Color, "Grey") == 0)
		sprintf_s(Value, sizeof("100 M"), "100 M");
	else if (_strcmpi(Color, "White") == 0)
		sprintf_s(Value, sizeof("1 G"), "1 G");
	else if (_strcmpi(Color, "Gold") == 0)
		sprintf_s(Value, sizeof("0.1 "), "0.1 ");
	else if (_strcmpi(Color, "Silver") == 0)
		sprintf_s(Value, sizeof("0.01 "), "0.01");
	return Value;
}


extern "C"  char * GetTolerence(char * Color) {
	char * Value1 = new char[50];
	/*if (strcmpi(Color, "black") == 0)
		   Value = "1";*/
		   //else
	if (_strcmpi(Color, "Brown") == 0)
		sprintf_s(Value1, sizeof("1"), "1");
	else if (_strcmpi(Color, "Red") == 0)
		sprintf_s(Value1, sizeof("2"), "2");
	else if (_strcmpi(Color, "Orange") == 0)
		sprintf_s(Value1, sizeof("3"), "3");
	else if (_strcmpi(Color, "Yellow") == 0)
		sprintf_s(Value1, sizeof("4"), "4");
	else if (_strcmpi(Color, "Green") == 0)
		sprintf_s(Value1, sizeof("0.5"), "0.5");
	else if (_strcmpi(Color, "Blue") == 0)
		sprintf_s(Value1, sizeof("0.25"), "0.25");
	else if (_strcmpi(Color, "Violet") == 0)
		sprintf_s(Value1, sizeof("0.10"), "0.10");
	else if (_strcmpi(Color, "Grey") == 0)
		sprintf_s(Value1, sizeof("0.05"), "0.05");
	/*else if (strcmpi(Color, "white") == 0)
		   Value = "1 G";*/
	else if (_strcmpi(Color, "Gold") == 0)
		sprintf_s(Value1, sizeof("5"), "5");
	else if (_strcmpi(Color, "Silver") == 0)
		sprintf_s(Value1, sizeof("10"), "10");
	return Value1;
}



extern "C"  char * GetTolerenceValue(char * Color) {
	char TolerenceValue[100];
	char * Tol1 = GetTolerence(Color);
	double TolVal = atof(Tol1);
	sprintf_s(TolerenceValue, sizeof(TolVal)+10,"± %.2f",TolVal );
	strcat_s(TolerenceValue, 20, "%%");
	wsprintf(str1, TolerenceValue);
	return(str1);

}

