#include <iostream>
#include <cstdlib>		/* srand() ile veri setini rastgele karýþtýrmak için*/
#include <ctime>		/* time  gerçek rastgele sayýlarýn üretimini zamana baðlama.  */
#include "getRandom.h"
//#include <algorithm>  //  kýsa sort kodlarý için test amaçlý.

using namespace std;

void getRandomFonk(float veriSeti[][5] , int veriAdet)
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
	
	cout<<"\n\nVerilerin yerleri 3 kez karýþtýrýldý. Güncel veri setini listeleyebilirsiniz.\n";
	
}
