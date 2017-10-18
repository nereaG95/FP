#ifndef ListaRegistros_h
#define ListaRegistros_h

#include <string>
#include<fstream>
#include "ListaCorreos.h"

using std::ofstream;
using std::ifstream;
using std::string;

const int MAX_REGISTROS = 10;

typedef struct {
	string id;
	bool leido;
}tRegCorreo;

typedef tRegCorreo tLista[MAX_REGISTROS];

typedef struct {
	tLista registros;
	int cont;
}tListaRegCorreo;

/*Funcion que dada una lista de registros la inicializa poniendo
contador a 0 (indica que hay 0 registros).
	S: listaReg: lista de registros, que va a salir modificada con el
	contador a 0*/
void inicializar(tListaRegCorreo &listaReg);

/*Funcion que carga una lista de registros, el archivo nos llega abierto. Para ello, primero
lee el numero de registros que hay y despues lee el registro(el id y si el correo está leido)
y lo inserta en la lista de registros.
	S:listaReg: lista de registros, que sale modificada con los registros que se han cargado
	del archivo.
	-E/S:archivo: flujo de archivo de entrada, el cual viene abierto, sale el archivo modificado con lo
	que se ha cargado.*/
void cargar(tListaRegCorreo &listaReg, ifstream& archivo);

/*Funcion que dada una lista de registros la guarda en el archivo, el cual ya viene abierto.
		E: -listaReg: lista de registros que vamos a guardar en el archivo
		E/S: archivo: archivo de salida que entra abierto y sale modificado con lo que se ha cargado*/
void guardar(const tListaRegCorreo &listaReg, ofstream& archivo);

/*Funcion que dado un registro lo inserta en la lista de registros si esta no está llena, devuelve true si se ha
insertado correctamente y false en caso contrario (cuando la lista este llena).Esta funcion inserta el registro al final de la lista.
	E: registro: es el registro que vamos a insertar en la lista de registros.
	E/S: listaReg: es la lista de registros, la cual va a salir modificada con los registros insertados y el contador actualizado*/
bool insertar(tListaRegCorreo &listaReg, const tRegCorreo & registro);

/*Funcion que dado un id, busca el id en la lista de registros y elimina el registro correspondiente
que tiene ese id. Devuelve true si se ha borrado el registro y false en caso contrario
	E/S:-listaReg: lista de registros en la que se va a buscar el registro a borrar, sale modificada si
	se ha encontrado el registro que se quiere borrar, es decir, saldra con un registro menos, el contador
	disminuye.
	E: -id: es el identificador del registro que queremos borrar.*/
bool borrar(tListaRegCorreo &listaReg, string id);

/*Funcion que dada una lista de registros y un id , devuelve true si se ha encontrado el registro (usando la funcion buscar del
modulo lista registros) y se ha marcado el correo como leido y false en caso contrario.
	E/S:-listaReg: lista de registros en la que se va a buscar el registro que se quiere marcar como leido, sale modificada si
	se ha encontrado el registro que queremos marcar como leido.
	E: - id:es el identificador del registro que queremos marcar como leido.*/
bool correoLeido(tListaRegCorreo &listaReg, string id);

/*Funcion que dada una lista de registros y un id , devuelve la posicion en la que se 
encuentra, si no está devuelve -1. Utilizamos la busqueda secuencial, ya que la lista de registros
no sigue ningun orden.
	E: listaReg: lista de registros en la que vamos a mirar si está el registro que tiene el id correspondiente
	-id: id que vamos a buscar en la lista de registros*/
int buscar(const tListaRegCorreo &listaReg, string id);

/*Funcion que muestra los correos correspondientes a la lista de registros, empezando desde el ultimo registro hasta el primero.
Para ello se busca el correo en la lista de correo, a partir del id que hay en el registro y mostramos el correo
	E: -registros: lista de registros, de la cual vamos a mostrar los correos correspondientes
	   -correos:lista de correos, en la que vamos a buscar el correo correspondiente de la lista de registros y mostrarlo*/
void mostrarAlReves(const tListaRegCorreo &registros,const tListaCorreos &correos);

/*Funcion que dada una lista de registros muestra los registros*/
void mostrarRegistros(const tListaRegCorreo &lista);

/*Funcion que dada una lista de registros, devuelve true si la posicion que introduce el usaurio es valida y false
en caso contrario. También devuelve la posicion que indica el usuario.
	E: listareg: lista de registros de la que el usuario va a pedir la posicion del registro que desea
	S: -pos: posicion en la que se encuentra el registro que indica el usuario*/
bool solicitarPos( const tListaRegCorreo& listaReg , int &pos);
#endif