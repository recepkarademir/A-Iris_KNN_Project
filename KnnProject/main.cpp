/* 
	2018-12-10
	Recep KARADEM�R 
	
	IRIS  :  S�sengiller (Iris), Asparagales tak�m�na ait bir �i�ekli bitki familyas�d�r.

	Iris familyas�ndaki �� t�r�n temel �zelliklerinden olu�an veri seti yard�m�yla, 
	en iyi t�r tahmini yapan K(kom�uluk seviyesi) de�erini bulan C++ program� .
	
	
	Versiyon : V3.1.1
*/

#include <iostream>

#include <conio.h>	// getch()  i�in.
#include <locale.h>	// T�rk�e karakter ��kt�s� i�in.

#include "AnaSayfa.h"	// Program a��l���ndaki ve kapan���ndaki bilgi ekran� kod k�t�phanesi
#include "veriOku.h"	// verinin txt dosyas�ndan okunmas�n� sa�layan kod k�t�phanesi
#include "standartizasyon.h"	// b�t�n verilerin �zellik de�erlerini 0 ile 1 aras�na oranl� olarak s�k��t�ran kod k�t�phanesi
#include "veriYazdir.h"	// verilerin tamam�n� ve test seti verilerini yazd�ran k�t�phane
#include "getRandom.h"	// veri setinindeki verilerin yerlerini 3 kez rastgele olarak kar��t�ran kod k�t�phanesi
#include "veriSetlereAyir.h"	// veriyi �� sete (e�itim , do�rulama ve test) ay�ran kod k�t�phanesi
#include "KInput.h"	//  k de�erini kullan�c�dan alan kod k�t�phanesi
#include "Knn.h"	// en yak�n kom�u lagoritmas�n� �al��t�ran �ekirdek kod k�t�phanesi
#include "testVeri.h"	// test steinden bir verinin tahmin edilmesi g�revini yapan kod k�t�phanesi

using namespace std;

