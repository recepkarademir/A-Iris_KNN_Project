/* 
	2018-10-18
	Recep KARADEM�R 
	IRIS  :  S�sengiller (Iris), Asparagales tak�m�na ait bir �i�ekli bitki familyas�d�r.

	Iris familyas�ndaki �� t�r�n temel �zelliklerinden olu�an veri seti yard�m�yla, 
	en iyi t�r tahmini yapabilen K (KNN) de�erini bulan C++ program�.
*/
#include <iostream>
#include <iomanip> 		// formatl� setw ��kt�s� alabilmek i�in.
#include <conio.h>		// getc() i�in.
#include <ctime>		/* time  ger�ek rastgele say�lar�n �retimini zamana ba�lama.  */
#include <cstdlib>		/* srand() ile veri setini rastgele kar��t�rmak i�in*/
#include <fstream>		// txt i�erisindeki verileri okuyabilmek i�in.
#include "windows.h"    // sleep fonk i�in.
//#include <algorithm>  //  k�sa sort kodlar� i�in test ama�l�.


using namespace std;



// Global de�i�kenler b�t�n fomksiyonlardan eri�ilebilir.
void espri();
void veriOkuFonk();
void getRandom() ;
void standartizasyon();
void verileriYazdir();
void enYakinKomsuAlgoritmasi();
void komsulukFarkHesapla(int);
int  veriAdet =0 , veriNitelik=5 , egitimSeti , dogrulamaSeti , testSeti; // setlerin indislerini tutmak i�in
// veri adeti txt deki bo� olmayan sat�rlar�n adetini ifade eder. 5 ise verinin �zelliklerini(sepalL,.., IrisName vs)
bool espribitir=false;

float veriSeti[150][5];
	// veriSeti dizisinin 1.s�tunun da sepalL    2.s�tununda sepalW    3.s�tununda petalL     4.s�tununda petalW   5.s�tununda irisName  bulunacak.
	// veriSeti dizisinin 1.sat�r�nda txtdeki ilk verinin bilgileri , n.sat�rda txt i�indeki n.sat�rdaki verinin bilgileri bulunur.
	// irisName 0 ise iris-setosa , 1 ise iris-versicolor , 2 ise iris-virginica  verilerini ifade edecek �ekilde kodlanm��t�r.



int main(int argc, char** argv) 
{
	system("color 70");  // konsolun rengi de�i�ir
	bool ktespiti_izin=false; // normalizasyon yapmadan k tespiti yapt�rmayaca��m.
	bool shuffle_testi=false;
	veriOkuFonk(); // bu fonksiyonda veriler okunup matris diziye atan�p veri adeti tespit edilecek.
	
	cout<<"\nIris adlari bellekte 0 ,1 ,2 olacak sekilde kodlanarak tutuluyor.\n";
	cout<<"Fakat listeleme yapilirken iris adinin kodu";
	cout<<"\n0 ise iris-setosa , 1 ise iris-versicolor , 2 ise iris-virginica olarak listelenecektir."<<endl;
	cout<<"\nBuradaki secimlerde tavsiye edilen islem sirasi soyledir : 1 , 2 , 3 , 4 , 5 \n"<<endl;
	char secim=5;
	
	while(true)
	{
		cout<<"\n\n\nVerilerin guncel halini listelemek icin.................. 1 e bas "<<endl;
		cout<<"Verilerin normalize edilmesi icin........................ 2 ye bas"<<endl;
		cout<<"Verilerin yerlerini karistirmak(3 defa karistirilir) icin 3 e bas"<<endl;
		cout<<"K-Nearest Neighbor (en yakin komsu) algoritmasi icin..... 4 e bas"<<endl;
		cout<<"Konsol ekranini temizlemek icin ......................... 0 a bas"<<endl;
		cout<<"Programi bitirmek icin .................................. 5 e bas"<<endl;
		
		secim=getch();
		
		if(secim=='1')
		{
			verileriYazdir(); // bellekteki veri setinin anl�k olarak konsola bas�lmas�n� sa�lar.
		}
		else if(secim=='2')
		{
			ktespiti_izin=true;
			standartizasyon(); // verilerin tahmine etkisinin ortak bir a��rl�kland�rmada olmas�n� sa�lar.
		}
		else if(secim=='3')
		{
			shuffle_testi=true;
			getRandom(); // verilerin yerlerini rastgele olarak 3 defa kar��t�r�r.
		}
		else if(secim=='4' && ktespiti_izin==true)
		{
			if(shuffle_testi==false)
			{
				cout<<"\n\n\n\n\n\n\nONCE VERILERIN "<<"KARISTIRILMASI TAVSIYE EDILIR ! \n";
			}
			enYakinKomsuAlgoritmasi();
		}
		else if(secim=='4' && ktespiti_izin==false)
		{
			cout<<"\n\n\n\n\n\n\nONCE NORMALIZASYON YAPMALISIN ! \n";
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
			cout<<"\n\nYanlis tuslama yaptin !"<<endl;
		}
	}

	cout<<"\n\nProgram sonlandi.";
	return 0;
}

