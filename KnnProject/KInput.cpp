#include <iostream>

using namespace std;

short enYakinKomsuAlgoritmasi(int egitimSeti, int veriAdet)
{
	short k;
	
	for(int g=0;g<5;++g){cout<<"-----------------";} cout<<endl;
	if((egitimSeti-1)>=(veriAdet/2))	// test setindeki bir veri i�in k de�eri (do�rulama + e�itim)  veri adeti kadar olabilir.
	{
		K_ISTE:cout<<"\nKa� yak�n kom�u i�in tahmin y�r�t�lmesini istiyorsun ( [1 , (do�rulama + e�itim) ] aras� de�er gir) ";
		cout<<"\nDegeri girip entera bas : \n";
		cin>>k;
		
		if(k<=0 || k>egitimSeti) // k de�eri e�itim seti adetinden b�y�k ve 0 dan k���k olamaz.
		{
			cout<<"\nBu de�eri k olarak atayamazs�n ! \n\a";
			goto K_ISTE; 
		}
	}
	else	// k de�eri [1 ile e�itimSetiVeriAdeti] aras�nda bir de�er olabilir.
	{
		K_ISTE2:cout<<"\nKa� yak�n kom�u i�in tahmin y�r�t�lmesini istiyorsun ( [1 , e�itimSetiVeriAdeti ] aras� de�er gir) ";
		cout<<"\nDegeri girip entera bas : \n";
		cin>>k;
		
		if(k<=0 || k>egitimSeti) // k de�eri e�itim seti adetinden b�y�k ve 0 dan k���k olamaz.
		{
			cout<<"\nBu de�eri k olarak atayamazs�n ! \n\a";
			goto K_ISTE2; 
		}
	}
	
	
	return k;	
}
