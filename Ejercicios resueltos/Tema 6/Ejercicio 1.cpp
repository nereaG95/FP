#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

typedef enum{noPresentado,suspenso, aprobado, notable, sobresaliente,matriculaDeHonor} tCalificaciones;

string cadCalificaciones(tCalificaciones calificacion);
tCalificaciones calificacionToEnum(double nota);

int main(){
	double nota1, nota2;
	tCalificaciones calif1, calif2;
	string notaLetra1, notaLetra2;
	cout << "Nota 1: ";
	cin >> nota1;
	cout << "Nota 2: ";
	cin >> nota2;
	calif1= calificacionToEnum(nota1);
	calif2=calificacionToEnum(nota2);
	if ((nota1 >=0 && nota1 <=10) && (nota2>=0 && nota2<=10)){
		cout << "Nota 1: " << fixed << setprecision(1)<< nota1 << " ( " << cadCalificaciones(calif1) << " )"<<endl;
		cout << "Nota 2: " << fixed << setprecision(1)<< nota2 << " (" << cadCalificaciones(calif2)<< " ) " <<endl;
	}
	system("pause");
	return 0;
}

tCalificaciones calificacionToEnum(double nota){
	tCalificaciones calificacion;
	if (nota==0){
		calificacion=noPresentado;
	}
	else if ( nota <5){
		calificacion=suspenso;
	}
	else if (nota <7){
		calificacion=aprobado;
	}
	else if (nota <9){
		calificacion = notable;
	}
	else if ( nota <10){
		calificacion = sobresaliente;
	}
	else {
		calificacion= matriculaDeHonor;
	}
	return calificacion;
}

string cadCalificaciones(tCalificaciones calificacion){
	string cadena;
	if (calificacion==noPresentado){
		cadena="No presentado ";
	}else if(calificacion==suspenso){
		cadena="Suspenso ";
	}else if (calificacion==aprobado){
		cadena="Aprobado ";
	}else if (calificacion==notable){
		cadena="Notable ";
	}else if (calificacion== sobresaliente){
		cadena= "Sobresaliente ";
	}
	else {
		cadena="Matricula de Honor ";
	}
	return cadena;
}

