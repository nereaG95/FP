#ifndef Usuario_h
#define Usuario_h

#include<string>
#include<fstream>
#include"ListaRegistros.h"

using std::string;
using std::ofstream;
using std::ifstream;

const string CENTINELA_FIN = "XXX";// porque poner aqui la constante de fin de archivo???
typedef struct {
	string id;
	string contrasenia;
	tListaRegCorreo recibidos;
	tListaRegCorreo enviados;
}tUsuario;
/*
Es una funcion de tipo booleana que devielve true si se a cargado correctamente el usuario y false cuando el id del es igual al centinela que señala el fion del archivo
E/S: archivo(ifstream) es un fujo de archivo ya abierto para cargar el usuario
S: usuario(tUsuario) si a salido todo bien sale el usuario ya cargado del archivo
*/
bool cargar(tUsuario& usuario, ifstream &archivo);
/*
Es un procedimiento que guarda el usuario en un archivo
E: usuario(tUsuario) es  el usuario que entra para cargarse en el archivo
E/S: archivo(ofstream) es un flujo de archivo ya abierto para guardar el usuario en el archivo
*/
void guardar(const tUsuario &usuario, ofstream &archivo);
/*
Es un procedimiento que inicializa un usuario con el id y la contraseña entrados por parametro, e inializa los contedores de las listas de registros a 0
E: id(string) id que se le va a asignar al usuario
   contrasenia(string) contrasenia que se le va a asignar al usuario
S: usuario(tUsuario) es el usuario que queremos inicializar, y sale ya inicializado
*/
void inicializar(tUsuario& usuario,  string id,  string contrasenia);
/*
Es una funcion booleana que dado un usuario y una contraseña los compara para ver si son iguales, devuelve true si los son y false en caso contrario
E: contrasenia(string): es la contraseña que queremos validar	
   usuario(tUsuario): es el usuario cuya contraseña queremos validar
*/
bool validarContrasenia(const tUsuario &usuario,  string contrasenia);

#endif