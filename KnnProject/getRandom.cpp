#include <iostream>
#include <cstdlib>		/* srand() ile veri setini rastgele kar��t�rmak i�in*/
#include <ctime>		/* time  ger�ek rastgele say�lar�n �retimini zamana ba�lama.  */
#include "getRandom.h"
//#include <algorithm>  //  k�sa sort kodlar� i�in test ama�l�.

using namespace std;

void getRandomFonk(float veriSeti[][5] , int veriAdet)
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
	
	cout<<"\n\nVerilerin yerleri 3 kez kar��t�r�ld�. G�ncel veri setini listeleyebilirsiniz.\n";
	
}
