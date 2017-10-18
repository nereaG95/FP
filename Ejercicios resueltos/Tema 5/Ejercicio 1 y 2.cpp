#include <iostream>
#include <string>
using namespace std;

int main(){
	int numero1, numero2, numero3, aux;

	cout << "Introduce el numero 1 : ";
	cin >> numero1;
	cout << "Introduce el numero 2 : ";
	cin >> numero2;
	cout << "Introduce el numero 3 : ";
	cin >> numero3;

	if ( numero1 > numero2){
		aux = numero1;
		numero1 =numero2;
		numero2 =aux;
	}
	if (numero1 > numero3){
		aux = numero1;
		numero1 =numero3;
		numero3=aux;
	}
	if(numero2 > numero3){
		aux=numero2;
		numero2=numero3;
		numero3=aux;
	}
	
	cout << numero1 << ", " << numero2 << ", " << numero3 << endl;

	/*if ((numero1 < numero2) &&  (numero1 < numero3) && (numero2 < numero3)){
		cout << numero1 << ", " << numero2 << ", " << numero3 << endl;
	}
	else if ((numero1 < numero2) &&  (numero1 < numero3) && (numero3 < numero2)){
		cout << numero1 << ", " << numero3 << ", " << numero2 << endl;
	}
	else if ((numero2 < numero1) &&  (numero2 < numero3) && (numero1 < numero3)){
		cout << numero2 << ", " << numero1 << ", " << numero3 << endl;
	}
	else if ((numero2 < numero1) &&  (numero2 < numero3) && (numero3 < numero1)){
		cout << numero2 << ", " << numero3 << ", " << numero1 << endl;
	}
	else if ((numero3 < numero1) &&  (numero3 < numero2) && (numero1 < numero2)){
		cout << numero3 << ", " << numero1 << ", " << numero2 << endl;
	}
	else if ((numero3 < numero1) &&  (numero3 < numero2) && (numero2 < numero1)){
		cout << numero3 << ", " << numero2 << ", " << numero1 << endl;
	}*/
	system("pause");
	return 0;
}

/*#include <iostream>
using namespace std;

int main(){
	int numero1, numero2, numero3;

	cout << "Introduce el numero 1 : ";
	cin >> numero1;
	cout << "Introduce el numero 2 : ";
	cin >> numero2;
	cout << "Introduce el numero 3 : ";
	cin >> numero3;

	if ((numero1 < numero2) &&  (numero1 < numero3) && (numero2 < numero3)){
		cout << numero1 << ", " << numero2 << ", " << numero3 << endl;
	}
	else if ((numero1 < numero2) &&  (numero1 < numero3) && (numero3 < numero2)){
		cout << numero1 << ", " << numero3 << ", " << numero2 << endl;
	}
	else if ((numero2 < numero1) &&  (numero2 < numero3) && (numero1 < numero3)){
		cout << numero2 << ", " << numero1 << ", " << numero3 << endl;
	}
	else if ((numero2 < numero1) &&  (numero2 < numero3) && (numero3 < numero1)){
		cout << numero2 << ", " << numero3 << ", " << numero1 << endl;
	}
	else if ((numero3 < numero1) &&  (numero3 < numero2) && (numero1 < numero2)){
		cout << numero3 << ", " << numero1 << ", " << numero2 << endl;
	}
	else if ((numero3 < numero1) &&  (numero3 < numero2) && (numero2 < numero1)){
		cout << numero3 << ", " << numero2 << ", " << numero1 << endl;
	}
	system("pause");
	return 0;
}*/