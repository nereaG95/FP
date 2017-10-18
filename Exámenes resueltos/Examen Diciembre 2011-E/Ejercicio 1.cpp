#include <iostream>
#include <fstream>
using namespace std;

int main(){
	int numero, formula, fib1=0,fib2=1;
	ofstream archivo;
	cout << "Introduce un numero (mayor que 2 ): ";
	cin >> numero;
	while (numero<2){
		cout << "Error, introduce de nuevo: ";
		cin >>numero;
	}
	formula=fib1+fib2;

	archivo.open("fibo.txt");
		archivo << fib1 << endl;
		archivo << fib2 << endl;
		
		cout <<fib1 << " , " << fib2 << " , " ;
		for (int i=2; i<numero; i++){
			archivo << formula << endl;
			cout << formula << ", " ;
			fib1=fib2;
			fib2=formula;
			formula=fib1+fib2;
		}
		archivo << -1 << endl;
	archivo.close();
	system("pause");
	return  0;
}