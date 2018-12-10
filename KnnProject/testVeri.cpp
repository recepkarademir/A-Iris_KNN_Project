#include <iostream>
#include <iomanip> 		// formatl� setw ��kt�s� alabilmek i�in.
#include "testVeri.h"
#include "veriYazdir.h"
#include <conio.h>		// getc() i�in.
using namespace std;

void testVeriFonk(int k,int egitimSeti,int dogrulamaSeti,int testSeti , float veriSeti[][5],int veriNitelik,float tahminYuzde)// kom�uluk farklar� hesaplanacak.
{
	int testVeriIndisi;
	
	system("cls");
	verileriYazdir(veriSeti,(egitimSeti+dogrulamaSeti+testSeti),(egitimSeti+dogrulamaSeti-1));
	
	while(true)
	{
		cout<<"\n\n============================================================================";
		cout<<"\nTest setindeki tahmin edilecek verinin s�ra numaras�n� gir ve entera bas :\n\n";
		cin>>testVeriIndisi;
		cout<<endl;
		if(testVeriIndisi<(egitimSeti+dogrulamaSeti) || testVeriIndisi>(egitimSeti+dogrulamaSeti+testSeti))
		{
			cout<< "\n\a Bu s�radaki veri test setinden de�il !"<<endl;
		}
		else
		{
			break;
		}
	}
	
	
	testVeriIndisi--;
	
	//SONUNDA V2 YAZAN YORUMLAR G�NCEL
	
	
	
	cout<<"\n\n============================================================================\n";
	cout<<"K = "<<k<<"  En yak�n "<<k<<" tane kom�u incelendi ve tahminler yap�ld�.";
	cout<<"\n\nTest setindeki verinin ger�ek ve tahmini de�eri\n"<<endl;
	
	
	
	
	float tmpFark=0 , toplamFark=0; // tmpFark : her h�cre k�yaslama sonucunda bulunan fark� tutar.        toplamFark:5 h�crenin tmpFark toplamlar�n� tutar.V2
	// egitim seti verileri veri seti kar���k oldu�u i�in ilk [0..74] elemanlar� olarak kullan�lacak.
	// e�itim seti de�eri 150 tane veri i�in �uan 75 ,  dogrulamaSeti=38 ve testSeti=37 olacakt�r.
	float farkDizisi[1][(egitimSeti+dogrulamaSeti)];  // farklar bu dizide tutulacak
	// egitimSeti=75 de�erini tutuyor.   
	int sutun=0;
	// egitim seti [0..74] aras�nda , do�rulamseti [75..112] aras�nda   , testSeti  [113..149]  aras�nda
	
	
	for(int i=testVeriIndisi,j=0;j<(egitimSeti+dogrulamaSeti);++j)// test setindeki istenen veri i�in e�itim seti ve do�rulama setindeki b�t�n verilerden fark�n� farkDizisinde tutmaya �al���yor. V2
	{
		tmpFark=0;
		toplamFark=0;
		tmpFark = ( (veriSeti[j][sutun]) - (veriSeti[i][sutun]) );
		if(tmpFark<0)
		{
			toplamFark+=(-1*tmpFark); // farklar�n negatif olmamas� gerekli. vekt�r uzakl��� negatif olmaz.
		}
		else
		{
			toplamFark+=tmpFark;
		}
		
		tmpFark = ((veriSeti[j][sutun+1])  - (veriSeti[i][sutun+1]) );
		if(tmpFark<0)
		{
			toplamFark+=(-1*tmpFark); // farklar�n negatif olmamas� gerekli. vekt�r uzakl��� negatif olmaz.
		}
		else
		{
			toplamFark+=tmpFark;
		}
		
		tmpFark = ( (veriSeti[j][sutun+2]) - (veriSeti[i][sutun+2]) );
		if(tmpFark<0)
		{
			toplamFark+=(-1*tmpFark); // farklar�n negatif olmamas� gerekli. vekt�r uzakl��� negatif olmaz.
		}
		else
		{
			toplamFark+=tmpFark;
		}
		
		tmpFark = ( (veriSeti[j][sutun+3]) - (veriSeti[i][sutun+3]) );
		if(tmpFark<0)
		{
			toplamFark+=(-1*tmpFark); // farklar�n negatif olmamas� gerekli. vekt�r uzakl��� negatif olmaz.
		}
		else
		{
			toplamFark+=tmpFark;
		}
		farkDizisi[0][j] = toplamFark;	
	}




	float geciciFark[1][(egitimSeti+dogrulamaSeti)];
	// veriler en yak�n kom�u hesaplarken bozuluyor. Korunmas� ve guncel veri seti listelemesinin yap�ld���nda bozulmu� verilerin g�r�nmemesi i�in.
	
	// �ok boyutlu bir dizi kopyalan�rken copy() kullan�labilir. memcpy() de kullan�labilir V2
	copy(&farkDizisi[0][0], &farkDizisi[0][0]+(egitimSeti+dogrulamaSeti),&geciciFark[0][0]); // dizi tamamen klonlan�yor.
	// geciciFark dizisi her do�rulama verisi i�in en yak�n k tane kom�usunun indisini tutuyor.
	
	
	
	/*BU YORUM BLO�U KONTROL AMA�LI YAZILMI�TIR
	
	
	int asda=0;
	for(int a=0;a<(egitimSeti+dogrulamaSeti);++a)
	{
		if(farkDizisi[0][a]!=geciciFark[0][a])
		{
			asda++; // 0 ��karsa iki dizi e�ittir.
		}
		
	}
	cout<<"\n\n\n\n"<<asda<<"\n\n\n\n";
	*/
	

	
	float degistir=(float)veriNitelik; // degi�tir 5 oldu. 5 niteli�in(sepalW vs.) toplam� oldu�u i�in en fazla fark toplam� 5 oldu�unda kom�u bulma i�lemi bu indiste yap�lm�� demektir V2
	float kucukSayi; // her kontrolde k���k say�y� tutup diziye yazd�raca��z.
	int kucukVeriIndis;
	int enKucukKNN[1][k]; // en yak�n kom�ular�n indislerinin tutuldu�u yap�. 
	
	
	
		for(int z=0;z<k;++z) // k  defa kontrol yap�p k tane s�tunu doldurulacak. bu for ikinci defa  �al��t���nda en k���k ikinci knn kom�unun indisi al�nacak
		{
			kucukSayi = geciciFark[0][0];
			kucukVeriIndis = 0;
			
			for(int j=0;j<egitimSeti;++j) // j= egitimSeti
			{
				if(geciciFark[0][j] <= kucukSayi) // <=  al�r�z ��nk� = olan en yak�n kom�usu da olabilir.
				{
					kucukSayi=geciciFark[0][j];//kucukSayi dan daha kucuk deger varsa kSayi ile de�i�tirilir.
					kucukVeriIndis=j;// e�itim setindeki yak�n kom�unun indisi j 'de  tutulur.
				}
			}
			geciciFark[0][kucukVeriIndis]=degistir;// dizideki de�eri 5 yap�l�r. 5 yap�l�r ��nk� en kucuk 2.  3.  4. vs aramalarda tekrar en kucuk diye yakalanmamas� i�in.
			enKucukKNN[0][z]=kucukVeriIndis; // en kucuk de�erin indisi yedeklendi.
		}




	int tahmin[1][3]; // do�rulama setinin hangi iris de�eri en fazla  tahmin yap�l�yor onu tutacak.
	
 // iris adetlerini tutan dizinin ba�lang��ta 0 de�erleri tutmas� gerekir.
	
		tahmin[0][0]=0;
		tahmin[0][1]=0;
		tahmin[0][2]=0;
	
	
		
	short irisKodu; // en yak�n kom�unun veri setindeki iris kodunu ge�ici tutmak i�in.
	
	
		for(int j=0;j<k;++j) // her s�tundaki iris ad�n� kontrol edip iris adlar�n�n say�s�n� tahmin dizisinde tutuyor.
		{
			// enKucukKNN[i][j] = en k���k verilerin konumlar�n�n tutulduklar� dizi. 
			irisKodu = veriSeti[(enKucukKNN[0][j])][4];// bu sat�r en yak�n kom�unun veri setindeki iris kodunu ��renmemizi sa�l�yor.  4  = iris ad�n�n tutuldu�u s�t�nlar
			if(irisKodu==0)
			{
				tahmin[0][0] = ( ( tahmin[0][0]) +1 );
			}
			else if(irisKodu==1)
			{
				tahmin[0][1] = ( ( tahmin[0][1]) +1 );
			}
			else if(irisKodu==2)
			{
				tahmin[0][2] = ( ( tahmin[0][2]) +1 );
			}
			else
			{
				cout<<"\nIris ismi bellekte d�zg�n olarak kodlanmam�� ! \n";
			}
		}		
	

	
	int agirlikliTahmin[1][1];
	int enBuyuk=0 , enBuyukIndis=0;
						
	enBuyuk = tahmin[0][0];
	

		enBuyuk = tahmin[0][0];
		for(int r=0;r<3;++r)
		{
			if(tahmin[0][r]>=enBuyuk)
			{
				enBuyuk=tahmin[0][r];
				enBuyukIndis=r;
			}
		}
		if(enBuyukIndis==0) // en agirlikli iris ad� taminini karar olarak kaydediyor.
		{
			agirlikliTahmin[0][0]=0;
		}
		else if(enBuyukIndis==1)
		{
			agirlikliTahmin[0][0]=1;
		}
		else if(enBuyukIndis==2)
		{
			agirlikliTahmin[0][0]=2;
		}
	
	// �imdi orijinal do�rulamadaki iris ad�yla tahmin iris adlar�n� k�yaslay�p tahmin y�zdesini ��kt� olarak verelim.
	
		cout<<endl;
		
		cout<<setw(3)<<testVeriIndisi+1<<". s�ra ("<<setw(3)<<testVeriIndisi<<".indisteki)"<<" Do�rulama verisinin iris ad� : "<<setw(17);

		if(veriSeti[testVeriIndisi][4]==0)
		{
			cout<<"Iris-setosa";
		}
		else if(veriSeti[testVeriIndisi][4]==1)
		{
			cout<<"Iris-versicolor";
		}
		else if(veriSeti[testVeriIndisi][4]==2)
		{
			cout<<"Iris-virginica";
		}
		
		cout<<"  "<<"Tahmin edilen iris ad� : "<<setw(17);
		if(agirlikliTahmin[0][0]==0)
		{
			cout<<"Iris-setosa";
		}
		else if(agirlikliTahmin[0][0]==1)
		{
			cout<<"Iris-versicolor";
		}
		else if(agirlikliTahmin[0][0]==2)
		{
			cout<<"Iris-virginica";
		}
		if(veriSeti[testVeriIndisi][4]==agirlikliTahmin[0][0]) // her do�ru tahmin i�in tahmin y�zdesi art�r�l�r.
		{
			cout<<endl;
		}
		else
		{
			cout<<" X "<<endl;
		}
		

	cout<<"\n\n============================================================================\n";	
	cout<<"Do�ruluk oran� % "<<tahminYuzde<<endl;
	cout<<"Yanl�� tahminin yan�nda X bulunur.\n============================================================================\n";
	cout<<"\nDevam etmek i�in bir tu�a bas...";
	
	system("pause");
}
