#include <iostream>
#include <iomanip >
using namespace std;

const int N=10;
typedef double tVector[N];
tVector estudiante;

double notaMedia (const tVector estudiante);
int suspensos(const tVector estudiante);

int main(){
	
	for (int i=0; i< N; i++){
		cout << "Introduce la nota del estudiante " << i+1 <<": ";
		cin >> estudiante[i];
	}
	for (int i=0; i<N; i++){
		cout << "Nota del estudiante " << i+1 << ": " <<left << setw(4) << estudiante[i] << endl;
	}
	cout << "La nota media es : " << fixed << setprecision(2) << notaMedia (estudiante) << endl;
	cout << "El numero de suspensos es : " << suspensos(estudiante) << " y el de aprobados : " << (N-suspensos(estudiante))<< endl;

	system("pause");
	return 0;
}

double notaMedia (const tVector estudiante){
	double notaMedia, suma=0;
	for (int i=0; i< N; i++){
		suma=suma+ estudiante[i];
	}
	notaMedia = suma /N;

	return notaMedia;
}

int suspensos(const tVector estudiante){
	int suspensos=0;
	for (int i=0; i<N; i++){
		if (estudiante[i]<5){
		suspensos=suspensos++;
		}
	}
	return suspensos;
}

