/* 
	2018-10-18
	Recep KARADEMÝR 
	IRIS  :  Süsengiller (Iris), Asparagales takýmýna ait bir çiçekli bitki familyasýdýr.

	Iris familyasýndaki üç türün temel özelliklerinden oluþan veri seti yardýmýyla, 
	en iyi tür tahmini yapabilen K (KNN) deðerini bulan C++ programý.
*/
#include <iostream>
#include <iomanip> 		// formatlý setw çýktýsý alabilmek için.
#include <conio.h>		// getc() için.
#include <ctime>		/* time  gerçek rastgele sayýlarýn üretimini zamana baðlama.  */
#include <cstdlib>		/* srand() ile veri setini rastgele karýþtýrmak için*/
#include <fstream>		// txt içerisindeki verileri okuyabilmek için.
#include "windows.h"    // sleep fonk için.
//#include <algorithm>  //  kýsa sort kodlarý için test amaçlý.


using namespace std;



// Global deðiþkenler bütün fomksiyonlardan eriþilebilir.
void espri();
void veriOkuFonk();
void getRandom() ;
void standartizasyon();
void verileriYazdir();
void enYakinKomsuAlgoritmasi();
void komsulukFarkHesapla(int);
int  veriAdet =0 , veriNitelik=5 , egitimSeti , dogrulamaSeti , testSeti; // setlerin indislerini tutmak için
// veri adeti txt deki boþ olmayan satýrlarýn adetini ifade eder. 5 ise verinin özelliklerini(sepalL,.., IrisName vs)
bool espribitir=false;

float veriSeti[150][5];
	// veriSeti dizisinin 1.sütunun da sepalL    2.sütununda sepalW    3.sütununda petalL     4.sütununda petalW   5.sütununda irisName  bulunacak.
	// veriSeti dizisinin 1.satýrýnda txtdeki ilk verinin bilgileri , n.satýrda txt içindeki n.satýrdaki verinin bilgileri bulunur.
	// irisName 0 ise iris-setosa , 1 ise iris-versicolor , 2 ise iris-virginica  verilerini ifade edecek þekilde kodlanmýþtýr.



int main(int argc, char** argv) 
{
	system("color 70");  // konsolun rengi deðiþir
	bool ktespiti_izin=false; // normalizasyon yapmadan k tespiti yaptýrmayacaðým.
	bool shuffle_testi=false;
	veriOkuFonk(); // bu fonksiyonda veriler okunup matris diziye atanýp veri adeti tespit edilecek.
	
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
			verileriYazdir(); // bellekteki veri setinin anlýk olarak konsola basýlmasýný saðlar.
		}
		else if(secim=='2')
		{
			ktespiti_izin=true;
			standartizasyon(); // verilerin tahmine etkisinin ortak bir aðýrlýklandýrmada olmasýný saðlar.
		}
		else if(secim=='3')
		{
			shuffle_testi=true;
			getRandom(); // verilerin yerlerini rastgele olarak 3 defa karýþtýrýr.
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
			break; // while döngüsünden çýkar ve program bitmiþ olur.
		}
		else if(secim=='0')
		{
			system("cls"); // konsol ekranýný temizler
		}
		else
		{
			cout<<"\n\nYanlis tuslama yaptin !"<<endl;
		}
	}

	cout<<"\n\nProgram sonlandi.";
	return 0;
}

/*		GENEL BÝLGÝLENDÝRME:

		sepalL  sütunu = veriSeti[indis][sutun]
		sepalW  sütunu = veriSeti[indis][sutun+1]
		petalL  sütunu = veriSeti[indis][sutun+2]
		petalW  sütunu = veriSeti[indis][sutun+3]
		irisAdý sütunu = veriSeti[indis][sutun+4]
		
		temp = Geçici kelimesinin kýsalmasý.
*/


