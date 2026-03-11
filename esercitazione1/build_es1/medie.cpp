#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char *argv[])
{
	if(argc != 2)
		cerr << "Numero parametri non esatto \n";
	else
	{
		string filename = "testo.txt";
		ifstream ifs(filename);
		if ( ifs.is_open()) {
			string location;
			double temp1, temp2, temp3, temp4;
			double somma;
			double media;
		
			for(int i = 0; i < 3; i++)
			{
				ifs >> location >> temp1 >> temp2 >> temp3 >> temp4;
				somma = temp1+temp2+temp3+temp4;
				media = somma/4;
				cout << "Temperatures at " << location << ": " << temp1 << " " << temp2 << " " << temp3 << " " << temp4 << "\n";
				cout << "Average at " << location << " is " << media << endl;
				cout << endl;
			}
			
			ifs.close();
		}
		else
		{
			cerr <<"Errore nell'apertura file \n";
		}
	}
	
	return 0;
}