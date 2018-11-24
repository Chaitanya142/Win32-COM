#include "stdio.h"
#using <MSCorLib.dll>

void main(void)
{
	
	printf("Hello World from Native\n");
	System::Console::WriteLine("Hello World from Dot Net");
	System::Console::ReadKey();
}