/*		GENEL B�LG�LEND�RME:

		sepalL  s�tunu = veriSeti[indis][sutun]
		sepalW  s�tunu = veriSeti[indis][sutun+1]
		petalL  s�tunu = veriSeti[indis][sutun+2]
		petalW  s�tunu = veriSeti[indis][sutun+3]
		irisAd� s�tunu = veriSeti[indis][sutun+4]
		
		temp = Ge�ici kelimesinin k�salmas�.
*/


void standartizasyon()
{
	float sepalLmindeger, sepalLmaxdeger ,sepalWmindeger , sepalWmaxdeger ,petalLmindeger,petalLmaxdeger, petalWmindeger , petalWmaxdeger;
	
	// ilk de�er atamalar� yap�ld�
	sepalLmindeger = veriSeti[0][0];   // sepalL
	sepalLmaxdeger = veriSeti[0][0];
	
	sepalWmindeger = veriSeti[0][1];	//sepalW
	sepalWmaxdeger = veriSeti[0][1];
	
	petalLmindeger = veriSeti[0][2];	//petalL
	petalLmaxdeger = veriSeti[0][2];
	
	petalWmindeger = veriSeti[0][3];	//petalW
	petalWmaxdeger = veriSeti[0][3];
	
	int sutun=0; // �zniteliklere veri aktar�rken
	for(int i=0;i<veriAdet;++i) // min max bulunacak form�l : standartize olacak veri = (veri - minimum veri) / (maximum veri- minimum veri)
	{
	
	//max ve min de�er h�zl�ca bulunacak.
		if(veriSeti[i][sutun] < sepalLmindeger  )
		{
			sepalLmindeger = veriSeti[i][sutun];
		}
		else if(veriSeti[i][sutun] > sepalLmaxdeger)
		{
			sepalLmaxdeger = veriSeti[i][sutun];
		}
		
		if(veriSeti[i][sutun+1] < sepalWmindeger  )
		{
			sepalWmindeger = veriSeti[i][sutun+1];
		}
		else if(veriSeti[i][sutun+1] > sepalWmaxdeger)
		{
			sepalWmaxdeger = veriSeti[i][sutun+1];
		}
		
		
		if(veriSeti[i][sutun+2] < petalLmindeger  )
		{
			petalLmindeger = veriSeti[i][sutun+2];
		}
		else if(veriSeti[i][sutun+2] > petalLmaxdeger)
		{
			petalLmaxdeger = veriSeti[i][sutun+2];
		}
		

		if(veriSeti[i][sutun+3] < petalWmindeger  )
		{
			petalWmindeger = veriSeti[i][sutun+3];
		}
		else if(veriSeti[i][sutun+3] > petalWmaxdeger)
		{
			petalWmaxdeger = veriSeti[i][sutun+3];
		}
		
	}
	
	for(int g=0;g<5;++g){cout<<"-----------------";}
	// bilgi amacli verilerin alt �st limiti g�sterliliyor.
	cout<< "\nen kucuk sepalL : "<<sepalLmindeger<<endl;
	cout<< "\nen kucuk sepalW : "<<sepalWmindeger<<endl;
	cout<< "\nen kucuk petalL : "<<petalLmindeger<<endl;
	cout<< "\nen kucuk petalW : "<<petalWmindeger<<endl;
	cout<<"--------------------------------------"<<endl;
	cout<< "en buyuk sepalL : "<<sepalLmaxdeger<<endl;
	cout<< "\nen buyuk sepalW : "<<sepalWmaxdeger<<endl;
	cout<< "\nen buyuk petalL : "<<petalLmaxdeger<<endl;
	cout<< "\nen buyuk petalW : "<<petalWmaxdeger<<endl;
	for(int g=0;g<5;++g){cout<<"-----------------";}
	
	cout<<"\nStandartizasyon formulu : normalize olacak veri = (veri - veriMin) / (veriMax - veriMin) "<<endl;
	
	for(int i=0;i<veriAdet;++i) // matris(veriSeti) diziye standartize olmu� veriler y�kleniyor.
	{
		veriSeti[i][sutun]   = ( veriSeti[i][sutun]   - sepalLmindeger ) / ( sepalLmaxdeger - sepalLmindeger  );
		veriSeti[i][sutun+1] = ( veriSeti[i][sutun+1] - sepalWmindeger ) / ( sepalWmaxdeger - sepalWmindeger  );
		veriSeti[i][sutun+2] = ( veriSeti[i][sutun+2] - petalLmindeger ) / ( petalLmaxdeger - petalLmindeger  );
		veriSeti[i][sutun+3] = ( veriSeti[i][sutun+3] - petalWmindeger ) / ( petalWmaxdeger - petalWmindeger  );
	}

	cout<<"\nVeriler 0 ile 1 arasinda normalize edildi. Verilerin guncel halini listeleyebilirsiniz."<<endl;
	for(int g=0;g<5;++g){cout<<"-----------------";}
}


