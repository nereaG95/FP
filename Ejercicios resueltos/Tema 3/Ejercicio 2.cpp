#include <iostream>
#include <cmath>
using namespace std;

double anguloRadianes (int angulo);
double areaTriangulo(double lado1, double lado2, double radianes);


int main(){
	double lado1,lado2,anguloRad;
	int angulo;

	cout << "Introduce el lado 1 del triangulo : ";
	cin >> lado1;
	cout << "Introduce el lado 2 del triangulo : ";
	cin >> lado2;
	cout << "Introduce el angulo del triangulo : ";
	cin >> angulo;

	anguloRad=anguloRadianes(angulo);
	cout << "El area del triangulo es : " << areaTriangulo(lado1,lado2,anguloRad) << endl;

	return 0;
}

double anguloRadianes(int angulo){
	const double PI =3.141592;
	double radianes;
	radianes =(angulo*PI)/180;
	return radianes;
}

double areaTriangulo(double lado1, double lado2, double radianes){
	double area;
	area = (1/2.0) * lado1 *lado2 * sin(radianes);
	return area;
}