#include <fstream>
#include<iostream>
#include<sstream>

#include "correo.h"

using namespace std;


/*Funcion que solicita el cuerpo al usuario y devuelve un string con las varias lineas de
cuerpo concatenadas */
string solicitarCuerpo();

/*Funcion que dado un correo genera el id(emisor+"_"+fecha) y fecha (time(0)) y lo devuelve en el correo*/
void generarIdYFecha(tCorreo &correo);

/*Funcion que dado un tipo tFecha devuelve un string con la fecha en formato
tipo año/mes/dia (hora:minutos:segundos)
	E: fecha: tipo tfecha que queremos que nos lo muestre con el formato descrito
	anteriormente
*/
string mostrarFecha(tFecha fecha);

/*Funcion que dado un tipo tFecha devuelve un string con la fecha en formato tipo año/mes/dia sin la hora
	E: fecha: tipo tfecha que queremos que nos lo muestre con el formato descrito anteriormente
*/
string fechaSinHora(tFecha fecha, tm &ltm);

void correoNuevo(tCorreo &correo, string emisor){
	correo.emisor = emisor;
	cout << "Introduzca un destinatario: ";
	cin >> correo.destinatario;
	cout << "Asunto : ";
	cin.sync();
	getline(cin, correo.asunto);
	correo.cuerpo=solicitarCuerpo();
	generarIdYFecha(correo);
}

void correoContestacion(const tCorreo &correoOriginal, tCorreo &correo, string emisor){
	stringstream asunt, cuerp;
	string  cuerpo;

	correo.emisor = emisor;
	correo.destinatario = correoOriginal.emisor;
	asunt << "RE: " << correoOriginal.asunto;
	correo.asunto=asunt.str();
	cuerpo = solicitarCuerpo(); //Solicitamos el cuerpo
	cuerp << cuerpo << endl << aCadena(correoOriginal); 
	correo.cuerpo=cuerp.str();
	generarIdYFecha(correo);
}


string solicitarCuerpo(){
	stringstream cuerpo;
	string mensaje;
	cout << "Introduzca el mensaje(introduzca una X para acabar): ";
	getline(cin,mensaje);
	while(mensaje != CENTINELA_MENSAJE){
		cuerpo << mensaje << endl;
		getline(cin, mensaje);
	}
	mensaje= cuerpo.str();
	return mensaje;
}

void generarIdYFecha(tCorreo &correo){
	stringstream id;
	correo.fecha = time(0);
	id << correo.emisor << "_" << correo.fecha;
	correo.id = id.str();
}

string aCadena(const tCorreo &correo){
	stringstream cadena;
	string cad;
	cadena << "De :" << correo.emisor << "			"<< mostrarFecha(correo.fecha)<< endl;
	cadena << "Para :" << correo.destinatario << endl;
	cadena << "Asunto : " << correo.asunto  << endl;
	cadena << correo.cuerpo << endl;
	cad=cadena.str();
	return cad;
}

string mostrarFecha(tFecha fecha) {
	stringstream resultado;
	string fechaSinhora;
	tm ltm;
	//localtime_s(&ltm, &fecha);
	//resultado << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon << "/" << 1 + ltm.tm_mday;
	fechaSinhora=fechaSinHora(fecha, ltm);
	resultado << fechaSinhora << " (" << ltm.tm_hour << ":" << ltm.tm_sec << ")";
	return resultado.str();
}

string fechaSinHora(tFecha fecha, tm &ltm){
	stringstream resultado;
	localtime_s(&ltm, &fecha);
	resultado << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon << "/" << 1 + ltm.tm_mday;
	return resultado.str();
}


string obtenerCabecera(const tCorreo &correo){
	tm ltm;
	stringstream cabecera;
	string cadena;
	cabecera <<"	"<< correo.emisor << "	" << correo.asunto << "	" <<fechaSinHora(correo.fecha,ltm);
	cadena=cabecera.str();
	return cadena;
}

bool cargar(tCorreo &correo, ifstream &archivo){
	bool ok = true;
	string aux, id;
	stringstream cuerpo;
	
	archivo >> id;
	if(id == CENTINELA_FIN_ARCH)
		ok = false;
	else {
		correo.id = id;
		archivo >> correo.fecha >> correo.emisor >> correo.destinatario;
		getline(archivo,aux); // leo el espacio en blanco que queda en la linea
		getline(archivo,correo.asunto);

		getline(archivo,aux);// Comprueba que la primera linea del mensaje sea el centinela
		while(aux != CENTINELA_MENSAJE) {
			cuerpo << aux << endl;
			getline(archivo,aux);
		}
		correo.cuerpo = cuerpo.str();
	}
	return ok;
}

void guardar(const tCorreo &correo, ofstream &archivo){
	archivo << correo.id << endl;
	archivo << correo.fecha << endl;
	archivo << correo.emisor << endl;
	archivo << correo.destinatario << endl;
	archivo << correo.asunto << endl;
	archivo << correo.cuerpo ;
	archivo << "X" << endl;

}

bool operator==(tCorreo izq, tCorreo der){
	return izq.id == der.id;
}

bool operator<(tCorreo izq, tCorreo der){
	return izq.id < der.id;
}

bool operator>(const tCorreo &izq,const tCorreo &der){
	bool mayorQue = false;
	string asunto1=izq.asunto, subasunto1, asunto2=der.asunto, subasunto2;
	subasunto1=izq.asunto.substr(0,4);
	subasunto2= der.asunto.substr(0,4);
	if(subasunto1 == "RE: "){
		asunto1=asunto1.erase(0,4);
	}
	if (subasunto2=="RE: "){
		asunto2=asunto2.erase(0,4);
	}
	if(asunto1 > asunto2)
		mayorQue = true;
	else if (asunto1 == asunto2){
		if(izq.fecha > der.fecha)
			mayorQue = true;
	}
	return mayorQue;
}