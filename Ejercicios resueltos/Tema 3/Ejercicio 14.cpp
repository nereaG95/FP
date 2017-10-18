#include <iostream>
using namespace std;

int cuadrados (int numero);

int main(){
	int numero;
	cout << "Introduzca el numero del que quiere calcular su cuadrado : ";
	cin >> numero;
	cout << "El cuadrado del entero es " << cuadrados(numero) << endl;
	system("pause");
	return 0;
}

int cuadrados (int numero){
	int cuadrado=0;
	int impar=1; 

	for ( int cont=0; cont < numero; cont++){
		cuadrado=cuadrado+impar;
		impar=impar+2; 
	}

	return cuadrado;
}