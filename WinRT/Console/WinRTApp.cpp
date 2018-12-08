#include<iostream>
using namespace std;
using namespace Platform;

int main(Array <String^>^ args){
String^ str="Hello World";
wcout<<str->Data()<<endl;
int i=0;
cin>>i;
return(0); 

}