int main() 
{
	char secim , testVeriSecim;  
	// secim de�i�keni men� ekran�ndaki se�imleri kontrol edebilmek i�in. testVeriSecim test setindeki bir verinin tahmin edilmesi i�in kontrol ama�l�d�r.
	float veriSeti[150][5] , dogrulukOrani=-1.0;
	// test setindeki bir veri tahmin edilirken dogrulukOrani de�i�keni do�ru tahmin y�zdesi de�erini tutacak.
	short k=1; // kom�uluk seviyesi
	bool ktespiti_izin=false , shuffle_testi=false; // normalizasyon yapmadan k tespiti yapt�rmayaca��m. setleri kar��t�rma tavsiyesi i�in.
	int  veriNitelik=5 , veriAdet =0 , egitimSeti , dogrulamaSeti , testSeti; 
	/*  
		egitimSeti dogrulamaSeti testSeti  verilerin indislerini tutabilmek ve veri setini setlere ay�rmak i�in 
	 	veri adeti txt deki bo� olmayan sat�rlar�n adetini ifade eder. 
		veriNitelik ise verinin �zelliklerini(sepalL,.., IrisName vs) adetini ifade eder.
	 	veriSeti dizisinin 1.s�tunun da sepalL    2.s�tununda sepalW    3.s�tununda petalL     4.s�tununda petalW   5.s�tununda irisName  bulunacak.
	 	veriSeti dizisinin 1.sat�r�nda txtdeki ilk verinin bilgileri , n.sat�rda txt i�indeki n.sat�rdaki verinin bilgileri bulunur.
	 	irisName 0 ise iris-setosa , 1 ise iris-versicolor , 2 ise iris-virginica  verilerini ifade edecek �ekilde kodlanm��t�r.
	*/ 

	Bilgi();	// Program ba�lang�c�nda bilgi ekran� g�z�kecek.
	system("color F0");  // Konsolun rengi de�i�tirildi.
	
	veriAdet = veriOkuFonk(veriSeti); // bu fonksiyonda veriler okunup matris diziye atan�p veri adeti tespit edilecek.
	
	setlocale(LC_ALL, "Turkish");	// Konsol ekran�ndaki ��kt�lar�n t�rk�e olmas� sa�land�.
	cout<<"\nBuradaki se�imlerde tavsiye edilen i�lem s�ras� ��yledir : 1 , 2 , 3 , 4 , 5 \n"<<endl;
	
	
	veriSetlereAyirFonk(&egitimSeti,&dogrulamaSeti,&testSeti,veriAdet);// veri setlere(e�itim , do�rulama ve test) ayr�ld�.
	
	while(true) // Kullan�c�n�n mod�l se�im ekran�nda gezinebilmesini sa�layan d�ng�.
	{
		cout<<"\n\n\n";
		cout<<"Verilerin g�ncel halini listelemek i�in.................. 1 e bas "<<endl;
		cout<<"Verilerin normalize edilmesi i�in........................ 2 ye bas"<<endl;
		cout<<"Verilerin yerlerini kar��t�rmak(3 defa kar��t�r�l�r) i�in 3 e bas"<<endl;
		cout<<"K-Nearest Neighbor (en yak�n kom�u) algoritmas� i�in..... 4 e bas"<<endl;
		cout<<"Test setinden bir veriyi tahmin ettirmek i�in............ 5 e bas�n\n";
		cout<<"Konsol ekran�n� temizlemek i�in ......................... 0 a bas"<<endl;
		cout<<"Program� bitirmek i�in .................................. 6 ya bas"<<endl;
		
		secim=getch(); // kullan�c�dan mod�l se�imi al�n�yor 
		
		if(secim=='1')
		{
			verileriYazdir(veriSeti,veriAdet,0); // bellekteki veri setinin anl�k olarak konsola bas�lmas�n� sa�lar.
			// 0 gitti�inde b�t�n veriyi yazdirir. 0.indisten ba�layarak yazd�r�r.
			// 0 dan farkl� de�er gelirse, test setini yazd�rm�� olur.
		}
		else if(secim=='2')
		{
			ktespiti_izin=true; // true olur ��nk� art�k normalizasyon yap�lm�� olur.
			standartizasyonfonk(veriSeti,veriAdet); // verilerin tahmine etkisinin ortak bir a��rl�kland�rmada olmas�n� sa�lar.
		}
		else if(secim=='3')
		{
			shuffle_testi=true;	// kar��t�rma yap�ld��� i�in art�k kar��t�rma yapmal�s�n uyar�s�n� vermemesi i�in true yap�ld�.
			getRandomFonk(veriSeti,veriAdet); // verilerin yerlerini rastgele olarak 3 defa kar��t�r�r.
		}
		else if(secim=='4' && ktespiti_izin==false) // ktespiti_izin==true ise normalizasyon yap�lm��t�r ve knn algoritmas� �al��t�r�labilir.
		{
			cout<<"\n\n\n\n\n\n\n�NCE NORMAL�ZASYON YAPMALISIN ! \n"; // normalize olmam�� verilerde kom�uluk fark� hesab� yapt�rm�yorum.
		}
		else if(secim=='4' && ktespiti_izin==true)
		{
			if(shuffle_testi==false)	// shuffle_testi==true ise veri setindeki veriler rastgele olarak kar��t�r�lm��t�r.
			{
				cout<<"\n\n\n\n\n\n\n�NCE VER�LER�N KARI�TIRILMASI TAVS�YE ED�L�R ! \n";
			}
			
			k=enYakinKomsuAlgoritmasi(egitimSeti,veriAdet);	// k de�eri test setindeki tahmin ve knn algoritmas� i�in al�n�yor.
			dogrulukOrani=komsulukFarkHesapla(k,egitimSeti,dogrulamaSeti,veriSeti,veriNitelik);// kom�uluk farklar� hesaplanacak ve tahminler listelenecek
		}
		else if(secim=='5' && ktespiti_izin==false) // ktespiti_izin==true ise normalizasyon yap�lm��t�r ve knn algoritmas� �al��t�r�labilir.
		{
			cout<<"\n\n\n\n\n\n\n�NCE NORMAL�ZASYON YAPMALISIN ! \n"; // normalize olmam�� verilerde test seti tahmini yapt�rm�yorum.
		}
		else if(secim=='5' && ktespiti_izin==true)
		{
			// test setindeki veri tahmini yap�lmas� isteniyorsa 5 de�eri klavyeden giilmeli.
			testVeriFonk(egitimSeti,dogrulamaSeti,testSeti ,veriSeti,veriNitelik,dogrulukOrani,shuffle_testi,k);
			// testVeriFonk ile test setindeki bir verinin tahmini yap�l�r.
		}
		else if(secim=='6')
		{
			break; // while d�ng�s�nden ��kar ve program bitmi� olur. Program tamamen kapat�l�r.
		}
		else if(secim=='0')
		{
			system("cls"); // konsol ekran�n� temizler
		}
		else
		{
			cout<<"\n\nYanl�� tu�lama yapt�n !"<<endl; // kullan�c� men�deyken yanl�� bir mod�l kodu girerse bu uyar� verilir.
		}
	}

	KapanisBilgi(); // kullan�c� istedi�inde program bir mesajla sonland�r�lacak.
	return 0;
}
