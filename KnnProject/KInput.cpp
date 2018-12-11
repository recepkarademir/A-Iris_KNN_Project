#include <iostream>

using namespace std;

short enYakinKomsuAlgoritmasi(int egitimSeti, int veriAdet)
{
	short k;
	
	for(int g=0;g<5;++g){cout<<"-----------------";} cout<<endl;
	if((egitimSeti-1)>=(veriAdet/2))	// test setindeki bir veri için k deðeri (doðrulama + eðitim)  veri adeti kadar olabilir.
	{
		K_ISTE:cout<<"\nKaç yakýn komþu için tahmin yürütülmesini istiyorsun ( [1 , (doðrulama + eðitim) ] arasý deðer gir) ";
		cout<<"\nDegeri girip entera bas : \n";
		cin>>k;
		
		if(k<=0 || k>egitimSeti) // k deðeri eðitim seti adetinden büyük ve 0 dan küçük olamaz.
		{
			cout<<"\nBu deðeri k olarak atayamazsýn ! \n\a";
			goto K_ISTE; 
		}
	}
	else	// k deðeri [1 ile eðitimSetiVeriAdeti] arasýnda bir deðer olabilir.
	{
		K_ISTE2:cout<<"\nKaç yakýn komþu için tahmin yürütülmesini istiyorsun ( [1 , eðitimSetiVeriAdeti ] arasý deðer gir) ";
		cout<<"\nDegeri girip entera bas : \n";
		cin>>k;
		
		if(k<=0 || k>egitimSeti) // k deðeri eðitim seti adetinden büyük ve 0 dan küçük olamaz.
		{
			cout<<"\nBu deðeri k olarak atayamazsýn ! \n\a";
			goto K_ISTE2; 
		}
	}
	
	
	return k;	
}
