/* 
	2018-12-10
	Recep KARADEMÝR 
	
	IRIS  :  Süsengiller (Iris), Asparagales takýmýna ait bir çiçekli bitki familyasýdýr.

	Iris familyasýndaki üç türün temel özelliklerinden oluþan veri seti yardýmýyla, 
	en iyi tür tahmini yapan K(komþuluk seviyesi) deðerini bulan C++ programý .
	
	
	Versiyon : V3.1.1
*/

#include <iostream>

#include <conio.h>	// getch()  için.
#include <locale.h>	// Türkçe karakter çýktýsý için.

#include "AnaSayfa.h"	// Program açýlýþýndaki ve kapanýþýndaki bilgi ekraný kod kütüphanesi
#include "veriOku.h"	// verinin txt dosyasýndan okunmasýný saðlayan kod kütüphanesi
#include "standartizasyon.h"	// bütün verilerin özellik deðerlerini 0 ile 1 arasýna oranlý olarak sýkýþtýran kod kütüphanesi
#include "veriYazdir.h"	// verilerin tamamýný ve test seti verilerini yazdýran kütüphane
#include "getRandom.h"	// veri setinindeki verilerin yerlerini 3 kez rastgele olarak karýþtýran kod kütüphanesi
#include "veriSetlereAyir.h"	// veriyi üç sete (eðitim , doðrulama ve test) ayýran kod kütüphanesi
#include "KInput.h"	//  k deðerini kullanýcýdan alan kod kütüphanesi
#include "Knn.h"	// en yakýn komþu lagoritmasýný çalýþtýran çekirdek kod kütüphanesi
#include "testVeri.h"	// test steinden bir verinin tahmin edilmesi görevini yapan kod kütüphanesi

using namespace std;

