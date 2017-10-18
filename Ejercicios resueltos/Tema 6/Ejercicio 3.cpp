#include <iostream >
using namespace std;

const int N=10;
typedef double tVector[N];

double sumaPares(const tVector num);
bool sonIguales (const tVector num1, const tVector num2);

int main (){
	tVector num1, num2;
	for (int i=0; i<N; i++){
		cout << "Introduce el elemento del vector 1 " << i+1 << ": " ;
		cin >> num1[i];
	}
	for (int i=0; i<N; i++){
		cout << "Introduce el elemento del vector 2 " << i+1 << ": " ;
		cin >> num2[i];
	}
	cout << "La suma de los indices pares es : " << sumaPares(num1) << endl;
	if (sonIguales(num1,num2)){
		cout << "Los dos vectores son iguales " << endl;
	}
	else {
		cout <<"Los vectores no son iguales " << endl;
	}
	system("pause");
	return 0;
}

double sumaPares(const tVector num){
	double suma=0;
	for (int i=0; i< N; i=i+2){
		suma=suma+num[i];
	}
	return suma;
}

bool sonIguales (const tVector num1, const tVector num2){
	bool iguales=true;
	int contador=0;
	while (contador < N && !iguales){
		if (num1[contador]!=num2[contador]){
			iguales=false;
		}
		contador++;
	 }
	return iguales;
}