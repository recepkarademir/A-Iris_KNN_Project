/* 
	2018-12-10
	Recep KARADEMÝR 
	IRIS  :  Süsengiller (Iris), Asparagales takýmýna ait bir çiçekli bitki familyasýdýr.

	Iris familyasýndaki üç türün temel özelliklerinden oluþan veri seti yardýmýyla, 
	en iyi tür tahmini yapan K deðerini bulan C++ programý .
	
	
	V2.0 :  Program modüler olarak tasarlandý
*/

#include <iostream>

#include <conio.h>		// getc() için.
#include <locale.h>  // Türkçe karakter çýktýsý için.

#include "AnaSayfa.h" // Program açýlýþýndaki bilgi ekraný.
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
	// veriSeti dizisinin 1.sütunun da sepalL    2.sütununda sepalW    3.sütununda petalL     4.sütununda petalW   5.sütununda irisName  bulunacak.
	// veriSeti dizisinin 1.satýrýnda txtdeki ilk verinin bilgileri , n.satýrda txt içindeki n.satýrdaki verinin bilgileri bulunur.
	// irisName 0 ise iris-setosa , 1 ise iris-versicolor , 2 ise iris-virginica  verilerini ifade edecek þekilde kodlanmýþtýr.

	int  veriAdet =0 ; // veri adeti txt deki boþ olmayan satýrlarýn adetini ifade eder. 5 ise verinin özelliklerini(sepalL,.., IrisName vs)
	int setler[3]={0,0,0};
	short k=1;
	// setler[0] = egitimSeti	setler[1] = dogrulamaSeti		setler[2] =  testSeti       
	int egitimSeti , dogrulamaSeti , testSeti; // setlerin indislerini tutmak için ; 
	bool ktespiti_izin=false; // normalizasyon yapmadan k tespiti yaptýrmayacaðým.
	bool shuffle_testi=false;
	char secim=5;
	char testVeriSecim;
	float dogrulukOrani=0.0; // testVeriSecim ile test setindeki veri tahmin edilirken bu deðiþken lazým olacak.
	
	
	Bilgi();
	system("color F0");  // konsolun rengi deðiþir
	
	veriAdet = veriOkuFonk(veriSeti); // bu fonksiyonda veriler okunup matris diziye atanýp veri adeti tespit edilecek.
	
	setlocale(LC_ALL, "Turkish");
	cout<<"\nBuradaki seçimlerde tavsiye edilen iþlem sýrasý þöyledir : 1 , 2 , 3 , 4 , 5 \n"<<endl;
	
	
	veriSetlereAyirFonk(&egitimSeti,&dogrulamaSeti,&testSeti,veriAdet);// veri setlere ayrýlmalý.
	
	while(true)
	{
		cout<<"\n\n\nVerilerin güncel halini listelemek için.................. 1 e bas "<<endl;
		cout<<"Verilerin normalize edilmesi için........................ 2 ye bas"<<endl;
		cout<<"Verilerin yerlerini karýþtýrmak(3 defa karýþtýrýlýr) için 3 e bas"<<endl;
		cout<<"K-Nearest Neighbor (en yakýn komþu) algoritmasý için..... 4 e bas"<<endl;
		cout<<"Konsol ekranýný temizlemek için ......................... 0 a bas"<<endl;
		cout<<"Programý bitirmek için .................................. 5 e bas"<<endl;
		
		secim=getch();
		
		if(secim=='1')
		{
			verileriYazdir(veriSeti,veriAdet,0); // bellekteki veri setinin anlýk olarak konsola basýlmasýný saðlar.
			// 0 gittiðinde bütün veriyi yazdirir.0.indisten baþlayarak yazdýrýr.
		}
		else if(secim=='2')
		{
			ktespiti_izin=true;
			standartizasyonfonk(veriSeti,veriAdet); // verilerin tahmine etkisinin ortak bir aðýrlýklandýrmada olmasýný saðlar.
		}
		else if(secim=='3')
		{
			shuffle_testi=true;
			getRandomFonk(veriSeti,veriAdet); // verilerin yerlerini rastgele olarak 3 defa karýþtýrýr.
		}
		else if(secim=='4' && ktespiti_izin==true)
		{
			if(shuffle_testi==false)
			{
				cout<<"\n\n\n\n\n\n\nÖNCE VERÝLERÝN "<<"KARIÞTIRILMASI TAVSÝYE EDÝLÝR ! \n";
			}
			k=enYakinKomsuAlgoritmasi(egitimSeti,veriAdet); // k deðeri alýnýyor.
			dogrulukOrani=komsulukFarkHesapla(k,egitimSeti,dogrulamaSeti,veriSeti,veriNitelik); // komþuluk farklarý hesaplanacak. ve tahminler listelenecek
			cout<<"\n\n\nTest setinden bir veriyi tahmin ettirmek için 9 a basýn\nMenüyü görüntülemek için herhangi bir tuþa bas:\n";
			testVeriSecim=getch();
			if(testVeriSecim=='9'){ testVeriFonk(k,egitimSeti,dogrulamaSeti,testSeti ,veriSeti,veriNitelik,dogrulukOrani); }
		}
		else if(secim=='4' && ktespiti_izin==false)
		{
			cout<<"\n\n\n\n\n\n\nÖNCE NORMALÝZASYON YAPMALISIN ! \n"; // normalize olmamýþ verilerde komþuluk farký hesabý yaptýrmýyorum.
		}
		else if(secim=='5')
		{
			break; // while döngüsünden çýkar ve program bitmiþ olur.
		}
		else if(secim=='0')
		{
			system("cls"); // konsol ekranýný temizler
		}
		else
		{
			cout<<"\n\nYanlýþ tuþlama yaptýn !"<<endl;
		}
	}

	KapanisBilgi();
	return 0;
}

