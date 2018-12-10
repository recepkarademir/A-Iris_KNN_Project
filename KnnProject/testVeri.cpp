#include <iostream>
#include <iomanip> 		// formatlý setw çýktýsý alabilmek için.
#include "testVeri.h"
#include "veriYazdir.h"
#include <conio.h>		// getc() için.
using namespace std;

void testVeriFonk(int k,int egitimSeti,int dogrulamaSeti,int testSeti , float veriSeti[][5],int veriNitelik,float tahminYuzde)// komþuluk farklarý hesaplanacak.
{
	int testVeriIndisi;
	
	system("cls");
	verileriYazdir(veriSeti,(egitimSeti+dogrulamaSeti+testSeti),(egitimSeti+dogrulamaSeti-1));
	
	while(true)
	{
		cout<<"\n\n============================================================================";
		cout<<"\nTest setindeki tahmin edilecek verinin sýra numarasýný gir ve entera bas :\n\n";
		cin>>testVeriIndisi;
		cout<<endl;
		if(testVeriIndisi<(egitimSeti+dogrulamaSeti) || testVeriIndisi>(egitimSeti+dogrulamaSeti+testSeti))
		{
			cout<< "\n\a Bu sýradaki veri test setinden deðil !"<<endl;
		}
		else
		{
			break;
		}
	}
	
	
	testVeriIndisi--;
	
	//SONUNDA V2 YAZAN YORUMLAR GÜNCEL
	
	
	
	cout<<"\n\n============================================================================\n";
	cout<<"K = "<<k<<"  En yakýn "<<k<<" tane komþu incelendi ve tahminler yapýldý.";
	cout<<"\n\nTest setindeki verinin gerçek ve tahmini deðeri\n"<<endl;
	
	
	
	
	float tmpFark=0 , toplamFark=0; // tmpFark : her hücre kýyaslama sonucunda bulunan farký tutar.        toplamFark:5 hücrenin tmpFark toplamlarýný tutar.V2
	// egitim seti verileri veri seti karýþýk olduðu için ilk [0..74] elemanlarý olarak kullanýlacak.
	// eðitim seti deðeri 150 tane veri için þuan 75 ,  dogrulamaSeti=38 ve testSeti=37 olacaktýr.
	float farkDizisi[1][(egitimSeti+dogrulamaSeti)];  // farklar bu dizide tutulacak
	// egitimSeti=75 deðerini tutuyor.   
	int sutun=0;
	// egitim seti [0..74] arasýnda , doðrulamseti [75..112] arasýnda   , testSeti  [113..149]  arasýnda
	
	
	for(int i=testVeriIndisi,j=0;j<(egitimSeti+dogrulamaSeti);++j)// test setindeki istenen veri için eðitim seti ve doðrulama setindeki bütün verilerden farkýný farkDizisinde tutmaya çalýþýyor. V2
	{
		tmpFark=0;
		toplamFark=0;
		tmpFark = ( (veriSeti[j][sutun]) - (veriSeti[i][sutun]) );
		if(tmpFark<0)
		{
			toplamFark+=(-1*tmpFark); // farklarýn negatif olmamasý gerekli. vektör uzaklýðý negatif olmaz.
		}
		else
		{
			toplamFark+=tmpFark;
		}
		
		tmpFark = ((veriSeti[j][sutun+1])  - (veriSeti[i][sutun+1]) );
		if(tmpFark<0)
		{
			toplamFark+=(-1*tmpFark); // farklarýn negatif olmamasý gerekli. vektör uzaklýðý negatif olmaz.
		}
		else
		{
			toplamFark+=tmpFark;
		}
		
		tmpFark = ( (veriSeti[j][sutun+2]) - (veriSeti[i][sutun+2]) );
		if(tmpFark<0)
		{
			toplamFark+=(-1*tmpFark); // farklarýn negatif olmamasý gerekli. vektör uzaklýðý negatif olmaz.
		}
		else
		{
			toplamFark+=tmpFark;
		}
		
		tmpFark = ( (veriSeti[j][sutun+3]) - (veriSeti[i][sutun+3]) );
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
	
	// çok boyutlu bir dizi kopyalanýrken copy() kullanýlabilir. memcpy() de kullanýlabilir V2
	copy(&farkDizisi[0][0], &farkDizisi[0][0]+(egitimSeti+dogrulamaSeti),&geciciFark[0][0]); // dizi tamamen klonlanýyor.
	// geciciFark dizisi her doðrulama verisi için en yakýn k tane komþusunun indisini tutuyor.
	
	
	
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
			
			for(int j=0;j<egitimSeti;++j) // j= egitimSeti
			{
				if(geciciFark[0][j] <= kucukSayi) // <=  alýrýz çünkü = olan en yakýn komþusu da olabilir.
				{
					kucukSayi=geciciFark[0][j];//kucukSayi dan daha kucuk deger varsa kSayi ile deðiþtirilir.
					kucukVeriIndis=j;// eðitim setindeki yakýn komþunun indisi j 'de  tutulur.
				}
			}
			geciciFark[0][kucukVeriIndis]=degistir;// dizideki deðeri 5 yapýlýr. 5 yapýlýr çünkü en kucuk 2.  3.  4. vs aramalarda tekrar en kucuk diye yakalanmamasý için.
			enKucukKNN[0][z]=kucukVeriIndis; // en kucuk deðerin indisi yedeklendi.
		}




	int tahmin[1][3]; // doðrulama setinin hangi iris deðeri en fazla  tahmin yapýlýyor onu tutacak.
	
 // iris adetlerini tutan dizinin baþlangýçta 0 deðerleri tutmasý gerekir.
	
		tahmin[0][0]=0;
		tahmin[0][1]=0;
		tahmin[0][2]=0;
	
	
		
	short irisKodu; // en yakýn komþunun veri setindeki iris kodunu geçici tutmak için.
	
	
		for(int j=0;j<k;++j) // her sütundaki iris adýný kontrol edip iris adlarýnýn sayýsýný tahmin dizisinde tutuyor.
		{
			// enKucukKNN[i][j] = en küçük verilerin konumlarýnýn tutulduklarý dizi. 
			irisKodu = veriSeti[(enKucukKNN[0][j])][4];// bu satýr en yakýn komþunun veri setindeki iris kodunu öðrenmemizi saðlýyor.  4  = iris adýnýn tutulduðu sütünlar
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
				cout<<"\nIris ismi bellekte düzgün olarak kodlanmamýþ ! \n";
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
	
	// þimdi orijinal doðrulamadaki iris adýyla tahmin iris adlarýný kýyaslayýp tahmin yüzdesini çýktý olarak verelim.
	
		cout<<endl;
		
		cout<<setw(3)<<testVeriIndisi+1<<". sýra ("<<setw(3)<<testVeriIndisi<<".indisteki)"<<" Doðrulama verisinin iris adý : "<<setw(17);

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
		
		cout<<"  "<<"Tahmin edilen iris adý : "<<setw(17);
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
		if(veriSeti[testVeriIndisi][4]==agirlikliTahmin[0][0]) // her doðru tahmin için tahmin yüzdesi artýrýlýr.
		{
			cout<<endl;
		}
		else
		{
			cout<<" X "<<endl;
		}
		

	cout<<"\n\n============================================================================\n";	
	cout<<"Doðruluk oraný % "<<tahminYuzde<<endl;
	cout<<"Yanlýþ tahminin yanýnda X bulunur.\n============================================================================\n";
	cout<<"\nDevam etmek için bir tuþa bas...";
	
	system("pause");
}
