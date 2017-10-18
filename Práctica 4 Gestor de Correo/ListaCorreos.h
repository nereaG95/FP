#ifndef ListaCorreos_h
#define ListaCorreos_h
#include <string>
#include "Correo.h"

using std::string;

const string TERMINACION_ARCHIVOCORREO = "_listaCorreo.txt";
const int MAX_CORREOS=20; 
typedef tCorreo tArrayCorreo[MAX_CORREOS];

typedef struct{
	tArrayCorreo correo;
	int cont;
}tListaCorreos;

/*Funcion que dada una lista de correos la inicializa de forma que pone el contador a 0
	S: correos, sale modificado de forma que el contador esta a 0*/
void inicializar(tListaCorreos &correos);

/*Funcion que dado un dominio carga la lista de correos del archivo, devuelve
true si se ha podido abrir el archivo y false en caso contrario. Si el archivo se ha abierto carga cada correo
hasta que el identificador sea XXX o se haya llenado la lista
	S: correos, la lista de correos sale modificada con los correos que se han cargado y el contador actualizado indicando
	el numero de correos que hay.
	E: dominio, indica el dominio para abrir el archivo dominio+_listacorreo*/
bool cargar(tListaCorreos &correos, string dominio);

/*Funcion que guarda la lista de correos en el archivo de texto, para ello llamamos a la funcion guardar
del modulo correos, para que vaya guardando cada correo.
	-E: correos: lista de correos que vamos a guardar en el archivo de texto
		-dominio: es el dominio que usamos, que nos va a indicar el nombre del archivo dominio+"_listacorreo"*/
void guardar(const tListaCorreos &correos, string dominio);

/*Funcion que dado un correo lo inserta en la lista de correos si esta no está llena, devuelve true si se ha
insertado correctamente y false en caso contrario (cuando la lista este llena).
	E: correo: es el correo que vamos a insertar en la lista de correos.
	S: corroes: es la lista de correos, la cual va a salir modificada con los correos insertados y el contador actualizado*/
bool insertar(tListaCorreos &correos, const tCorreo &correo);

/*Funcion que devuelve true si se ha encontrado el id en la lista de correos y false en caso contrario. Además devuelve
la posicion en la que se encuentra el id y en caso de que no este indica la posicion en la que deberia estar. Para esta 
busqueda utilizados el algoritmo de busqueda binaria.
	E: correos: lista de correos en la que vamos a buscar el id
		id: el id que vamos a buscar en la lista de correos
	S: - pos: indica la posicion en la que se encuentra el correo con el id correspondiente, o en la que se deberia 
	encontrar si el correo con ese id todavía no está*/
bool buscar(const tListaCorreos &correos, string id, int &pos);

/*Funcion que dada una lista de correos la ordena primero por asunto (omitiendo los "RE:") y si los asuntos son
iguales lo ordenamos por fecha, para ello hemos definido el operator en el modulo correo. Utilizamos el algoritmo
de la burbuja mejorado.
	S: correos: lista de correos que saldra modificada ordenada por asunto y despues fecha*/
void ordenar_AF(tListaCorreos &correos);

/*Funcion que dada una lista de correos y una posicion nos devuelve el correo que hay en la lista de correos en esa pos
	E: -correos: lista de correos en donde se va a buscar el correo a devolver
		- pos: posicion que ocupa el correo que queremos devolver*/
tCorreo obtenerCorreo(const tListaCorreos &correos, int pos);

/*Funcion que dada una lista de correos muestra los correos, la hemos usado para depurar */
void mostrarCorreos(const tListaCorreos &correos);

#endif