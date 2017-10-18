#include <iostream>
#include <fstream>
using namespace std;

int main(){
	ifstream archivo;
	int numero, num;
	bool encontrado=false;
	cout << "Introduce un numero positivo: ";
	cin >> numero;
	archivo.open("fibo.txt");
	if(archivo.is_open()){
		archivo >> num ;
		while (num!=-1 && !encontrado ){
			if (num%numero==0 && num >0){
				encontrado=true;
			}
			else{
				archivo >> num;
			}
		}
		if (!encontrado){
			cout << "Multiplo no encontrado " << endl;
		}
		else{
			cout << "Multiplo encontrado : " << num  << endl;
		}

	}
	system("pause");
	return 0;
}