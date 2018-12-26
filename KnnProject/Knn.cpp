#include <iostream>
#include <iomanip> 		// formatl� setw ��kt�s� alabilmek i�in.
#include <conio.h>		// getch() i�in.
using namespace std;

float komsulukFarkHesapla(int k,int egitimSeti,int dogrulamaSeti, float veriSeti[][5],int veriNitelik)// kom�uluk farklar� hesaplanacak.
{
	//veriSeti adresi yeni bir diziye atan�yor. Art�k yeni ve orijinal dizi birbirinden etkilenir.
	system("cls");
	cout<<"K = "<<k<<"  En yak�n "<<k<<" tane kom�u incelendi ve tahminler yap�ld�.";
	
	float tmpFark=0 , toplamFark=0;
	// egitim seti verileri veri seti kar���k oldu�u i�in ilk [0..74] elemanlar� olarak kullan�lacak.
	float farkDizisi[dogrulamaSeti][egitimSeti];  // farklar bu dizide tutulacak
	// egitimSeti=75 de�erini tutuyor.   
	// egitim seti [0..74] aras�nda , do�rulamseti [75..112] aras�nda   , testSeti  [113..149]  aras�nda
	
	
	for(int z=0 , i=(egitimSeti);z<dogrulamaSeti;++z , ++i) // do�rulama veri setindeki her sat�rdaki veriler i�in de�erlerinin e�itim setindeki de�erlerden fark�n� toplay�p farkDizisine at�yor.
	{
		for(int j=0;j<egitimSeti;++j)// her bir do�rulama verisi i�in e�itim setindeki b�t�n verilerden fark�n� farkDizisinde tutmaya �al���yor.
		{
			tmpFark=0;
			toplamFark=0;
			tmpFark = ( (veriSeti[j][0]) - (veriSeti[i][0]) );
			if(tmpFark<0)
			{
				toplamFark+=(-1*tmpFark); // farklar�n negatif olmamas� gerekli. vekt�r uzakl��� negatif olmaz.
			}
			else
			{
				toplamFark+=tmpFark;
			}
			
			tmpFark = ((veriSeti[j][1])  - (veriSeti[i][1]) );
			if(tmpFark<0)
			{
				toplamFark+=(-1*tmpFark); // farklar�n negatif olmamas� gerekli. vekt�r uzakl��� negatif olmaz.
			}
			else
			{
				toplamFark+=tmpFark;
			}
			
			tmpFark = ( (veriSeti[j][2]) - (veriSeti[i][2]) );
			if(tmpFark<0)
			{
				toplamFark+=(-1*tmpFark); // farklar�n negatif olmamas� gerekli. vekt�r uzakl��� negatif olmaz.
			}
			else
			{
				toplamFark+=tmpFark;
			}
				
			tmpFark = ( (veriSeti[j][3]) - (veriSeti[i][3]) );
			if(tmpFark<0)
			{
				toplamFark+=(-1*tmpFark); // farklar�n negatif olmamas� gerekli. vekt�r uzakl��� negatif olmaz.
			}
			else
			{
				toplamFark+=tmpFark;
			}
			farkDizisi[z][j] = toplamFark;
		}
	}
	
	
	// printf("0 0 icin fark toplami : %2.6f",farkDizisi[0][0]);cout<<endl;    	   //test ama�l�
	// printf("37 74  icin fark toplami : %2.6f",farkDizisi[37][74]);cout<<endl;  // test ama�l�


	float geciciFark[dogrulamaSeti][egitimSeti];
	// veriler en yak�n kom�u hesaplarken bozuluyor. Korunmas� ve guncel veri seti listelemesinin yap�ld���nda bozulmu� verilerin g�r�nmemesi i�in.
	copy(&farkDizisi[0][0], &farkDizisi[0][0]+dogrulamaSeti*egitimSeti,&geciciFark[0][0]); // dizi tamamen klonlan�yor.
	// �ok boyutlu bir dizi kopyalan�rken copy() kullan�labilir. memcpy() de kullan�labilir
	// geciciFark dizisi her do�rulama verisi i�in en yak�n k tane kom�usunun indisini tutuyor.
	
	
	float degistir=(float)veriNitelik; // degistir 5 oldu. 5 niteli�in toplam� oldu�u i�in en fazla fark toplam� 5 oldu�unda kom�u bulma i�lemi bu indiste yap�lm�� demektir.
	float kucukSayi; // her kontrolde k���k say�y� tutup diziye yazd�raca��z.
	int kucukVeriIndis;
	int enKucukKNN[dogrulamaSeti][k]; // en yak�n kom�ular�n indislerinin tutuldu�u yap�. 
	
	for(int i=0;i<dogrulamaSeti;++i) // i=dogrulamaSeti
	{
		for(int z=0;z<k;++z) // k  defa kontrol yap�p k tane s�tunu doldurulacak. bu for ikinci defa  �al��t���nda en k���k ikinci knn kom�unun indisi al�nacak
		{
			kucukSayi = geciciFark[i][0];
			kucukVeriIndis = 0;
			
			for(int j=0;j<egitimSeti;++j) // j= egitimSeti
			{
				if(geciciFark[i][j] <= kucukSayi) // <=  al�r�z ��nk� = olan en yak�n kom�usu da olabilir.
				{
					kucukSayi=geciciFark[i][j];//kucukSayi dan daha kucuk deger varsa kSayi ile de�i�tirilir.
					kucukVeriIndis=j;// e�itim setindeki yak�n kom�unun indisi j 'de  tutulur.
				}
			}
			geciciFark[i][kucukVeriIndis]=degistir;// dizideki de�eri 5 yap�l�r. 5 yap�l�r ��nk� en kucuk 2.  3.  4. vs aramalarda tekrar en kucuk diye yakalanmamas� i�in.
			enKucukKNN[i][z]=kucukVeriIndis; // en kucuk de�erin indisi yedeklendi.
		}
	}
	
	/*
	for( int satir=0; satir<5 ; ++satir ) // Belli sat�rdaki s�tunlar�n de�erlerini yazd�ktan sonra alttaki sat�ra ge�ecek.
	{
		cout<<"\t";
		for(int sutun2=0 ; sutun2<k ; ++sutun2)// ayn� sat�rdaki b�t�n s�tun de�erlerini yazd�racak
		{
			cout<<enKucukKNN[satir][sutun2];cout<<"  --------  ";
		}	
		cout<<endl;
	} 		// BURADA DOGRULAMA SET�NDEK� VER�LERE E��T�M SET�NDEK� EN YAKIN K TANE KOMSUNUN KONUMU TUTULUYOR. TEST AMA�LI*/

	int tahmin[dogrulamaSeti][3]; // do�rulama setinin hangi iris de�eri en fazla  tahmin yap�l�yor onu tutacak.
	
	for(int i=0;i<dogrulamaSeti;i++) // iris adetlerini tutan dizinin ba�lang��ta 0 de�erleri tutmas� gerekir.
	{
		tahmin[i][0]=0;
		tahmin[i][1]=0;
		tahmin[i][2]=0;
	}	
	short irisKodu; // en yak�n kom�unun veri setindeki iris kodunu ge�ici tutmak i�in.
	
	for(int i=0 ; i<dogrulamaSeti;++i)// her sat�r i�in iris adlar�n�n ka� tane oldu�unu hesapl�yor.
	{
		for(int j=0;j<k;++j) // her s�tundaki iris ad�n� kontrol edip iris adlar�n�n say�s�n� tahmin dizisinde tutuyor.
		{
			// enKucukKNN[i][j] = en k���k verilerin konumlar�n�n tutulduklar� dizi. 
			irisKodu = veriSeti[(enKucukKNN[i][j])][4];// bu sat�r en yak�n kom�unun veri setindeki iris kodunu ��renmemizi sa�l�yor.  4  = iris ad�n�n tutuldu�u s�t�nlar
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
				cout<<"\nIris ismi bellekte d�zg�n olarak kodlanmam�� ! \n";
			}
		}		
	}
	//yukar�s� a�a��daki gibi bir sonu� �retir
	/*
					iris tekrarlama adeti
					0 i�in   1i�in   2i�in
	tahmin[i][0] =  2			6		9
					8			6		1		
	.
	.
	*/
	
	
	int agirlikliTahmin[dogrulamaSeti][1];
	int enBuyuk=0 , enBuyukIndis=0;
						
	enBuyuk = tahmin[0][0];
	
	for(int i=0;i<dogrulamaSeti;++i)// en agirlikli iris ad� tamininin 
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
		if(enBuyukIndis==0) // en agirlikli iris ad� taminini karar olarak kaydediyor.
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
	Yukar�daki for 
				Do�rulama setindeki i.indisteki veri i�in tahmin karar�
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
	
	// �imdi orijinal do�rulamadaki iris ad�yla tahmin iris adlar�n� k�yaslay�p tahmin y�zdesini ��kt� olarak verelim.
	double tahminYuzde=00.00;
	

	for(int i=egitimSeti,j=0; i<(egitimSeti+dogrulamaSeti);++i)// do�rulama setindeki sat�radaki verielerle tahmin verileri kar��la�t�r�l�yor.
	{			
		if(veriSeti[i][4]==agirlikliTahmin[j][0]) // her do�ru tahmin i�in tahmin y�zdesi art�r�l�r.
		{
			tahminYuzde++;
		}
		j++;
	}
	
	tahminYuzde = ((100.0 / dogrulamaSeti) * tahminYuzde); // tahmin adetini y�zdelik olarak yazd�rd�k
	cout<<"\n============================================================================\n";	
	cout<<"Do�ruluk oran� % "<<tahminYuzde<<endl;


	cout<<"\n\nTahmin ve ger�ek de�erleri g�rmek i�in 1 e bas ";
	cout<<"\n\nK�yaslanmay� listelemeyip men�ye d�nmek i�in herhangi bir tu�a bas�n : ";
	char yazdirma='0';
	yazdirma=getch();
	if(yazdirma=='1')
	{
		cout<<"Yanl�� tahmin(ler)in yan�nda X bulunur.\n============================================================================\n";
		cout<<"\nDo�rulama setindeki verilerin ger�ek ve tahmini de�erleri  \n\n"<<endl;
		for(int i=egitimSeti,j=0; i<(egitimSeti+dogrulamaSeti);++i)// do�rulama setindeki sat�radaki verielerle tahmin verileri kar��la�t�r�l�yor.
		{		
			cout<<setw(3)<<j+1<<". ("<<setw(3)<<i<<".indisteki)"<<" Do�rulama verisinin iris ad� : "<<setw(17);
			
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
			
			cout<<"     "<<"Tahmin edilen iris ad� : "<<setw(17);
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
			if(veriSeti[i][4]==agirlikliTahmin[j][0]) // her do�ru tahmin i�in tahmin y�zdesi art�r�l�r.
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
