#include <iostream>
#include <iomanip> 		// formatlý setw çýktýsý alabilmek için.
#include <conio.h>		// getch() için.
using namespace std;

float komsulukFarkHesapla(int k,int egitimSeti,int dogrulamaSeti, float veriSeti[][5],int veriNitelik)// komþuluk farklarý hesaplanacak.
{
	//veriSeti adresi yeni bir diziye atanýyor. Artýk yeni ve orijinal dizi birbirinden etkilenir.
	system("cls");
	cout<<"K = "<<k<<"  En yakýn "<<k<<" tane komþu incelendi ve tahminler yapýldý.";
	
	float tmpFark=0 , toplamFark=0;
	// egitim seti verileri veri seti karýþýk olduðu için ilk [0..74] elemanlarý olarak kullanýlacak.
	float farkDizisi[dogrulamaSeti][egitimSeti];  // farklar bu dizide tutulacak
	// egitimSeti=75 deðerini tutuyor.   
	// egitim seti [0..74] arasýnda , doðrulamseti [75..112] arasýnda   , testSeti  [113..149]  arasýnda
	
	
	for(int z=0 , i=(egitimSeti);z<dogrulamaSeti;++z , ++i) // doðrulama veri setindeki her satýrdaki veriler için deðerlerinin eðitim setindeki deðerlerden farkýný toplayýp farkDizisine atýyor.
	{
		for(int j=0;j<egitimSeti;++j)// her bir doðrulama verisi için eðitim setindeki bütün verilerden farkýný farkDizisinde tutmaya çalýþýyor.
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
			farkDizisi[z][j] = toplamFark;
		}
	}
	
	
	// printf("0 0 icin fark toplami : %2.6f",farkDizisi[0][0]);cout<<endl;    	   //test amaçlý
	// printf("37 74  icin fark toplami : %2.6f",farkDizisi[37][74]);cout<<endl;  // test amaçlý


	float geciciFark[dogrulamaSeti][egitimSeti];
	// veriler en yakýn komþu hesaplarken bozuluyor. Korunmasý ve guncel veri seti listelemesinin yapýldýðýnda bozulmuþ verilerin görünmemesi için.
	copy(&farkDizisi[0][0], &farkDizisi[0][0]+dogrulamaSeti*egitimSeti,&geciciFark[0][0]); // dizi tamamen klonlanýyor.
	// çok boyutlu bir dizi kopyalanýrken copy() kullanýlabilir. memcpy() de kullanýlabilir
	// geciciFark dizisi her doðrulama verisi için en yakýn k tane komþusunun indisini tutuyor.
	
	
	float degistir=(float)veriNitelik; // degistir 5 oldu. 5 niteliðin toplamý olduðu için en fazla fark toplamý 5 olduðunda komþu bulma iþlemi bu indiste yapýlmýþ demektir.
	float kucukSayi; // her kontrolde küçük sayýyý tutup diziye yazdýracaðýz.
	int kucukVeriIndis;
	int enKucukKNN[dogrulamaSeti][k]; // en yakýn komþularýn indislerinin tutulduðu yapý. 
	
	for(int i=0;i<dogrulamaSeti;++i) // i=dogrulamaSeti
	{
		for(int z=0;z<k;++z) // k  defa kontrol yapýp k tane sütunu doldurulacak. bu for ikinci defa  çalýþtýðýnda en küçük ikinci knn komþunun indisi alýnacak
		{
			kucukSayi = geciciFark[i][0];
			kucukVeriIndis = 0;
			
			for(int j=0;j<egitimSeti;++j) // j= egitimSeti
			{
				if(geciciFark[i][j] <= kucukSayi) // <=  alýrýz çünkü = olan en yakýn komþusu da olabilir.
				{
					kucukSayi=geciciFark[i][j];//kucukSayi dan daha kucuk deger varsa kSayi ile deðiþtirilir.
					kucukVeriIndis=j;// eðitim setindeki yakýn komþunun indisi j 'de  tutulur.
				}
			}
			geciciFark[i][kucukVeriIndis]=degistir;// dizideki deðeri 5 yapýlýr. 5 yapýlýr çünkü en kucuk 2.  3.  4. vs aramalarda tekrar en kucuk diye yakalanmamasý için.
			enKucukKNN[i][z]=kucukVeriIndis; // en kucuk deðerin indisi yedeklendi.
		}
	}
	
	/*
	for( int satir=0; satir<5 ; ++satir ) // Belli satýrdaki sütunlarýn deðerlerini yazdýktan sonra alttaki satýra geçecek.
	{
		cout<<"\t";
		for(int sutun2=0 ; sutun2<k ; ++sutun2)// ayný satýrdaki bütün sütun deðerlerini yazdýracak
		{
			cout<<enKucukKNN[satir][sutun2];cout<<"  --------  ";
		}	
		cout<<endl;
	} 		// BURADA DOGRULAMA SETÝNDEKÝ VERÝLERE EÐÝTÝM SETÝNDEKÝ EN YAKIN K TANE KOMSUNUN KONUMU TUTULUYOR. TEST AMAÇLI*/

	int tahmin[dogrulamaSeti][3]; // doðrulama setinin hangi iris deðeri en fazla  tahmin yapýlýyor onu tutacak.
	
	for(int i=0;i<dogrulamaSeti;i++) // iris adetlerini tutan dizinin baþlangýçta 0 deðerleri tutmasý gerekir.
	{
		tahmin[i][0]=0;
		tahmin[i][1]=0;
		tahmin[i][2]=0;
	}	
	short irisKodu; // en yakýn komþunun veri setindeki iris kodunu geçici tutmak için.
	
	for(int i=0 ; i<dogrulamaSeti;++i)// her satýr için iris adlarýnýn kaç tane olduðunu hesaplýyor.
	{
		for(int j=0;j<k;++j) // her sütundaki iris adýný kontrol edip iris adlarýnýn sayýsýný tahmin dizisinde tutuyor.
		{
			// enKucukKNN[i][j] = en küçük verilerin konumlarýnýn tutulduklarý dizi. 
			irisKodu = veriSeti[(enKucukKNN[i][j])][4];// bu satýr en yakýn komþunun veri setindeki iris kodunu öðrenmemizi saðlýyor.  4  = iris adýnýn tutulduðu sütünlar
			if(irisKodu==0)
			{
				tahmin[i][0] = ( ( tahmin[i][0]) +1 );
			}
			else if(irisKodu==1)
			{
				tahmin[i][1] = ( ( tahmin[i][1]) +1 );
			}
			else if(irisKodu==2)
			{
				tahmin[i][2] = ( ( tahmin[i][2]) +1 );
			}
			else
			{
				cout<<"\nIris ismi bellekte düzgün olarak kodlanmamýþ ! \n";
			}
		}		
	}
	//yukarýsý aþaðýdaki gibi bir sonuç üretir
	/*
					iris tekrarlama adeti
					0 için   1için   2için
	tahmin[i][0] =  2			6		9
					8			6		1		
	.
	.
	*/
	
	
	int agirlikliTahmin[dogrulamaSeti][1];
	int enBuyuk=0 , enBuyukIndis=0;
						
	enBuyuk = tahmin[0][0];
	
	for(int i=0;i<dogrulamaSeti;++i)// en agirlikli iris adý tamininin 
	{
		enBuyuk = tahmin[i][0];
		for(int r=0;r<3;++r)
		{
			if(tahmin[i][r]>=enBuyuk)
			{
				enBuyuk=tahmin[i][r];
				enBuyukIndis=r;
			}
		}
		if(enBuyukIndis==0) // en agirlikli iris adý taminini karar olarak kaydediyor.
		{
			agirlikliTahmin[i][0]=0;
		}
		else if(enBuyukIndis==1)
		{
			agirlikliTahmin[i][0]=1;
		}
		else if(enBuyukIndis==2)
		{
			agirlikliTahmin[i][0]=2;
		}
	}/*
	Yukarýdaki for 
				Doðrulama setindeki i.indisteki veri için tahmin kararý
	agirlikliTahmin[i][0] =  1
							 2
							 0
							 0
							 1
							 2
							 0
							 .
							 .
	*/
	
	// þimdi orijinal doðrulamadaki iris adýyla tahmin iris adlarýný kýyaslayýp tahmin yüzdesini çýktý olarak verelim.
	double tahminYuzde=00.00;
	

	for(int i=egitimSeti,j=0; i<(egitimSeti+dogrulamaSeti);++i)// doðrulama setindeki satýradaki verielerle tahmin verileri karþýlaþtýrýlýyor.
	{			
		if(veriSeti[i][4]==agirlikliTahmin[j][0]) // her doðru tahmin için tahmin yüzdesi artýrýlýr.
		{
			tahminYuzde++;
		}
		j++;
	}
	
	tahminYuzde = ((100.0 / dogrulamaSeti) * tahminYuzde); // tahmin adetini yüzdelik olarak yazdýrdýk
	cout<<"\n============================================================================\n";	
	cout<<"Doðruluk oraný % "<<tahminYuzde<<endl;


	cout<<"\n\nTahmin ve gerçek deðerleri görmek için 1 e bas ";
	cout<<"\n\nKýyaslanmayý listelemeyip menüye dönmek için herhangi bir tuþa basýn : ";
	char yazdirma='0';
	yazdirma=getch();
	if(yazdirma=='1')
	{
		cout<<"Yanlýþ tahmin(ler)in yanýnda X bulunur.\n============================================================================\n";
		cout<<"\nDoðrulama setindeki verilerin gerçek ve tahmini deðerleri  \n\n"<<endl;
		for(int i=egitimSeti,j=0; i<(egitimSeti+dogrulamaSeti);++i)// doðrulama setindeki satýradaki verielerle tahmin verileri karþýlaþtýrýlýyor.
		{		
			cout<<setw(3)<<j+1<<". ("<<setw(3)<<i<<".indisteki)"<<" Doðrulama verisinin iris adý : "<<setw(17);
			
			if(veriSeti[i][4]==0)
			{
				cout<<"Iris-setosa";
			}
			else if(veriSeti[i][4]==1)
			{
				cout<<"Iris-versicolor";
			}
			else if(veriSeti[i][4]==2)
			{
				cout<<"Iris-virginica";
			}
			
			cout<<"     "<<"Tahmin edilen iris adý : "<<setw(17);
			if(agirlikliTahmin[j][0]==0)
			{
				cout<<"Iris-setosa";
			}
			else if(agirlikliTahmin[j][0]==1)
			{
				cout<<"Iris-versicolor";
			}
			else if(agirlikliTahmin[j][0]==2)
			{
				cout<<"Iris-virginica";
			}
			if(veriSeti[i][4]==agirlikliTahmin[j][0]) // her doðru tahmin için tahmin yüzdesi artýrýlýr.
			{
				cout<<endl;
			}
			else
			{
				cout<<" X "<<endl;
			}
			j++;
		}	
	}
	
	return tahminYuzde;
}
