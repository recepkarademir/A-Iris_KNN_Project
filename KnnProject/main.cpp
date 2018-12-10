/* 
	2018-12-10
	Recep KARADEM�R 
	IRIS  :  S�sengiller (Iris), Asparagales tak�m�na ait bir �i�ekli bitki familyas�d�r.

	Iris familyas�ndaki �� t�r�n temel �zelliklerinden olu�an veri seti yard�m�yla, 
	en iyi t�r tahmini yapan K de�erini bulan C++ program� .
	
	
	V2.0 :  Program mod�ler olarak tasarland�
*/

#include <iostream>

#include <conio.h>		// getc() i�in.
#include <locale.h>  // T�rk�e karakter ��kt�s� i�in.

#include "AnaSayfa.h" // Program a��l���ndaki bilgi ekran�.
#include "veriOku.h"
#include "standartizasyon.h"
#include "veriYazdir.h"
#include "getRandom.h"
#include "veriSetlereAyir.h"
#include "KInput.h"
#include "Knn.h"
#include "testVeri.h"

using namespace std;

int main() 
{
	float veriSeti[150][5];
	int  veriNitelik=5 ;
	// veriSeti dizisinin 1.s�tunun da sepalL    2.s�tununda sepalW    3.s�tununda petalL     4.s�tununda petalW   5.s�tununda irisName  bulunacak.
	// veriSeti dizisinin 1.sat�r�nda txtdeki ilk verinin bilgileri , n.sat�rda txt i�indeki n.sat�rdaki verinin bilgileri bulunur.
	// irisName 0 ise iris-setosa , 1 ise iris-versicolor , 2 ise iris-virginica  verilerini ifade edecek �ekilde kodlanm��t�r.

	int  veriAdet =0 ; // veri adeti txt deki bo� olmayan sat�rlar�n adetini ifade eder. 5 ise verinin �zelliklerini(sepalL,.., IrisName vs)
	int setler[3]={0,0,0};
	short k=1;
	// setler[0] = egitimSeti	setler[1] = dogrulamaSeti		setler[2] =  testSeti       
	int egitimSeti , dogrulamaSeti , testSeti; // setlerin indislerini tutmak i�in ; 
	bool ktespiti_izin=false; // normalizasyon yapmadan k tespiti yapt�rmayaca��m.
	bool shuffle_testi=false;
	char secim=5;
	char testVeriSecim;
	float dogrulukOrani=0.0; // testVeriSecim ile test setindeki veri tahmin edilirken bu de�i�ken laz�m olacak.
	
	
	Bilgi();
	system("color F0");  // konsolun rengi de�i�ir
	
	veriAdet = veriOkuFonk(veriSeti); // bu fonksiyonda veriler okunup matris diziye atan�p veri adeti tespit edilecek.
	
	setlocale(LC_ALL, "Turkish");
	cout<<"\nBuradaki se�imlerde tavsiye edilen i�lem s�ras� ��yledir : 1 , 2 , 3 , 4 , 5 \n"<<endl;
	
	
	veriSetlereAyirFonk(&egitimSeti,&dogrulamaSeti,&testSeti,veriAdet);// veri setlere ayr�lmal�.
	
	while(true)
	{
		cout<<"\n\n\nVerilerin g�ncel halini listelemek i�in.................. 1 e bas "<<endl;
		cout<<"Verilerin normalize edilmesi i�in........................ 2 ye bas"<<endl;
		cout<<"Verilerin yerlerini kar��t�rmak(3 defa kar��t�r�l�r) i�in 3 e bas"<<endl;
		cout<<"K-Nearest Neighbor (en yak�n kom�u) algoritmas� i�in..... 4 e bas"<<endl;
		cout<<"Konsol ekran�n� temizlemek i�in ......................... 0 a bas"<<endl;
		cout<<"Program� bitirmek i�in .................................. 5 e bas"<<endl;
		
		secim=getch();
		
		if(secim=='1')
		{
			verileriYazdir(veriSeti,veriAdet,0); // bellekteki veri setinin anl�k olarak konsola bas�lmas�n� sa�lar.
			// 0 gitti�inde b�t�n veriyi yazdirir.0.indisten ba�layarak yazd�r�r.
		}
		else if(secim=='2')
		{
			ktespiti_izin=true;
			standartizasyonfonk(veriSeti,veriAdet); // verilerin tahmine etkisinin ortak bir a��rl�kland�rmada olmas�n� sa�lar.
		}
		else if(secim=='3')
		{
			shuffle_testi=true;
			getRandomFonk(veriSeti,veriAdet); // verilerin yerlerini rastgele olarak 3 defa kar��t�r�r.
		}
		else if(secim=='4' && ktespiti_izin==true)
		{
			if(shuffle_testi==false)
			{
				cout<<"\n\n\n\n\n\n\n�NCE VER�LER�N "<<"KARI�TIRILMASI TAVS�YE ED�L�R ! \n";
			}
			k=enYakinKomsuAlgoritmasi(egitimSeti,veriAdet); // k de�eri al�n�yor.
			dogrulukOrani=komsulukFarkHesapla(k,egitimSeti,dogrulamaSeti,veriSeti,veriNitelik); // kom�uluk farklar� hesaplanacak. ve tahminler listelenecek
			cout<<"\n\n\nTest setinden bir veriyi tahmin ettirmek i�in 9 a bas�n\nMen�y� g�r�nt�lemek i�in herhangi bir tu�a bas:\n";
			testVeriSecim=getch();
			if(testVeriSecim=='9'){ testVeriFonk(k,egitimSeti,dogrulamaSeti,testSeti ,veriSeti,veriNitelik,dogrulukOrani); }
		}
		else if(secim=='4' && ktespiti_izin==false)
		{
			cout<<"\n\n\n\n\n\n\n�NCE NORMAL�ZASYON YAPMALISIN ! \n"; // normalize olmam�� verilerde kom�uluk fark� hesab� yapt�rm�yorum.
		}
		else if(secim=='5')
		{
			break; // while d�ng�s�nden ��kar ve program bitmi� olur.
		}
		else if(secim=='0')
		{
			system("cls"); // konsol ekran�n� temizler
		}
		else
		{
			cout<<"\n\nYanl�� tu�lama yapt�n !"<<endl;
		}
	}

	KapanisBilgi();
	return 0;
}

