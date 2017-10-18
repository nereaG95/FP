#include <iostream>
#include <fstream>
using namespace std;

const int CENTINELA=0;
bool esPerfecto(int numero);
bool esTriangular(int numero);
void perfectoYtriangular(int numero);

int main(){
	int num=1;
	const int max_numero=100000;
	while (num<=max_numero){
		perfectoYtriangular(num);
		num++;
	}
	system("pause");
	return 0;
}

bool esTriangular(int numero){
	bool esTriangular = false;
	int suma = 0, i = 1;
	while (suma < numero) {
		suma = suma + i;
		i++;
	}  
	if (suma == numero) 
		esTriangular = true;
	return esTriangular;
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

void perfectoYtriangular(int numero){
	if(esTriangular(numero) && esPerfecto(numero)){
		cout << numero << " es perfecto y triangular " << endl;
	}
}

