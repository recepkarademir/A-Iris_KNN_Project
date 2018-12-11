#include <fstream>		// txt içerisindeki verileri okuyabilmek için.
#include <iostream>

using namespace std;

int veriOkuFonk(float veriSeti[][5])
{
	int veriAdet=0;
	
	FILE *oku; // okuma yapabilmek için oku pointerý oluþturuldu.
	
	if( (oku=fopen("iris.txt","r"))==NULL )
	{
		system("cls");
		cout<<" Dosya okuma basarisiz.";
		exit(0);
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
			cout<<"Veri dosyasindaki string veri duzgun islenemiyor !"<<endl;
			exit(0);	
		}
		satir++; // bir alt satýrdaki veriler okunacak.
				
	}
	fclose(oku);// dosya kapatma.
	cout<<"Veriler okundu . \n";
	return veriAdet;
}
