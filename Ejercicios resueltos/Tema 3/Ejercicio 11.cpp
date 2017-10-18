#include <iostream>
using namespace std;

int main(){
	double numero, resultado;
	char letra;
	const double PULGADAS= 0.39370;
	const double MILLAS = 0.00062137;
	const double FAREN1 =32 ;
	const double FAREN2 = 1.8000;
	const double GALONES= 3.78541178;
	const double ONZAS = 0.035274;
	const double LIBRAS =2.2046 ;

	cout << " Unidades admitidad  : pulgadas(p) , millas(m), grados Farenheit (F), galones(g), onzas(o) y libras (l). " << endl;
	cout << " Introduce una medida (cantidad y seguido una letra ): ";
	cin >> numero ;
	cin >> letra;
	letra=toupper(letra);
	if (letra=='P'){
		resultado = numero / PULGADAS ;
		cout << "Equivalente a : " << resultado << " cm " << endl;
	}
	else if (letra=='M'){
		resultado = numero/MILLAS;
		cout << "Equivalente a : " << resultado << " m" <<  endl;
	}
	else if (letra=='F'){
		resultado = (numero - FAREN1)/FAREN2;
		cout << "Equivalente a : " << resultado << " c " << endl;
	}
	else if (letra=='G'){
		resultado =  numero * GALONES;
		cout << "Equivalente a : " << resultado << " l "<< endl;
	}
	else if (letra=='O'){
		resultado = numero/ONZAS;
		cout << "Equivalente a : " << resultado << " gr " <<  endl;
	}
	else if (letra =='L'){
		resultado = numero / LIBRAS;
		cout << "Equivalente a : " << resultado << " kg "<< endl;
	}
	else {
		cout << "Esta conversion es incorrecta " << endl;
	}
	system("pause");
	return 0;
}