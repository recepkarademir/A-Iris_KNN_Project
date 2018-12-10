#include<iostream>
#include "veriSetlereAyir.h"
#include"AnaSayfa.h" // prototiplerin k�t�phenesi AnaSayfa.h da
using namespace std;

void veriSetlereAyirFonk(int *egitimSeti,int *dogrulamaSeti,int *testSeti,int veriAdet)
{
	*egitimSeti=veriAdet*0.50; 	// yukar� yuvarlama yapar. e�itim seti, toplam veri setinin %50 si kadar
	*dogrulamaSeti=veriAdet*0.25;// do�rulama seti, toplam veri setinin ~%25 si kadar
	*testSeti=veriAdet*0.25; 	// test seti, toplam veri setinin ~%25 si kadar
	
	int setduzeltme = *dogrulamaSeti + *egitimSeti + *testSeti ; // kesirli say�larda do�rulama seti +1 yukar� yuvarlan�r ve setler d�zeltilmi� olur.
	if(setduzeltme!=veriAdet) // veri setinin toplam adeti orijinal veri setinin toplam veri adetiyle ayn� olmal�. de�ilse setler mant�kl� olarak ayr�l�r.
	{
		setduzeltme = veriAdet - setduzeltme;
		*dogrulamaSeti += setduzeltme;
		setduzeltme = *dogrulamaSeti + *egitimSeti + *testSeti ;
		cout<<"\n";
		for(int g=0;g<5;++g){cout<<"-----------------";}
		cout<<"\nVeri Adedi "<<veriAdet<<" a�a��daki gibi setlere ayr�ld� : \nE�itim seti veri adeti    : "<<*egitimSeti<<endl;
		cout<<"Do�rulama seti veri adeti : "<<*dogrulamaSeti<<endl;
		cout<<"Test seti veri adeti      : "<<*testSeti<<endl;
		if(setduzeltme==veriAdet)
		{
			cout<<"\nSetlerin oranl� ayr�lmas� i�in d�zeltme yap�ld�.\n"<<endl;
		}
	}
	else
	{
		cout<<"\n\nE�itim seti veri adeti    : "<<*egitimSeti<<endl;
		cout<<"Do�rulama seti veri adeti : "<<*dogrulamaSeti<<endl;
		cout<<"Test seti veri adeti      : "<<*testSeti<<endl;
	}
	for(int g=0;g<5;++g){cout<<"-----------------";} cout<<endl;
	
	if(veriAdet < 10 )
	{
		cout<<	"\n\n\n\nVeri seti �ok k���k !\n"<<endl; // d���k veri setine k de�eri i�in i�lem yapt�rm�yorum
		cout<< "\n\n\n\nProgram sonland�r�ld�.";
		exit(0);
	}
}

