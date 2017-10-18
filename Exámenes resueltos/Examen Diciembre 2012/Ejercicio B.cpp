/*#include <iostream>
#include <fstream>
using namespace std;

int rango(int menor, int mayor);

int main (){
	ifstream arch;
	int menor;
	int mayor=0;
	int numero;
	arch.open("input.txt");
	if (arch.is_open()){
		arch >>numero;
		menor=numero;
		while (numero!=0){
			if (numero < menor){
				menor=numero;
			}
			else if (numero >=mayor){
				mayor=numero;
			}
			arch >> numero;
		}
		cout << mayor << menor;
		arch.close();
	}
	cout << "El rango es : " << rango(menor, mayor) << endl;
	system("pause");
	return 0;
}

int rango(int menor, int mayor){
	int rango;
	rango=mayor-menor;
	return rango;
}*/