/*#include <iostream>
#include <fstream>
using namespace std;

int main (){
	ifstream archivo;
	bool creciente=true;
	int numero;
	int mayor=0;
	archivo.open("input.txt");
	if(archivo.is_open()){
		archivo >> numero;
		while (numero!=0 && creciente ){
			if (numero>= mayor){
				mayor=numero;
				archivo >> numero;
			}
			else{
				creciente=false;
			}
		}
		archivo.close();
	}

	if (!creciente){
		cout << "la secuencia no es creciente " << endl;
	}
	else{
		cout << "la secuencia es creciente " << endl;
	}

	system("pause");
	return 0;
}*/