#include <iostream>
using namespace std;


int inverso(int numero);
bool capicua(int numero);

int main(){
	int numero;
	do{
		cout << "Introduce un numero positivo para ver si es capicua (< 0 para terminar): ";
		cin >> numero;
		cout << numero;
		if (!capicua(numero)){
			cout << " no ";
		}
		cout << " es capicua " << endl;
	}while (numero >= 0);
	system("pause");
	return 0;
}

bool capicua(int numero){
	bool esCapicua=false;
	if (numero==(inverso(numero))){
		esCapicua=true;
	}
	return esCapicua;
}

int inverso(int numero){
	int inverso=0,digito;
	while (numero > 0){
		digito=numero%10;
		inverso=(inverso*10)+digito;
		numero=numero/10;
	}
	return inverso;
}