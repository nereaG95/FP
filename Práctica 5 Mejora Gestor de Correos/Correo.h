#ifndef Correo_h
#define Correo_h

#include<string>
#include<fstream>
#include <ctime>

using std::string;
using std::ifstream;
using std::ofstream;
using std::ctime;

const string CENTINELA_MENSAJE = "X", CENTINELA_FIN_ARCH = "XXX";

typedef time_t tFecha;

typedef struct{
	string emisor;
	string destinatario;
	string asunto;
	string cuerpo;
	tFecha fecha;
	string id;
}tCorreo;

typedef tCorreo *tPuntCorreo;

/*Funcion que dado un emisor devuelve un correo nuevo, para ello pide los datos
de destinatario, asunto y cuerpo al usuario. La fecha y el id los generamos
a partid de la funcion generarIdYFecha.
	E: emisor, variable de tipo string que indica quien es la persona que envia el correo
	S: correo, se devuelve un correo con todos sus campos completos*/
void correoNuevo(tCorreo &correo, string emisor);

/*Funcion que dado un correoOriginal y un emisor devuelve un correo contestacion. El destinatario
del correo es el emisor del correo original y el asunto sera el mismo que el del correo original
pero a?adiendole "RE:" , el cuerpo del correo constara del cuerpo que introduzca el usuario
mas el emisor, destinatrio, fecha, asunto y cuerpo del correoOriginal
	E:-correoOriginal: es el correo al que se va a contestar
	  -emisor: persona que le va a contestar al correo.
	S: - correo: es el correo que devolvemos como correo contestacion al correo original.*/
void correoContestacion(const tCorreo &correoOriginal, tCorreo &correo, string emisor);

/*Funcion que dado un correo devuelve un string con todos los datos del correo. Para ello vamos a ir concatenando
con una variable stringstream todos los datos y despues la convertimos a un string
	E: -correo: correo con el que vamos a generar el string */
string aCadena(const tCorreo &correo);

/*Funcion que dado un correo devuelve la cabecera de este, es decir un string
con el emisor, el asunto y la fecha.
	E: -correo: a partir de este vamos a generar la cabecera*/
string obtenerCabecera(const tCorreo &correo);

/*Funcion booleana que devuelve true si se ha podido cargar un correo, es decir
cuando el id es distinto del centinela final y devuelve false en caso contrario.
	-S: correo: devuelve el correo cargado del archivo
	-E/S: archivo: archivo de entrada, el cual ya esta abierto y sale modificado con lo que 
	se ha cargado
*/
void cargar(tCorreo &correo, ifstream &archivo);

/*Funcion que dado un correo y un flujo abierto guarda los datos del correo
que le pasamos
	-E: correo: correo que vamos a guardar en el archivo
	-E/S: archivo:  archivo de salida, el cual ya esta abierto, saldra modificado con
	los datos escritos*/
void guardar(const tCorreo &correo, ofstream &archivo);

/*
Operator que devuelve true cuando el operando izquiero es mayor que el operando derecho si el izq.id es mayor que el der.id 
*/
bool operator<(tCorreo izq, tCorreo der);

/*
Operator que devuelve true cuando el operando izquiero es igual que el operando derecho si el izq.id es igual que el der.id 
*/
bool operator==(tCorreo izq, tCorreo der);

/*Operator que devuelve true cuando el operando izquiero es mayor que el operando derecho,
para ello primero miramos si el izq.asunto es mayor que el der.asunto (omitiendo los RE: encaso de
que los halla), si izq.asunto es igual que der.asunto entonces comprobamos si
izq.fecha es mayor que der.fecha, cuando es mayor se devuelve true, y false en caos contrario*/
bool operator>(const tCorreo &izq, const tCorreo &der);


#endif