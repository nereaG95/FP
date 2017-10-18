#include <iostream>
#include <cmath>
using namespace std;

int main(){
	int numero;
	const double ERROR=1e-4;
	double raiz, operacion, intento;
	cout << "Introduce un numero entero positivo : ";
	cin >> numero;
	raiz=sqrt(numero);
	cout << "La raiz es " << raiz<< endl;
	do{
		cout << " Adivina la raiz de " << numero << " : ";
		cin >> intento;
		operacion = abs(raiz-intento);
		if (operacion < ERROR){
			cout << endl << "Enhorabuena has encontrado la raiz de " << numero << " con un error menor que " << ERROR << endl;
		}
		else if (intento > raiz ){
			cout << intento << " es mayor que la raiz de " << numero << endl;
		}
		else if ( intento < raiz){
			cout << intento << " es menor que la raiz de " << numero << endl;
		}
	}while (!(operacion < ERROR));

	system("pause");
	return 0;
}