void standartizasyon()
{
	float sepalLmindeger, sepalLmaxdeger ,sepalWmindeger , sepalWmaxdeger ,petalLmindeger,petalLmaxdeger, petalWmindeger , petalWmaxdeger;
	
	// ilk deðer atamalarý yapýldý
	sepalLmindeger = veriSeti[0][0];   // sepalL
	sepalLmaxdeger = veriSeti[0][0];
	
	sepalWmindeger = veriSeti[0][1];	//sepalW
	sepalWmaxdeger = veriSeti[0][1];
	
	petalLmindeger = veriSeti[0][2];	//petalL
	petalLmaxdeger = veriSeti[0][2];
	
	petalWmindeger = veriSeti[0][3];	//petalW
	petalWmaxdeger = veriSeti[0][3];
	
	int sutun=0; // özniteliklere veri aktarýrken
	for(int i=0;i<veriAdet;++i) // min max bulunacak formül : standartize olacak veri = (veri - minimum veri) / (maximum veri- minimum veri)
	{
	
	//max ve min deðer hýzlýca bulunacak.
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
	// bilgi amacli verilerin alt üst limiti gösterliliyor.
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
	
	for(int i=0;i<veriAdet;++i) // matris(veriSeti) diziye standartize olmuþ veriler yükleniyor.
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
	
	FILE *oku; // okuma yapabilmek için oku pointerý oluþturuldu.
	
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
	char irisAd[16]; // iris adlarýnýn en uzun karakterli olanýn harf sayýsý
	string kontrol; // iris adlarýný 0 ,1 ,2 diye kodlamak için
	while(!feof(oku)) // ogrenci.txt içerisinde aranýyor.
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
		
		// formatlý olarak veriler okunup matris diziye aktarýlýyor.
		
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
			cout<<"Veri dosyasýndaki string veri duzgun islenemiyor !"<<endl;	
		}
		satir++; // bir alt satýrdaki veriler okunacak.
				
	}
	fclose(oku);// dosya kapatma.
	cout<<"\nVeriler basariyla okundu . \n";
	
}


