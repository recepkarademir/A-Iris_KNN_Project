#include <iostream>

using namespace std;

void standartizasyonfonk(float veriSeti[][5] , int veriAdet)
{
	float sepalLmindeger, sepalLmaxdeger ,sepalWmindeger , sepalWmaxdeger ,petalLmindeger,petalLmaxdeger, petalWmindeger , petalWmaxdeger;
	
	/*		GENEL B�LG�LEND�RME:

		sepalL  s�tunu = veriSeti[indis][sutun]
		sepalW  s�tunu = veriSeti[indis][sutun+1]
		petalL  s�tunu = veriSeti[indis][sutun+2]
		petalW  s�tunu = veriSeti[indis][sutun+3]
		irisAd� s�tunu = veriSeti[indis][sutun+4]
		
		temp = Ge�ici kelimesinin k�salmas�.
	*/
	
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
	
		//max ve min de�eri bulunacak.
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
	cout<< "\nen k���k sepalL : "<<sepalLmindeger<<endl;
	cout<< "\nen k���k sepalW : "<<sepalWmindeger<<endl;
	cout<< "\nen k���k petalL : "<<petalLmindeger<<endl;
	cout<< "\nen k���k petalW : "<<petalWmindeger<<endl;
	cout<<"--------------------------------------"<<endl;
	cout<< "en b�y�k sepalL : "  <<sepalLmaxdeger<<endl;
	cout<< "\nen b�y�k sepalW : "<<sepalWmaxdeger<<endl;
	cout<< "\nen b�y�k petalL : "<<petalLmaxdeger<<endl;
	cout<< "\nen b�y�k petalW : "<<petalWmaxdeger<<endl;
	for(int g=0;g<5;++g){cout<<"-----------------";}
	
	cout<<"\nStandartizasyon form�l� : normalize olacak veri = (veri - veriMin) / (veriMax - veriMin) "<<endl;
	
	for(int i=0;i<veriAdet;++i) // matris(veriSeti) diziye standartize olmu� veriler y�kleniyor.
	{
		veriSeti[i][sutun]   = ( veriSeti[i][sutun]   - sepalLmindeger ) / ( sepalLmaxdeger - sepalLmindeger  );
		veriSeti[i][sutun+1] = ( veriSeti[i][sutun+1] - sepalWmindeger ) / ( sepalWmaxdeger - sepalWmindeger  );
		veriSeti[i][sutun+2] = ( veriSeti[i][sutun+2] - petalLmindeger ) / ( petalLmaxdeger - petalLmindeger  );
		veriSeti[i][sutun+3] = ( veriSeti[i][sutun+3] - petalWmindeger ) / ( petalWmaxdeger - petalWmindeger  );
	}

	cout<<"\nVeriler 0 ile 1 aras�nda normalize edildi. Verilerin g�ncel halini listeleyebilirsiniz."<<endl;
	for(int g=0;g<5;++g){cout<<"-----------------";}
}
