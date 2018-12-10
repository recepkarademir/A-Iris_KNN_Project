#include<iostream> // cin cout cerr kütüphanesi
#include "windows.h" // sleep fonk için.
using namespace std;

void Bilgi()
{	
	system("color F0"); // Ýlk arkaplan , ikici yazý rengi.
	// Aþaðýsý formatlý hoþgeldiniz ekraný.
	cout<<"\n\n\n\n\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xBB  \xdb\xdb\xdb\xdb\xdb\xdb\xBB  \xdb\xdb\xBB \xdb\xdb\xdb\xdb\xdb\xBB"<<endl; 
	cout<<"\t\t\t\t\t\t\xC8\xCD\xCD\xCD\xCD\xdb\xdb\xBB\xdb\xdb\xC9\xCD\xdb\xdb\xdb\xdb\xBB\xdb\xdb\xdb\xBA\xdb\xdb\xC9\xCD\xCD\xdb\xdb\xBB"<<endl;
	cout<<"\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb \xC9\xBC\xdb\xdb\xBA\xdb\xdb\xC9\xdb\xdb\xBA\xC8\xdb\xdb\xBA\xC8\xdb\xdb\xdb\xdb\xdb\xC9\xBC"<<endl;
	cout<<"\t\t\t\t\t\t\xdb\xdb\xC9\xCD\xCD\xCD\xBC \xdb\xdb\xdb\xdb\xC9\xBC\xdb\xdb\xBA \xdb\xdb\xBA\xdb\xdb\xC9\xCD\xCD\xdb\xdb\xBB"<<endl;
	cout<<"\t\t\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xBB\xC8\xdb\xdb\xdb\xdb\xdb\xdb\xC9\xBC \xdb\xdb\xBA\xC8\xdb\xdb\xdb\xdb\xdb\xC9\xBC"<<endl;
	cout<<"\t\t\t\t\t\t\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xBC \xC8\xCD\xCD\xCD\xCD\xCD\xBC  \xC8\xCD\xBC \xC8\xCD\xCD\xCD\xCD\xBC "<<endl;

	cout<<"\n\t\t\t\t\t\t\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0 HAZIRLAYAN \xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\xb0\n";
											            
	cout<<"   _____   _____   _____   _____   _____      _____   _____   _____   _____    ____   _____   _____   _____   _____ \n";   
    cout<<"  ||   || ||   || ||   || ||   || ||   ||    ||   || ||   || ||   || ||   || ||   || ||   || ||   || ||   || ||   ||\n";
    cout<<"  || R || || E || || C || || E || || P ||    || K || || A || || R || || A || || D || || E || || M || || i || || R ||\n";
    cout<<"  ||___|| ||___|| ||___|| ||___|| ||___||    ||___|| ||___|| ||___|| ||___|| ||___|| ||___|| ||___|| ||___|| ||___||\n";
    cout<<"  |/___\\| |/___\\| |/___\\| |/___\\| |/___\\|    |/___\\| |/___\\| |/___\\| |/___\\| |/___\\| |/___\\| |/___\\| |/___\\| |/___\\|\n";

	cout<<"\n\n\n\n\n\n";
	                                                      
	Sleep(2200); // program biraz bekleyecek.
}

void KapanisBilgi()
{
	int p=23;
	
	HANDLE  hConsole; // hConsole adýnda bir handle oluþturuyoruz.
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    p=6;
  	SetConsoleTextAttribute(hConsole, p);
	system("cls");// Kullanýcý çýkýþ için kapat ý 5 yaparsa program buraya ve main in return 0 ýna gider.
	cout<<"\n\n\n\n\n\n\n";
	cout<<"\t\t\t\t";SetConsoleTextAttribute(hConsole, p);cout<<"  _           _             _   _           _               \n";
	p=1;SetConsoleTextAttribute(hConsole, p);p=6;
    cout<<"\t\t\t\t";SetConsoleTextAttribute(hConsole, p);cout<<" (_)         (_)           (_) (_)         | |              \n";
    p=1;SetConsoleTextAttribute(hConsole, p);p=6;
	cout<<"\t\t\t\t";SetConsoleTextAttribute(hConsole, p);cout<<"  _   _   _   _      __ _   _   _   _ __   | |   ___   _ __ \n";
	p=1;SetConsoleTextAttribute(hConsole, p);p=6;
	cout<<"\t\t\t\t";SetConsoleTextAttribute(hConsole, p);cout<<" | | | | | | | |    / _  | | | | | |  _ \\  | |  / _ \\ |  __|\n";
	p=1;SetConsoleTextAttribute(hConsole, p);p=6;
    cout<<"\t\t\t\t";SetConsoleTextAttribute(hConsole, p);cout<<" | | | |_| | | |   | (_| | | |_| | | | | | | | |  __/ | |   \n";
    p=1;SetConsoleTextAttribute(hConsole, p);p=6;
    cout<<"\t\t\t\t";SetConsoleTextAttribute(hConsole, p);cout<<" |_|  \\__  | |_|    \\__  |  \\____| |_| |_| |_|  \\___| |_|   \n";
    p=1;SetConsoleTextAttribute(hConsole, p);p=6;
    cout<<"\t\t\t\t";SetConsoleTextAttribute(hConsole, p);cout<<"       __/ |         __/ |                                  \n";
    p=1;SetConsoleTextAttribute(hConsole, p);p=6;
    cout<<"\t\t\t\t";SetConsoleTextAttribute(hConsole, p);cout<<"      |___/         |___/                                   \n";
    p=7;SetConsoleTextAttribute(hConsole, p);
    cout<<"\n\n\n\n\n\n\n";                                                       
}