int main() 
{
	char secim , testVeriSecim;  
	// secim deðiþkeni menü ekranýndaki seçimleri kontrol edebilmek için. testVeriSecim test setindeki bir verinin tahmin edilmesi için kontrol amaçlýdýr.
	float veriSeti[150][5] , dogrulukOrani=-1.0;
	// test setindeki bir veri tahmin edilirken dogrulukOrani deðiþkeni doðru tahmin yüzdesi deðerini tutacak.
	short k=1; // komþuluk seviyesi
	bool ktespiti_izin=false , shuffle_testi=false; // normalizasyon yapmadan k tespiti yaptýrmayacaðým. setleri karýþtýrma tavsiyesi için.
	int  veriNitelik=5 , veriAdet =0 , egitimSeti , dogrulamaSeti , testSeti; 
	/*  
		egitimSeti dogrulamaSeti testSeti  verilerin indislerini tutabilmek ve veri setini setlere ayýrmak için 
	 	veri adeti txt deki boþ olmayan satýrlarýn adetini ifade eder. 
		veriNitelik ise verinin özelliklerini(sepalL,.., IrisName vs) adetini ifade eder.
	 	veriSeti dizisinin 1.sütunun da sepalL    2.sütununda sepalW    3.sütununda petalL     4.sütununda petalW   5.sütununda irisName  bulunacak.
	 	veriSeti dizisinin 1.satýrýnda txtdeki ilk verinin bilgileri , n.satýrda txt içindeki n.satýrdaki verinin bilgileri bulunur.
	 	irisName 0 ise iris-setosa , 1 ise iris-versicolor , 2 ise iris-virginica  verilerini ifade edecek þekilde kodlanmýþtýr.
	*/ 

	Bilgi();	// Program baþlangýcýnda bilgi ekraný gözükecek.
	system("color F0");  // Konsolun rengi deðiþtirildi.
	
	veriAdet = veriOkuFonk(veriSeti); // bu fonksiyonda veriler okunup matris diziye atanýp veri adeti tespit edilecek.
	
	setlocale(LC_ALL, "Turkish");	// Konsol ekranýndaki çýktýlarýn türkçe olmasý saðlandý.
	cout<<"\nBuradaki seçimlerde tavsiye edilen iþlem sýrasý þöyledir : 1 , 2 , 3 , 4 , 5 \n"<<endl;
	
	
	veriSetlereAyirFonk(&egitimSeti,&dogrulamaSeti,&testSeti,veriAdet);// veri setlere(eðitim , doðrulama ve test) ayrýldý.
	
	while(true) // Kullanýcýnýn modül seçim ekranýnda gezinebilmesini saðlayan döngü.
	{
		cout<<"\n\n\n";
		cout<<"Verilerin güncel halini listelemek için.................. 1 e bas "<<endl;
		cout<<"Verilerin normalize edilmesi için........................ 2 ye bas"<<endl;
		cout<<"Verilerin yerlerini karýþtýrmak(3 defa karýþtýrýlýr) için 3 e bas"<<endl;
		cout<<"K-Nearest Neighbor (en yakýn komþu) algoritmasý için..... 4 e bas"<<endl;
		cout<<"Test setinden bir veriyi tahmin ettirmek için............ 5 e basýn\n";
		cout<<"Konsol ekranýný temizlemek için ......................... 0 a bas"<<endl;
		cout<<"Programý bitirmek için .................................. 6 ya bas"<<endl;
		
		secim=getch(); // kullanýcýdan modül seçimi alýnýyor 
		
		if(secim=='1')
		{
			verileriYazdir(veriSeti,veriAdet,0); // bellekteki veri setinin anlýk olarak konsola basýlmasýný saðlar.
			// 0 gittiðinde bütün veriyi yazdirir. 0.indisten baþlayarak yazdýrýr.
			// 0 dan farklý deðer gelirse, test setini yazdýrmýþ olur.
		}
		else if(secim=='2')
		{
			ktespiti_izin=true; // true olur çünkü artýk normalizasyon yapýlmýþ olur.
			standartizasyonfonk(veriSeti,veriAdet); // verilerin tahmine etkisinin ortak bir aðýrlýklandýrmada olmasýný saðlar.
		}
		else if(secim=='3')
		{
			shuffle_testi=true;	// karýþtýrma yapýldýðý için artýk karýþtýrma yapmalýsýn uyarýsýný vermemesi için true yapýldý.
			getRandomFonk(veriSeti,veriAdet); // verilerin yerlerini rastgele olarak 3 defa karýþtýrýr.
		}
		else if(secim=='4' && ktespiti_izin==false) // ktespiti_izin==true ise normalizasyon yapýlmýþtýr ve knn algoritmasý çalýþtýrýlabilir.
		{
			cout<<"\n\n\n\n\n\n\nÖNCE NORMALÝZASYON YAPMALISIN ! \n"; // normalize olmamýþ verilerde komþuluk farký hesabý yaptýrmýyorum.
		}
		else if(secim=='4' && ktespiti_izin==true)
		{
			if(shuffle_testi==false)	// shuffle_testi==true ise veri setindeki veriler rastgele olarak karýþtýrýlmýþtýr.
			{
				cout<<"\n\n\n\n\n\n\nÖNCE VERÝLERÝN KARIÞTIRILMASI TAVSÝYE EDÝLÝR ! \n";
			}
			
			k=enYakinKomsuAlgoritmasi(egitimSeti,veriAdet);	// k deðeri test setindeki tahmin ve knn algoritmasý için alýnýyor.
			dogrulukOrani=komsulukFarkHesapla(k,egitimSeti,dogrulamaSeti,veriSeti,veriNitelik);// komþuluk farklarý hesaplanacak ve tahminler listelenecek
		}
		else if(secim=='5' && ktespiti_izin==false) // ktespiti_izin==true ise normalizasyon yapýlmýþtýr ve knn algoritmasý çalýþtýrýlabilir.
		{
			cout<<"\n\n\n\n\n\n\nÖNCE NORMALÝZASYON YAPMALISIN ! \n"; // normalize olmamýþ verilerde test seti tahmini yaptýrmýyorum.
		}
		else if(secim=='5' && ktespiti_izin==true)
		{
			// test setindeki veri tahmini yapýlmasý isteniyorsa 5 deðeri klavyeden giilmeli.
			testVeriFonk(egitimSeti,dogrulamaSeti,testSeti ,veriSeti,veriNitelik,dogrulukOrani,shuffle_testi,k);
			// testVeriFonk ile test setindeki bir verinin tahmini yapýlýr.
		}
		else if(secim=='6')
		{
			break; // while döngüsünden çýkar ve program bitmiþ olur. Program tamamen kapatýlýr.
		}
		else if(secim=='0')
		{
			system("cls"); // konsol ekranýný temizler
		}
		else
		{
			cout<<"\n\nYanlýþ tuþlama yaptýn !"<<endl; // kullanýcý menüdeyken yanlýþ bir modül kodu girerse bu uyarý verilir.
		}
	}

	KapanisBilgi(); // kullanýcý istediðinde program bir mesajla sonlandýrýlacak.
	return 0;
}