void veriOkuFonk()
{
	veriAdet=0;
	
	FILE *oku; // okuma yapabilmek i�in oku pointer� olu�turuldu.
	
	if( (oku=fopen("iris.txt","r"))==NULL )
	{
		cout<<" Dosya okuma basarisiz.";
		abort();
	}

	string line;
	ifstream satiroku("iris.txt");
	
	while(!satiroku.eof())
	{
		getline(satiroku,line);
		if(line!="\0")
		{
			veriAdet++;
		}		
	}
	satiroku.close();

	int satir = 0 , sutun = 0;
	char irisAd[16]; // iris adlar�n�n en uzun karakterli olan�n harf say�s�
	string kontrol; // iris adlar�n� 0 ,1 ,2 diye kodlamak i�in
	while(!feof(oku)) // ogrenci.txt i�erisinde aran�yor.
	{
			
		sutun = 0;
		
		/*veriSeti[150][5] ={indis           veriler
							0.{seplaL,sepalW,petalL,petalW,irisName},
							1.{seplaL,sepalW,petalL,petalW,irisName},
							2.{seplaL,sepalW,petalL,petalW,irisName},
							3.{seplaL,sepalW,petalL,petalW,irisName},
							4.{seplaL,sepalW,petalL,petalW,irisName},
							5.{seplaL,sepalW,petalL,petalW,irisName},
							.
							.
							.
							.
							149.{seplaL,sepalW,petalL,petalW,irisName} };
							
							irisName = 0-1 veya 2 olacak.
		*/
		
		// formatl� olarak veriler okunup matris diziye aktar�l�yor.
		
		fscanf(oku,"%f,%f,%f,%f,%s",&veriSeti[satir][sutun],&veriSeti[satir][sutun+1],&veriSeti[satir][sutun+2],&veriSeti[satir][sutun+3],&irisAd); 
		kontrol = irisAd;
		
		
		if(kontrol=="Iris-setosa")
		{
			veriSeti[satir][sutun+4] = 0.0;
		}
		else if(kontrol=="Iris-versicolor")
		{
			veriSeti[satir][sutun+4] = 1.0;
		}
		else if(kontrol=="Iris-virginica")
		{
			veriSeti[satir][sutun+4] = 2.0;
		}
		else
		{
			cout<<"Veri dosyas�ndaki string veri duzgun islenemiyor !"<<endl;	
		}
		satir++; // bir alt sat�rdaki veriler okunacak.
				
	}
	fclose(oku);// dosya kapatma.
	cout<<"\nVeriler basariyla okundu . \n";
	
}


void verileriYazdir()
{
		cout<<endl;
		for(int inds=0 , sutun = 0;inds<veriAdet;++inds)
		{
			cout<<setw(3)<<inds+1<<" : "; // setw formatl� yazd�rmak i�in.  i+1 0. yerine 1 den ba�lamas� i�in.
			printf("%2.4f  %2.4f  %2.4f  %2.4f ", veriSeti[inds][sutun],veriSeti[inds][sutun+1],veriSeti[inds][sutun+2],veriSeti[inds][sutun+3]);
			if(veriSeti[inds][sutun+4]==0)
			{
				cout<<"Iris-setosa"<<endl;
			}
			else if(veriSeti[inds][sutun+4]==1)
			{
				cout<<"Iris-versicolor"<<endl;
			}
			else if(veriSeti[inds][sutun+4]==2)
			{
				cout<<"Iris-virginica"<<endl;
			}
			else
			{
				cout<<"Sistemdeki kayitli verilerde hata var.!"<<endl;	
			}
		}
}

