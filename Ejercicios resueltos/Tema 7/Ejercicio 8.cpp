#include <iostream>
using namespace std;

void pedirDatos(int &altura, int &base);
double areaTriangulo(int altura, int base);

int main(){
	int altura,base;
	pedirDatos(altura,base);
	cout << "El area del triangulo es : " << areaTriangulo(altura,base) << endl;
	system("pause");
	return 0;
}

void pedirDatos(int &altura, int &base){
	cout << "Introduzca los siguientes datos del triangulo : ";
	cout << "Altura : ";
	cin >> altura;
	cout << "Base : ";
	cin >> base;
}

double areaTriangulo(int altura, int base){
	return ((base*altura)/2);
}