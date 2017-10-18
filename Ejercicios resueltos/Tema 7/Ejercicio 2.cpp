#include <iostream>
#include <fstream>
using namespace std;

const int CENTINELA=0;
bool esPerfecto(int numero);

int main(){
	ifstream archivo;
	int numero, numerosPerfectos=0;
	archivo.open("datos.txt");
	if(archivo.is_open()){
		archivo >> numero;
		while (numero !=CENTINELA){
			if(esPerfecto(numero)){
				numerosPerfectos++;
			}
			archivo >> numero;
		}
		archivo.close();
	}
	cout << "El archivo contiene " << numerosPerfectos << " numero(s) perfecto(s) " << endl;
	system("pause");
	return 0;
}


bool esPerfecto(int numero){
	bool perfecto=false;
	int suma=0,i=1;
	while (i < numero){
		if (numero%i==0){
			suma= suma+(i);
		}
		i++;
	}
	if (suma==numero){
		perfecto=true;
	}
	return perfecto;
}

