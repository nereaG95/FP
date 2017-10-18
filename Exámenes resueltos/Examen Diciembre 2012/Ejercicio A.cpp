#include <iostream>
#include <fstream>
using namespace std;


bool esCasiIgual (int numero, int num_usuario);
int main(){
	int numero, num_usuario;
	ifstream archivo;
	bool encontrado=false;
	cout << "Introduce un numero casi igual ";
	cin >> num_usuario;
	archivo.open("input.txt");
	if(archivo.is_open()){
		archivo >> numero;
		while (numero !=0 && !encontrado){
			if(esCasiIgual(numero, num_usuario)){
				encontrado=true;
			}
			else{
				archivo >> numero;
			}
		}
	}
	if (!encontrado){
		cout << "No se ha encontrado " << endl;
	}
	else
	{
		cout << "Se ha encontrado un numero casi igual que es  " << numero << endl;
	}
	system("pause");
	return 0;
}

bool esCasiIgual(int numero, int num_usuario){
	bool encontrado=false;
	if ( numero-2 <=num_usuario || num_usuario>=numero+2)
		encontrado=true;
	return encontrado;
}