void espri()// knn e�er 9 �zerinde bir de�er girilirse bu fonksiyon �al��t�r�l�r.
{
/*

0=Siyah				A=A�ik Yesil
1=Mavi				B=A�ik Deniz Mavisi
2=Yesil				C=A�ik Kirmizi
3=Deniz Mavisi 		D=A�ik Mor
4=Kirmizi			E=A�ik Sari
5=Mor				F=Parlak Beyaz
6=Sari				
7=Beyaz				
8=Gri				
9=A�ik Mavi			

*/

	//espri yap�l�rsa bura �al��s�n.
	
	string yan  = "\xC4\xC4"; // iki farkl� sembol�n ascii kar��l���
	string ort = "\xC5";	 // bir sembol�n ascii kar��l���
	
	cout<< "\n Buyuk bir K degeri girdin bu islem uzun surebilir.\n";
	cout<< "\tBeklemek yerine SUDOKU cozebilirsin.\n";
	Sleep(3500); /* program biraz bekleyecek.	*/  system("cls");
	system("color 89");// �lk rakam arkaplani ikinci rakam ise yazi rengini belirler.
	short satir  =11 , sutun  =11;
	string dizi[11][11]={	{"5 ","3 ","  ","|","   ","7 ","  ","|","   ","  "," "},
							{"6 ","  ","  ","|"," 1 ","9 ","5 ","|","   ","  "," "},
							{"  ","9 ","8 ","|","   ","  ","  ","|","   ","6 "," "},
							{yan,yan,yan,ort,yan,yan,"\xC4\xC4\xC4",ort,yan,yan,yan},
							{"8 ","  ","  ","|","   ","6 ","  ","|","   ","  ","3"},
							{"4 ","  ","  ","|"," 8 ","  ","3 ","|","   ","  ","1"},
							{"7 ","  ","  ","|","   ","2 ","  ","|","   ","  ","6"},
							{yan,yan,yan,ort,yan,yan,"\xC4\xC4\xC4",ort,yan,yan,yan},
							{"  ","6 ","  ","|","   ","  ","  ","|"," 2 ","8 "," "},
							{"  ","  ","  ","|"," 4 ","1 ","9 ","|","   ","  ","5"},
							{"  ","  ","  ","|","   ","8 ","  ","|","   ","7 ","9"},	};
		
	cout<<"\n\n";	
	for( int satir=0; satir<11 ; ++satir ) // Belli sat�rdaki s�tunlar�n de�erlerini yazd�ktan sonra alttaki sat�ra ge�ecek.
	{
		cout<<"\t";
		for(int sutun=0 ; sutun<11 ; ++sutun)// ayn� sat�rdaki b�t�n s�tun de�erlerini yazd�racak
		{
			cout<<dizi[satir][sutun];
		}	
		cout<<endl;
	}	
	
	Sleep(2200); // program biraz bekleyecek.
	system("cls");
	system("color 70");
}

