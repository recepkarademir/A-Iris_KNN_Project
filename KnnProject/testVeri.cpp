#include <iostream>
#include <iomanip> 		// formatlý setw çýktýsý alabilmek için.
#include <conio.h>		// getc() için.
#include "veriYazdir.h"
#include "KInput.h"	//  k deðerini kullanýcýdan alan kod kütüphanesi

using namespace std;

void testVeriFonk(int egitimSeti,int dogrulamaSeti,int testSeti , float veriSeti[][5],int veriNitelik,float tahminYuzde,bool shuffle_testi, int kEgitim)
{
	int testVeriIndisi; // test setindeki tahmin edilecek verinin sýra numarasýný tutan deðiþken.
	system("cls");
	verileriYazdir(veriSeti,(egitimSeti+dogrulamaSeti+testSeti),(egitimSeti+dogrulamaSeti-1));
	cout<<"\nTest seti verileri yukarýdakilerdir.\n\n";
	if(shuffle_testi==false)	// shuffle_testi==true ise veri setindeki veriler rastgele olarak karýþtýrýlmýþtýr.
	{
		cout<<"\n\nÖNCE VERÝLERÝN KARIÞTIRILMASI TAVSÝYE EDÝLÝR ! \n";
	}
	while(true) // test setindeki sýra numarasý dýþýnda baþka bir deðer girilmemeli.
	{
		cout<<"\n============================================================================";
		cout<<"\nTest setindeki tahmin edilecek verinin sýra numarasýný gir ve entera bas :\n\n";
		cin>>testVeriIndisi;
		cout<<endl;
		
		if(testVeriIndisi<(egitimSeti+dogrulamaSeti) || testVeriIndisi>(egitimSeti+dogrulamaSeti+testSeti))
		{
			cout<< "\n\a Bu sýradaki veri test setinden deðil !"<<endl;
		}
		else
		{
			break; // istenilen aralýkta bir sýra numarasý giridiyse program iþlemeye devam etsin.
		}
	}
	int k=enYakinKomsuAlgoritmasi((egitimSeti+dogrulamaSeti),(egitimSeti+dogrulamaSeti+testSeti));
	
	testVeriIndisi--; // test setindeki tahmin edilecek verinin sýra numarasýný indis olarak iþlememiz gerekiyor.
	
	
	cout<<"\n\n============================================================================\n";
	cout<<"K = "<<k<<"  En yakýn "<<k<<" tane komþu incelendi ve tahminler yapýldý.";
	cout<<"\n\nTest setindeki verinin gerçek ve tahmini deðeri\n"<<endl;
	
	
	
	
	float tmpFark=0 , toplamFark=0; 
	// tmpFark : her hücre kýyaslama sonucunda bulunan farký tutar.        toplamFark:5 hücrenin tmpFark toplamlarýný tutar.
	
	float farkDizisi[1][(egitimSeti+dogrulamaSeti)];  // farklar bu dizide tutulacak
	// (egitimSeti+dogrulamaSeti) =113 deðerini tutuyor. 113 tane veri ile test setindeki verinin farklarý toplamý farkdizisinde saklanacak.
	// egitim seti [0..74] arasýnda , doðrulamseti [75..112] arasýnda   , testSeti  [113..149]  arasýnda
	
	
	for(int i=testVeriIndisi,j=0;j<(egitimSeti+dogrulamaSeti);++j)// test setindeki istenen veri için eðitim seti ve doðrulama setindeki bütün verilerden farkýný farkDizisinde tutmaya çalýþýyor. V2
	{
		tmpFark=0;
		toplamFark=0;
		tmpFark = ( (veriSeti[j][0]) - (veriSeti[i][0]) );
		if(tmpFark<0)
		{
			toplamFark+=(-1*tmpFark); // farklarýn negatif olmamasý gerekli. vektör uzaklýðý negatif olmaz.
		}
		else
		{
			toplamFark+=tmpFark;
		}
		
		tmpFark = ((veriSeti[j][1])  - (veriSeti[i][1]) );
		if(tmpFark<0)
		{
			toplamFark+=(-1*tmpFark); // farklarýn negatif olmamasý gerekli. vektör uzaklýðý negatif olmaz.
		}
		else
		{
			toplamFark+=tmpFark;
		}
		
		tmpFark = ( (veriSeti[j][2]) - (veriSeti[i][2]) );
		if(tmpFark<0)
		{
			toplamFark+=(-1*tmpFark); // farklarýn negatif olmamasý gerekli. vektör uzaklýðý negatif olmaz.
		}
		else
		{
			toplamFark+=tmpFark;
		}
		
		tmpFark = ( (veriSeti[j][3]) - (veriSeti[i][3]) );
		if(tmpFark<0)
		{
			toplamFark+=(-1*tmpFark); // farklarýn negatif olmamasý gerekli. vektör uzaklýðý negatif olmaz.
		}
		else
		{
			toplamFark+=tmpFark;
		}
		farkDizisi[0][j] = toplamFark;	
	}




	float geciciFark[1][(egitimSeti+dogrulamaSeti)];
	// veriler en yakýn komþu hesaplarken bozuluyor. Korunmasý ve guncel veri seti listelemesinin yapýldýðýnda bozulmuþ verilerin görünmemesi için.
	// çok boyutlu bir dizi kopyalanýrken copy() kullanýlabilir. memcpy() de kullanýlabilir
	copy(&farkDizisi[0][0], &farkDizisi[0][0]+(egitimSeti+dogrulamaSeti),&geciciFark[0][0]); // dizi tamamen klonlanýyor.
	// geciciFark dizisi test edilecek veri için en yakýn k tane komþusunun indisini tutuyor.
	
	
	
	/*BU YORUM BLOÐU KONTROL AMAÇLI YAZILMIÞTIR
	
	
	int asda=0;
	for(int a=0;a<(egitimSeti+dogrulamaSeti);++a)
	{
		if(farkDizisi[0][a]!=geciciFark[0][a])
		{
			asda++; // 0 çýkarsa iki dizi eþittir.
		}
		
	}
	cout<<"\n\n\n\n"<<asda<<"\n\n\n\n";
	*/
	
	
	float degistir=(float)veriNitelik; // degiþtir 5 oldu. 5 niteliðin(sepalW vs.) toplamý olduðu için en fazla fark toplamý 5 olduðunda komþu bulma iþlemi bu indiste yapýlmýþ demektir V2
	float kucukSayi; // her kontrolde küçük sayýyý tutup diziye yazdýracaðýz.
	int kucukVeriIndis;
	int enKucukKNN[1][k]; // en yakýn komþularýn indislerinin tutulduðu yapý. 
	

	for(int z=0;z<k;++z) // k  defa kontrol yapýp k tane sütunu doldurulacak. bu for ikinci defa  çalýþtýðýnda en küçük ikinci knn komþunun indisi alýnacak
	{
		kucukSayi = geciciFark[0][0];
		kucukVeriIndis = 0;
		
		for(int j=0;j<(egitimSeti+dogrulamaSeti);++j) // j= (egitimSeti+dogrulamaSeti) a kadar gidecek.
		{
			if(geciciFark[0][j] <= kucukSayi) // <=  alýrýz çünkü = olan en yakýn komþusu da olabilir.
			{
				kucukSayi=geciciFark[0][j];//kucukSayi dan daha kucuk deger varsa kSayi ile deðiþtirilir.
				kucukVeriIndis=j;// (egitimSeti+dogrulamaSeti) ndeki yakýn komþunun indisi j 'de  tutulur.
			}
		}
		geciciFark[0][kucukVeriIndis]+=100;// dizideki deðeri 5 yapýlýr. 5 yapýlýr çünkü en kucuk 2.  3.  4. vs aramalarda tekrar en kucuk diye yakalanmamasý için.
		// 5 yapýldýðýnda en küçük fark olarak 5ten küçük veriler mutlaka geciciFark[0][kucukVeriIndis] e atanýr.
		enKucukKNN[0][z]=kucukVeriIndis; // en kucuk deðerin indisi yedeklendi.
	}

	/* TEST AMAÇLI
	
	int b;
	for(int a=0;a<k;++a)
	{
		b=enKucukKNN[0][a];
		cout<<geciciFark[0][b]<<endl;
	}
	
	*/

	int tahmin[1][3]={{0,0,0}}; // tahmin edilecek verinin hangi iris deðeri en baskýn onu tutacak.
 	// iris adetlerini tutan dizinin baþlangýçta 0 deðerleri tutmasý gerekir.

	
	
		
	short irisKodu; // en yakýn komþunun veri setindeki iris kodunu geçici tutmak için.
	
		for(int j=0;j<k;++j) // her sütundaki iris adýný kontrol edip iris adlarýnýn sayýsýný tahmin dizisinde tutuyor.
		{
			// enKucukKNN[i][j] = en küçük verilerin konumlarýnýn tutulduklarý dizi. 
			irisKodu = veriSeti[(enKucukKNN[0][j])][4];// bu satýrda en yakýn komþunun veri setindeki iris kodunu öðrenmemizi saðlar.4 =iris adýnýn tutulduðu sütünlar
			if(irisKodu==0)
			{
				tahmin[0][0]++;
			}
			else if(irisKodu==1)
			{
				tahmin[0][1]++;
			}
			else if(irisKodu==2)
			{
				tahmin[0][2]++;
			}
			else
			{
				cout<<"\nIris ismi bellekte düzgün olarak kodlanmamýþ ! \n";
			}
		}
				
	// TEST AMAÇLI
	/*for(int a=0;a<3;++a)
	{
		
		cout<<tahmin[0][a]<<endl;
	}*/
	
	int agirlikliTahmin[1][1];
	int enBuyuk=0 , enBuyukIndis=0; // burada iris adýnýn aðýrlýklý olarak hangisi olduðunu buluyoruz.

		enBuyuk = tahmin[0][0];
		for(int r=0;r<3;++r)
		{
			if(tahmin[0][r]>=enBuyuk)
			{
				enBuyuk=tahmin[0][r];
				enBuyukIndis=r;
			}
		}
		
		if(enBuyukIndis==0) // en agirlikli iris adý taminini karar olarak kaydediyor.
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
	
		float tahminYuzdeTest=0.0;
		 
		tahminYuzdeTest = (100.0/k)*tahmin[0][enBuyukIndis];
		// þimdi orijinal test edilecek test verisinin iris adýyla tahmin yüzdesini çýktý olarak verelim.
		cout<<endl<<setw(3)<<testVeriIndisi+1<<". sýra ("<<setw(3)<<testVeriIndisi<<".indisteki)"<<" Test verisinin iris adý : "<<setw(14);

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
		
		cout<<"   "<<"Tahmin edilen iris adý : "<<setw(14);
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
		if(veriSeti[testVeriIndisi][4]==agirlikliTahmin[0][0])
		{
			cout<<endl;
		}
		else
		{
			cout<<" X "<<endl;
		}
		

	cout<<"\n\n============================================================================\n";
	if(tahminYuzde==-1.0)
	{
		cout<<"Programýn genel tahmin doðruluk oraný bilinmiyor !"<<endl;
	}
	else
	{
		cout<<"Programýn genel tahmin doðruluk oraný  k = "<<kEgitim<<" için  % "<<tahminYuzde<<endl;
	}
	
	cout<<"Test setindeki verinin k="<<k<<" için tahmin doðruluk oraný % "<<tahminYuzdeTest<<endl;
	cout<<"Yanlýþ tahminin yanýnda X bulunur.\n============================================================================\n";
	cout<<"\nDevam etmek için bir tuþa bas...";
	
	system("pause");
}
