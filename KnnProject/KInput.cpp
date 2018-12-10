#include <iostream>
#include "KInput.h"

using namespace std;

short enYakinKomsuAlgoritmasi(int egitimSeti, int veriAdet)
{
	short k;
	
	
	for(int g=0;g<5;++g){cout<<"-----------------";} cout<<endl;
	K_ISTE:cout<<"\n\nKaç yakýn komþu için tahmin yürütülmesini istiyorsun ( [1 , eðitimSetiVeriAdeti ] arasý deðer gir) ";
	cout<<"\nDegeri girip entera bas : \n\n\n";
	cin>>k;
	
	if(k<=0 || k>egitimSeti)
	{
		cout<<"\nBu deðeri k olarak atayamazsýn ! \n";
		goto K_ISTE; 
	}
	system("cls");
	
	
	// setlere ayýrma iþlemi yapýlýyor.  egitimSeti , testSeti , dogrulamaSeti ,	
	
	return k;
	
	
}
