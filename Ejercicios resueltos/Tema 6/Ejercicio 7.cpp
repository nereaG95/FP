#include <iostream>
using namespace std;

const int N=10;
typedef int tVector[N];

int mayorValor(const tVector vector); //Funcion que devuelve el mayor elemento del array
int sumaIgualResto(const tVector vector); //Funcion que devuelve la 1 posicion en la que el valor del array es igual a la suma del resto

int main(){
	tVector vector;
	for (int i=0;i<N; i++){ //Para probar introducimos los valores del array 
		cout << "Elemento : " << i << " : ";
		cin >> vector[i];
	}
	cout << "El mayor valor es : "<< mayorValor(vector)<<endl;
	cout << "La primera posicion en la que la suma es igual al valor del array " << sumaIgualResto(vector) << endl;
	system("pause");
	return 0;
}

int mayorValor(const tVector vector){
	int mayor=vector[0];
	for (int i=0; i<N; i++){
		if(vector[i]>mayor){
			mayor=vector[i];
		}
	}
	return mayor;
}

int sumaIgualResto(const tVector vector){
	bool encontrado = false;
	int pos=0, suma;
	while (pos<N && !encontrado){
		suma = 0; //Inicializamos la suma a 0  
		for(int posAux = 0; posAux <N; posAux++){
			if (pos != posAux){ //Si la posicion es distinta de la auxiliar se realiza la suma 
				suma =suma+vector[posAux];
			}
		}
		encontrado = (vector[pos] == suma); //Si el elemento del vector es igual a la suma se ha encontrado el elemento
		if (!encontrado) {
			pos++;
		}
	}
	if(!encontrado){ //Si no se ha encontrado devolvemos -1
		pos=-1;
	}
	return pos;
}


