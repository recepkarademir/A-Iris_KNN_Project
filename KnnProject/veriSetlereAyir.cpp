#include<iostream>
#include "veriSetlereAyir.h"
#include"AnaSayfa.h" // prototiplerin kütüphenesi AnaSayfa.h da
using namespace std;

void veriSetlereAyirFonk(int *egitimSeti,int *dogrulamaSeti,int *testSeti,int veriAdet)
{
	*egitimSeti=veriAdet*0.50; 	// yukarý yuvarlama yapar. eðitim seti, toplam veri setinin %50 si kadar
	*dogrulamaSeti=veriAdet*0.25;// doðrulama seti, toplam veri setinin ~%25 si kadar
	*testSeti=veriAdet*0.25; 	// test seti, toplam veri setinin ~%25 si kadar
	
	int setduzeltme = *dogrulamaSeti + *egitimSeti + *testSeti ; // kesirli sayýlarda doðrulama seti +1 yukarý yuvarlanýr ve setler düzeltilmiþ olur.
	if(setduzeltme!=veriAdet) // veri setinin toplam adeti orijinal veri setinin toplam veri adetiyle ayný olmalý. deðilse setler mantýklý olarak ayrýlýr.
	{
		setduzeltme = veriAdet - setduzeltme;
		*dogrulamaSeti += setduzeltme;
		setduzeltme = *dogrulamaSeti + *egitimSeti + *testSeti ;
		cout<<"\n";
		for(int g=0;g<5;++g){cout<<"-----------------";}
		cout<<"\nVeri Adedi "<<veriAdet<<" aþaðýdaki gibi setlere ayrýldý : \nEðitim seti veri adeti    : "<<*egitimSeti<<endl;
		cout<<"Doðrulama seti veri adeti : "<<*dogrulamaSeti<<endl;
		cout<<"Test seti veri adeti      : "<<*testSeti<<endl;
		if(setduzeltme==veriAdet)
		{
			cout<<"\nSetlerin oranlý ayrýlmasý için düzeltme yapýldý.\n"<<endl;
		}
	}
	else
	{
		cout<<"\n\nEðitim seti veri adeti    : "<<*egitimSeti<<endl;
		cout<<"Doðrulama seti veri adeti : "<<*dogrulamaSeti<<endl;
		cout<<"Test seti veri adeti      : "<<*testSeti<<endl;
	}
	for(int g=0;g<5;++g){cout<<"-----------------";} cout<<endl;
	
	if(veriAdet < 10 )
	{
		cout<<	"\n\n\n\nVeri seti çok küçük !\n"<<endl; // düþük veri setine k deðeri için iþlem yaptýrmýyorum
		cout<< "\n\n\n\nProgram sonlandýrýldý.";
		exit(0);
	}
}

