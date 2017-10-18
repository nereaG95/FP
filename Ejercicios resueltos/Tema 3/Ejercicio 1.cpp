#include <iostream>
#include <cmath>
using namespace std;

double formula (int x, int y);

const double SIGMA = 2.34444;
const double LAMBDA=5.678;
const double ALFA=1.789;

int main(){
	int x,y;
	cout << "Introduce el valor de x : ";
	cin >> x;
	cout << "Introduce el valor de y : ";
	cin >> y;
	cout << " El resultado es : " << formula(x,y) << endl;
	system("pause");
	return 0;
}

double formula (int x, int y){
	double resultado;
	resultado = 3 *((x+ SIGMA*y)/(pow(x,2)-pow(y,2))) -LAMBDA * (ALFA-13.7);
	return resultado;
}