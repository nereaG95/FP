#include <iostream>
using namespace std;

int lecturaConLimites(int a, int b);
void pedirNumero(int &numero);

int main(){
	int a =10;
	int b=20;
	cout << "El numero entre " << a << " y " << b << " es " <<lecturaConLimites(a,b) << endl;
	system("pause");
	return 0;
}

void pedirNumero(int &numero, int a, int b){
	cout << "Introduce un numero : ";
	cin >> numero;
	if (numero > b){
		cout << "Demasiado alto ... " << endl;
	}
	else if (numero < a ){
		cout << "Demasiado bajo ... " << endl;
	}
}

int lecturaConLimites(int a, int b){
	int numero;
	do{
		pedirNumero(numero,a,b);
	}while (numero<a || numero >b);
	return numero;
}