void getRandom() 
{
	int sutun=0;
	int RastGeleSayi;
	short temprastgele[veriAdet];
	float tempsepalL[veriAdet] , tempsepalW[veriAdet] , temppetalL[veriAdet] , temppetalW[veriAdet] , tempirisName[veriAdet];
	bool ekle=false;
	srand((unsigned)time(NULL)); // zmana ba�l� rastgele say� �retme.
	
	for(int kar=0;kar<3;++kar)
	{
		ekle=false;
		
		for(int indis=0;indis<veriAdet;++indis) // kontrol i�in -1 dolduruldu.
		{
			temprastgele[indis]=-1;
		}
	
		
		for(int i=0;i<veriAdet;i++)  //  0 ile 149  (dahil)  aras�nda de�er �reten d�ng�.
		{
			while(ekle == false)
			{
				RastGeleSayi = rand()%veriAdet; //  0 ile 149 dahil rastgele say� �retti.
				for(int indis = 0 ; indis <veriAdet;++indis)//ayn� say�y� tekrar �retmemesi i�in, rastgele birbirinden farkl� �retilecek say�lar�n tutuldu�u diziyi kontrol eder.
				{
					if(RastGeleSayi == temprastgele[indis]) // �retilen say� dizide daha �nce �retildiyse yeni rastgele say�y� �retir.
					{
						ekle=false;
						break;
					}
					else
					{
						ekle= true;
						continue;
					}
					
				}
			}
			temprastgele[i]=RastGeleSayi;
			ekle=false;
		}
		
		// �imdi verilerin yerleri kar��t�r�l�yor. // UYARI : YERLE�T�RME ��LEM� YAPILIRKEN GE��C� D�Z�LER KULLANIMALI. OR�J�NAL D�Z�N�N VER�LER� KARI�MAMASI ���N.
		// t�pk� iki say�n�n yerlerini de�i�tirirken gecici bir de�i�ken kullanmak gibi. 
	    
		
		/* #include <algorithm> yorum olmaktan ��kar�l�rsa ve buras� yorum olmaktan ��kar�l�rsa 3 kez 0 dan 149 a her numaradan bir tane olacak �ekilde altalta yazmal�.
		sort(temprastgele, temprastgele + veriAdet);      // her bir numaradan sadece bir tane ve 150 ye kadar olmal�.
		for(int indis=0;indis<veriAdet;++indis)	
		{
			cout<<temprastgele[indis]<<endl;
		}
		*/
		
		for(int indis=0 ; indis<veriAdet ; indis++) // iris de�erlerini rastgele ge�ici rastgele yeni konumlar�na yerle�tirelim.
		{
			
			tempsepalL[temprastgele[indis]]  = veriSeti[indis][sutun];
				
			tempsepalW[temprastgele[indis]]  = veriSeti[indis][sutun+1];
	
		    temppetalL[temprastgele[indis]]  = veriSeti[indis][sutun+2];
		
			temppetalW[temprastgele[indis]]  = veriSeti[indis][sutun+3];
		
			tempirisName[temprastgele[indis]]=veriSeti[indis][sutun+4];
		}
		for(int indis=0;indis<veriAdet;++indis) // temp iris verilerini as�l iris verilerine yerle�tirelim.
		{	
			veriSeti[indis][sutun]  =tempsepalL[indis];
			veriSeti[indis][sutun+1]=tempsepalW[indis];
			veriSeti[indis][sutun+2]=temppetalL[indis];
			veriSeti[indis][sutun+3]=temppetalW[indis];
			veriSeti[indis][sutun+4]=tempirisName[indis];
		}
	}
	
	cout<<"\n\nVerilerin yerleri 3 kez karistirildi. Guncel veri setini listeleyebilirsiniz.\n";
	
}

void enYakinKomsuAlgoritmasi()
{
	short k;     bool ESPRI=false;
	
	
	egitimSeti=veriAdet*0.50; 	// yukar� yuvarlama yapar. e�itim seti, toplam veri setinin %50 si kadar
	dogrulamaSeti=veriAdet*0.25;// do�rulama seti, toplam veri setinin ~%25 si kadar
	testSeti=veriAdet*0.25; 	// test seti, toplam veri setinin ~%25 si kadar
	
	int setduzeltme = dogrulamaSeti + egitimSeti + testSeti ; // kesirli say�larda do�rulama seti +1 yukar� yuvarlan�r ve setler d�zeltilmi� olur.
	if(setduzeltme!=veriAdet) // veri setinin toplam adeti orijinal veri setinin toplam veri adetiyle ayn� olmal�. de�ilse setler mant�kl� olarak ayr�l�r.
	{
		setduzeltme = veriAdet - setduzeltme;
		dogrulamaSeti += setduzeltme;
		setduzeltme = dogrulamaSeti + egitimSeti + testSeti ;
		cout<<"\n\n\n";
		for(int g=0;g<5;++g){cout<<"-----------------";}
		cout<<"\nVeri Adedi "<<veriAdet<<" asagidaki gibi setlere ayrildi : \nEgitim seti veri adeti    : "<<egitimSeti<<endl;
		cout<<"Dogrulama seti veri adeti : "<<dogrulamaSeti<<endl;
		cout<<"Test seti veri adeti      : "<<testSeti<<endl;
		if(setduzeltme==veriAdet)
		{
			cout<<"\nSetlerin oranli ayrilmasi icin duzeltme yapildi.\n"<<endl;
		}
	}
	else
	{
		cout<<"\n\nEgitim seti veri adeti    : "<<egitimSeti<<endl;
		cout<<"Dogrulama seti veri adeti : "<<dogrulamaSeti<<endl;
		cout<<"Test seti veri adeti      : "<<testSeti<<endl;
	}
	
	for(int g=0;g<5;++g){cout<<"-----------------";} cout<<endl;
	K_ISTE:cout<<"\n\nKac yakin komsu icin tahmin yurutulmesini istiyorsun (1-3-5-7-9..-21 vs. girilmesi tavsiye edilir) ";
	cout<<"\nDegeri girip entera bas : \n\n\n";
	cin>>k;
	
	if(k<=0 || k>egitimSeti)
	{
		cout<<"\nBu degeri k olarak atayamazsin ! \n";
		goto K_ISTE; 
	}
	system("cls");
	
	if(k>21 && espribitir==false)
	{
		espri();
		ESPRI=true;
		if(ESPRI==true && espribitir==false)
		{
			cout<<"\n\n    SAKA SAKA	 Islem coktan tamamlandi bile.\n\n";
		}
		espribitir=true;
	}

	
	// setlere ay�rma i�lemi yap�l�yor.  egitimSeti , testSeti , dogrulamaSeti ,	
	if(veriAdet < 10 )
	{
		cout<<	"\n\nVeri seti cok kucuk !\n"<<endl; // d���k veri setine k de�eri i�in i�lem yapt�rm�yorum
		goto K_ISTE;
	}
	komsulukFarkHesapla(k); // kom�uluk farklar� hesaplanacak.
	
}


