#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int N=15;
typedef int tVector[N];

void mostrarArray(const tVector vector);
int numeroDivisible(const tVector vector, int numero);
int sumaPares(int numero);
void mostrarSuma(const tVector vector);
bool cargarArchivo(tVector vector);
void generarArrayAleatorio(tVector vector);
void guardarFichero(const tVector vector);

int main(){
	tVector vector;
	int numero, pos;
	srand(time(NULL));
	if(cargarArchivo(vector)){
		mostrarArray(vector); //mostramos el array
		cout << "Introduce el numero por el que quieres que sea divisible : ";
		cin >> numero;
		pos=numeroDivisible(vector, numero);
		if(pos>=0){
			cout << "El primer numero divisible por " << numero << " es " << vector[pos] << " y esta en la posicion " << pos+1 << endl;
		}
		else{
			cout << "No se ha encontrado ningun numero" << endl;
		}
		mostrarSuma(vector);
	}
	else{
		generarArrayAleatorio(vector);
		mostrarArray(vector); //mostramos el array

	}
	system("pause");
	return 0;
}

void guardarFichero(const tVector vector){
	ofstream archivo;
	archivo.open("entero.txt");
	for (int i=0; i < N; i++){
		archivo << vector[i] << endl;
	}
	archivo.close();
}

void generarArrayAleatorio(tVector vector){
	for (int i=0; i<N ; i++){
		vector[i]= rand() % 1000 + 1;
	}
}

bool cargarArchivo(tVector vector){
	ifstream archivo;
	bool ok=false;
	int contador=0;
	archivo.open("enteros.txt");
	if(archivo.is_open()){
		ok=true;
		archivo >> vector[contador];
		while (vector[contador]!=0 && contador < N){
			contador++;
			archivo >> vector[contador];
		}
		archivo.close();
	}
	return ok;
}

void mostrarArray(const tVector vector){
	cout << "Contenido del array : " << endl;
	for (int i=0; i < N; i++){
		cout << i+1 << "- " << vector[i] << endl;
	}
}

int numeroDivisible(const tVector vector, int numero){
	bool encontrado=false;
	int contador=0;
	while ((contador < N) && (!encontrado)){
		if (vector[contador] % numero == 0){
			encontrado=true;
		}
		else{
			contador++;
		}
	}

	if (!encontrado){
		contador=-1;
	}

	return contador;
}

int sumaPares(int numero){
	int suma=0;
	for (int i=0; i< numero; i=i+2){
		suma=suma+i;
	}
	return suma;
}

void mostrarSuma(const tVector vector){
	for (int i=0; i<N; i++){
		cout << "Suma para : " << vector[i] << " - " << sumaPares(vector[i]) << endl;
	}
}
