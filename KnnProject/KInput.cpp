#include <iostream>
#include "KInput.h"

using namespace std;

short enYakinKomsuAlgoritmasi(int egitimSeti, int veriAdet)
{
	short k;
	
	
	for(int g=0;g<5;++g){cout<<"-----------------";} cout<<endl;
	K_ISTE:cout<<"\n\nKa� yak�n kom�u i�in tahmin y�r�t�lmesini istiyorsun ( [1 , e�itimSetiVeriAdeti ] aras� de�er gir) ";
	cout<<"\nDegeri girip entera bas : \n\n\n";
	cin>>k;
	
	if(k<=0 || k>egitimSeti)
	{
		cout<<"\nBu de�eri k olarak atayamazs�n ! \n";
		goto K_ISTE; 
	}
	system("cls");
	
	
	// setlere ay�rma i�lemi yap�l�yor.  egitimSeti , testSeti , dogrulamaSeti ,	
	
	return k;
	
	
}
