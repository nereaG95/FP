#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int PALABRAS=25;
typedef string tVector[PALABRAS];
const string CENTINELA="XXX";

//Prototipos
int menu();
void mostrarLista(const tVector vector);  //Funcion que muestra la lista
int aparicionesPalabra(const tVector vector, string palabra); //Funcion que cuenta cuantas veces aparece una palabra
void palabraLongitud(const tVector vector, int longitud);//Funcion que devuelve la primera palabta y la posicion de la longitud a superar

int main(){
	ifstream archivo;
	tVector vector;
	int contador=0, op, longitud;
	string palabra;

	archivo.open("palabras.txt");
	if(archivo.is_open()){ //Si el archivo se ha abierto, lo leemos, guardamos los datos en el array 
		archivo >> vector[contador];
		while ((vector[contador]!=CENTINELA) && contador < PALABRAS){
			contador++;
			archivo >> vector[contador];
		}
		op=menu();
		while (op!=0){
			switch(op){
			case 1:
				cout << endl;
				mostrarLista(vector);//mostrar lista
				break;
			case 2: //Apariciones de una palabra
				cout << endl;
				cout << "Introduce la palabra a buscar : ";
				cin >> palabra;
				cout << palabra << " aparece " << aparicionesPalabra(vector, palabra) << " veces " << endl;
				break;
			case 3: //Primera palabra larga
				cout << endl;
				cout << " Longitud a superar : ";
				cin >> longitud;
				while (cin.fail()){
					cin.sync();
					cin.clear();
					cout << " Longitud a superar : ";
					cin >> longitud;
				}
				
				palabraLongitud(vector, longitud);
				break;
			}
			op=menu();
		}

	}
	system("pause");
	return 0;
}

//Funcion que nos dice la primera palabra que supera la longitud dada y la posicion en la que se encuentra
void palabraLongitud(const tVector vector, int longitud){
	string palabra;
	int contador=0;
	bool encontrado=false;
	while (contador < PALABRAS && !encontrado){
		if (longitud < vector[contador].size()){
			palabra=vector[contador];
			encontrado=true;
		}
		else{
			contador++;
		}
	}

	if (!encontrado){
		cout << "No se ha encontrado ninguna palabra de mas de " << longitud << " caracteres" << endl;
	}
	else{
		cout << "Primera palabra de mas de " << longitud << " caracteres es : " << palabra << " (Posicion : " << contador+1<<")"<<endl;
	}
}

//Funcion que devuelve el numero de veces que aparece una palabra dada
int aparicionesPalabra(const tVector vector, string palabra){
	int apariciones=0, contador=0;
	while (contador< PALABRAS && vector[contador]!=CENTINELA){ //Recorremos todo el array hasta que lleguemos a centinela
		if (vector[contador]==palabra){ //Si lo que hay en el vector es igual a la palabra se aumenta el contador
			apariciones++;
		}
		contador++;
	}
	return apariciones;
}

//Funcion que muestra la lista de palabras
void mostrarLista(const tVector vector){ 
	int i=0; //Posiciones del array
	while (i<PALABRAS && vector[i]!=CENTINELA){
		cout << i+1 <<" - " << vector[i] << endl;
		i++;
	}
}

//Funcion menu
int menu(){
	int op;
	cout << endl;
	cout << "1-Mostrar la lista " << endl;
	cout << "2-Contar las apariciones de una palabra " << endl;
	cout << "3-Primera palabra larga " << endl;
	cout << "0- Salir " << endl;
	cout << "Opcion : ";
	cin >> op;
	while (op<0 || op>3){
		cout << "Opcion incorrecta , introduzca una nueva : ";
		cin >> op;
	}
	return op;
}