void komsulukFarkHesapla(int k)// kom�uluk farklar� hesaplanacak.
{
	cout<<"K = "<<k<<"  En yakin "<<k<<" tane komsu incelendi ve tahminler yapildi. \n\n"<<endl;
	float tmpFark=0 , toplamFark=0;
	// egitim seti verileri veri seti kar���k oldu�u i�in ilk [0..74] elemanlar� olarak kullan�lacak.
	float farkDizisi[dogrulamaSeti][egitimSeti];  // farklar bu dizide tutulacak
	// egitimSeti=75 de�erini tutuyor.   
	int sutun=0;
	// egitim seti [0..74] aras�nda , do�rulamseti [75..112] aras�nda   , testSeti  [113..149]  aras�nda
	
	
	for(int z=0 , i=(egitimSeti);z<dogrulamaSeti;++z , ++i) // do�rulama veri setindeki her sat�rdaki veriler i�in de�erlerinin e�itim setindeki de�erlerden fark�n� toplay�p farkDizisine at�yor.
	{
			for(int j=0;j<egitimSeti;++j)// her bir do�rulama verisi i�in e�itim setindeki b�t�n verilerden fark�n� farkDizisinde tutmaya �al���yor.
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
				farkDizisi[z][j] = toplamFark;
			}
	}
	
	
	// printf("0 0 icin fark toplami : %2.6f",farkDizisi[0][0]);cout<<endl;    	   //test ama�l�
	// printf("37 74  icin fark toplami : %2.6f",farkDizisi[37][74]);cout<<endl;  // test ama�l�


	float geciciFark[dogrulamaSeti][egitimSeti];
	// veriler en yak�n kom�u hesaplarken bozuluyor. Korunmas� ve guncel veri seti listelemesinin yap�ld���nda bozulmu� verilerin g�r�nmemesi i�in.
	copy(&farkDizisi[0][0], &farkDizisi[0][0]+dogrulamaSeti*egitimSeti,&geciciFark[0][0]); // dizi tamamen klonlan�yor.
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
	}/*
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
				cout<<"\nIris ismi bellekte duzgun olarak kodlanmamis ! \n";
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
		cout<<setw(3)<<j+1<<". ("<<setw(3)<<i<<".indisteki)"<<" Dogrulama verisinin iris adi : "<<setw(17);
		
		
		
		
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
		
		cout<<"     "<<"Tahmin edilen iris adi : "<<setw(17);
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
			tahminYuzde++;
			cout<<endl;
		}
		else
		{
			cout<<" X "<<endl;
		}
		j++;
	}
	

	tahminYuzde = ((100.0 / dogrulamaSeti) * tahminYuzde); // tahmin adetini y�zdelik olarak yazd�rd�k
	cout<<"\n============================================================================\n";	
	cout<<"Dogruluk orani % "<<tahminYuzde<<endl;
	cout<<"Yanlis tahmin(ler)in yaninda X bulunur.\n============================================================================\n";
	cout<<"\nDevam etmek icin bir tusa bas...";
	
	system("pause");
}