void verileriYazdir()
{
		cout<<endl;
		for(int inds=0 , sutun = 0;inds<veriAdet;++inds)
		{
			cout<<setw(3)<<inds+1<<" : "; // setw formatlý yazdýrmak için.  i+1 0. yerine 1 den baþlamasý için.
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

void espri()// knn eðer 9 üzerinde bir deðer girilirse bu fonksiyon çalýþtýrýlýr.
{
/*

0=Siyah				A=Açik Yesil
1=Mavi				B=Açik Deniz Mavisi
2=Yesil				C=Açik Kirmizi
3=Deniz Mavisi 		D=Açik Mor
4=Kirmizi			E=Açik Sari
5=Mor				F=Parlak Beyaz
6=Sari				
7=Beyaz				
8=Gri				
9=Açik Mavi			

*/

	//espri yapýlýrsa bura çalýþsýn.
	
	string yan  = "\xC4\xC4"; // iki farklý sembolün ascii karþýlýðý
	string ort = "\xC5";	 // bir sembolün ascii karþýlýðý
	
	cout<< "\n Buyuk bir K degeri girdin bu islem uzun surebilir.\n";
	cout<< "\tBeklemek yerine SUDOKU cozebilirsin.\n";
	Sleep(3500); /* program biraz bekleyecek.	*/  system("cls");
	system("color 89");// Ýlk rakam arkaplani ikinci rakam ise yazi rengini belirler.
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
	for( int satir=0; satir<11 ; ++satir ) // Belli satýrdaki sütunlarýn deðerlerini yazdýktan sonra alttaki satýra geçecek.
	{
		cout<<"\t";
		for(int sutun=0 ; sutun<11 ; ++sutun)// ayný satýrdaki bütün sütun deðerlerini yazdýracak
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
	srand((unsigned)time(NULL)); // zmana baðlý rastgele sayý üretme.
	
	for(int kar=0;kar<3;++kar)
	{
		ekle=false;
		
		for(int indis=0;indis<veriAdet;++indis) // kontrol için -1 dolduruldu.
		{
			temprastgele[indis]=-1;
		}
	
		
		for(int i=0;i<veriAdet;i++)  //  0 ile 149  (dahil)  arasýnda deðer üreten döngü.
		{
			while(ekle == false)
			{
				RastGeleSayi = rand()%veriAdet; //  0 ile 149 dahil rastgele sayý üretti.
				for(int indis = 0 ; indis <veriAdet;++indis)//ayný sayýyý tekrar üretmemesi için, rastgele birbirinden farklý üretilecek sayýlarýn tutulduðu diziyi kontrol eder.
				{
					if(RastGeleSayi == temprastgele[indis]) // üretilen sayý dizide daha önce üretildiyse yeni rastgele sayýyý üretir.
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
		
		// þimdi verilerin yerleri karýþtýrýlýyor. // UYARI : YERLEÞTÝRME ÝÞLEMÝ YAPILIRKEN GEÇÝCÝ DÝZÝLER KULLANIMALI. ORÝJÝNAL DÝZÝNÝN VERÝLERÝ KARIÞMAMASI ÝÇÝN.
		// týpký iki sayýnýn yerlerini deðiþtirirken gecici bir deðiþken kullanmak gibi. 
	    
		
		/* #include <algorithm> yorum olmaktan çýkarýlýrsa ve burasý yorum olmaktan çýkarýlýrsa 3 kez 0 dan 149 a her numaradan bir tane olacak þekilde altalta yazmalý.
		sort(temprastgele, temprastgele + veriAdet);      // her bir numaradan sadece bir tane ve 150 ye kadar olmalý.
		for(int indis=0;indis<veriAdet;++indis)	
		{
			cout<<temprastgele[indis]<<endl;
		}
		*/
		
		for(int indis=0 ; indis<veriAdet ; indis++) // iris deðerlerini rastgele geçici rastgele yeni konumlarýna yerleþtirelim.
		{
			
			tempsepalL[temprastgele[indis]]  = veriSeti[indis][sutun];
				
			tempsepalW[temprastgele[indis]]  = veriSeti[indis][sutun+1];
	
		    temppetalL[temprastgele[indis]]  = veriSeti[indis][sutun+2];
		
			temppetalW[temprastgele[indis]]  = veriSeti[indis][sutun+3];
		
			tempirisName[temprastgele[indis]]=veriSeti[indis][sutun+4];
		}
		for(int indis=0;indis<veriAdet;++indis) // temp iris verilerini asýl iris verilerine yerleþtirelim.
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
	
	
	egitimSeti=veriAdet*0.50; 	// yukarý yuvarlama yapar. eðitim seti, toplam veri setinin %50 si kadar
	dogrulamaSeti=veriAdet*0.25;// doðrulama seti, toplam veri setinin ~%25 si kadar
	testSeti=veriAdet*0.25; 	// test seti, toplam veri setinin ~%25 si kadar
	
	int setduzeltme = dogrulamaSeti + egitimSeti + testSeti ; // kesirli sayýlarda doðrulama seti +1 yukarý yuvarlanýr ve setler düzeltilmiþ olur.
	if(setduzeltme!=veriAdet) // veri setinin toplam adeti orijinal veri setinin toplam veri adetiyle ayný olmalý. deðilse setler mantýklý olarak ayrýlýr.
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

	
	// setlere ayýrma iþlemi yapýlýyor.  egitimSeti , testSeti , dogrulamaSeti ,	
	if(veriAdet < 10 )
	{
		cout<<	"\n\nVeri seti cok kucuk !\n"<<endl; // düþük veri setine k deðeri için iþlem yaptýrmýyorum
		goto K_ISTE;
	}
	komsulukFarkHesapla(k); // komþuluk farklarý hesaplanacak.
	
}


void komsulukFarkHesapla(int k)// komþuluk farklarý hesaplanacak.
{
	cout<<"K = "<<k<<"  En yakin "<<k<<" tane komsu incelendi ve tahminler yapildi. \n\n"<<endl;
	float tmpFark=0 , toplamFark=0;
	// egitim seti verileri veri seti karýþýk olduðu için ilk [0..74] elemanlarý olarak kullanýlacak.
	float farkDizisi[dogrulamaSeti][egitimSeti];  // farklar bu dizide tutulacak
	// egitimSeti=75 deðerini tutuyor.   
	int sutun=0;
	// egitim seti [0..74] arasýnda , doðrulamseti [75..112] arasýnda   , testSeti  [113..149]  arasýnda
	
	
	for(int z=0 , i=(egitimSeti);z<dogrulamaSeti;++z , ++i) // doðrulama veri setindeki her satýrdaki veriler için deðerlerinin eðitim setindeki deðerlerden farkýný toplayýp farkDizisine atýyor.
	{
			for(int j=0;j<egitimSeti;++j)// her bir doðrulama verisi için eðitim setindeki bütün verilerden farkýný farkDizisinde tutmaya çalýþýyor.
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
				farkDizisi[z][j] = toplamFark;
			}
	}
	
	
	// printf("0 0 icin fark toplami : %2.6f",farkDizisi[0][0]);cout<<endl;    	   //test amaçlý
	// printf("37 74  icin fark toplami : %2.6f",farkDizisi[37][74]);cout<<endl;  // test amaçlý


	float geciciFark[dogrulamaSeti][egitimSeti];
	// veriler en yakýn komþu hesaplarken bozuluyor. Korunmasý ve guncel veri seti listelemesinin yapýldýðýnda bozulmuþ verilerin görünmemesi için.
	copy(&farkDizisi[0][0], &farkDizisi[0][0]+dogrulamaSeti*egitimSeti,&geciciFark[0][0]); // dizi tamamen klonlanýyor.
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
	}/*
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
				cout<<"\nIris ismi bellekte duzgun olarak kodlanmamis ! \n";
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
		
		
		if(veriSeti[i][4]==agirlikliTahmin[j][0]) // her doðru tahmin için tahmin yüzdesi artýrýlýr.
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
	

	tahminYuzde = ((100.0 / dogrulamaSeti) * tahminYuzde); // tahmin adetini yüzdelik olarak yazdýrdýk
	cout<<"\n============================================================================\n";	
	cout<<"Dogruluk orani % "<<tahminYuzde<<endl;
	cout<<"Yanlis tahmin(ler)in yaninda X bulunur.\n============================================================================\n";
	cout<<"\nDevam etmek icin bir tusa bas...";
	
	system("pause");
}
