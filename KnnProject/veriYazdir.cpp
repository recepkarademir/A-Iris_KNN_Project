#include <iostream>
#include <iomanip> 		// formatlý setw çýktýsý alabilmek için.
#include "veriYazdir.h"

using namespace std;

void verileriYazdir(float veriSeti[][5] , int veriAdet , int inds)
{
	
	cout<<endl;
	if(inds!=0)
	{
		cout<<"Test seti verileri\n\n";
	}
	for(int sutun = 0;inds<veriAdet;++inds)
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
			cout<<"Sistemdeki kayýtlý verilerde hata var.!"<<endl;	
		}
	}
}
