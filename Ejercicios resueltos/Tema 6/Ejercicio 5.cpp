#include <iostream>
using namespace std;
#include <fstream>
#include <string>

const int N=50;
typedef string tVector[N];
int menu();
void mostrarLista(const tVector palabras); //¿¿¿METER CONTADOR COMO PARAMETRO PARA QUE SOLO MUESTRE HASTA ESA POSICION??
int posicionPalabra (const tVector palabras, string buscar);

int main(){
	tVector palabras;
	ifstream archivo;
	string buscar;
	int contador=0, op, posicion;
	archivo.open("palabras.txt");
	if(archivo.is_open()){
		archivo >> palabras[contador];
		while ((contador<N) && (palabras[contador]!="XXX")){
			contador++;
			archivo >> palabras[contador];
		}
		op=menu ();
		while (op!=0){
			switch(op){
			case 1:
				{
					mostrarLista(palabras);
				}
				break;
			case 2:
				{
					cout << "Palabra a buscar : ";
					cin >> buscar;
					posicion=posicionPalabra (palabras, buscar);
					if (posicion<0){
						cout << "No se ha encontrado la palabra " << endl;
					}
					else{
						cout << "Esta en la posicion " << posicion << endl;
					}

				}
				break;
			}
			op=menu();
		}
	}
	else{
		cout << "El archivo no existe " << endl;
	}
	system("pause");
	return 0;
}

void mostrarLista(const tVector palabras){
	int i=0;
	while (palabras[i]!="XXX" && i <N){
		cout << i+1 << " - " << palabras[i] << endl;
		i++;
	}
}

int posicionPalabra (const tVector palabras, string buscar){
	bool encontrado =false;
	int i=0;
	int posicion;
	while (!encontrado && i<N && palabras[i]!="XXX"){
		if (palabras[i]==buscar){
			encontrado=true;
			posicion=i;
		}
		else{
			i++;
		}	
	}
	if(!encontrado){
		posicion=-1;
	}
	return posicion;
}
int menu(){
	int op=-1;
	cout << endl;
	cout << "1- Mostrar Lista " << endl;
	cout << "2- Buscar Palabra " << endl;
	cout << "0 - Salir " << endl;
	cout << "Opcion : " ;
	cin >> op;
	while (op<0 || op>2 || cin.fail()){
		cin.clear();
		cin.sync();
		cout << "Opcion : ";
		cin >> op;
	}
	return op;
}