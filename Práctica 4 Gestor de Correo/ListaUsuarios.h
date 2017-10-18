#ifndef ListaUsuario_h
#define ListaUsuario_h

#include<string>
#include"Usuario.h"

using std::string;

const int MAX_USUARIO = 20;
const string TERMINACION_ARCHIVOUSUARIO= "_Usuarios.txt."/*, CENTINELA_FIN_ARCH = "XXX"*/; // Porque quitar CENTINELA_FIN_ARCH???

typedef tUsuario tArrayUsuaruo[MAX_USUARIO];

typedef struct{
	tArrayUsuaruo usuario;
	int cont;
}tListaUsuarios;


/*
Es un procedimiento para poner el contador de usuarios a 0
S: es el usuario que sale inicializado
*/
void inicializar(tListaUsuarios &usuarios);
/*
Es una funcion de tipo booleana que carga en usuarios la lista de usuarios que se encuentra en dominio_Usuarios.txt, devuelve true si se a cargado correctamente y false en caso contrario
S: usuarios(tListaUsuarios) es donde se carga la lista de usuarios, si la carga a tenido exito
E: dominio(string) es el nombre del archivo de donde queremos cargar la lista de usuarios
*/
bool cargar(tListaUsuarios& usuarios, const string dominio);
/*
Es un procedimiento que guarda usuarios en un archivo con el nombre del dominio
E: usuario(tListaUsuarios) es la lista de usuarios que guarda en el archivo
   dominio(string) es el nombre que va a tener el archivo en el que se va a guardar sin la terminacion incluida
*/
void guardar(const tListaUsuarios& usuarios,const string dominio);
/*
Es una funcion de tipo booleana que dado una lista de usuarios y un usuario, introduce el usuario en esa lista de manera ordenada, devuelve true
si se añadio y false en caso contrario
E: usuario(tUsuario) es el usuario que queremos añadir
E/S: usuarios(tListaUsuarios) es la lista en donde lo queremos introducir
*/
bool aniadir(tListaUsuarios& usuarios, const tUsuario& usuario);
/*
Es una funcion de tipo booleano que dado una lista de usuarios y un id, hace una busqueda binaria para encontrar la posicion, devuelve true si la encontro y false si no,
y pos toma el valor de la posicion que se encuentra el usuario si a tenido exito la busqueda, y si no la tuvo,la posicion donde deberia estar ese usuario
E: usuarios(tListaUsuarios) es la lista en donde se va a buscar el usuario
   id(string) es el identificador del usuario que buscamos en la lista
S: posicion(int) es la posicion donde se encuentra el usuario su la busqueda a tenido exito o, si no lo tuvo, en donde deberia de estar
*/
bool buscarUsuario(const tListaUsuarios& usuarios, string id, int& posicion);
/*
Es un procedimiento que dada una lista de usuarios y un posicion desplaza en esa lista todos los elemento desde la posicion a la derecha para abrir hueco a  algo que queramos introducir
E/S: usuarios(tListaUsuarios) es la lista en la que vamos a desplazar los usuarios a la derecha
E: pos (int) es la posicion a partir de la cual desplazamos a la derecha
*/
void desplazarALaDerecha(tListaUsuarios &usuarios,int pos);
/*
Es un procedimiento que dado una lista de usuarios, un usuario y una posicion, introduce el usuario en la lista en la posicion que entra por parametro
E/S: usuarios(tListaUsuarios) es la lista de usuarios en la cual se introduce el usuario en la posicion indicada
E: usuario(tUsuario) es el usuario que queremos introducir en la lista
   pos(int) es la posicion donde queremos introducir el usuario
*/
void insertar(tListaUsuarios &usuarios,const tUsuario usuario, const int pos);
/*
Es una funcion de tipo tUsuario que dado una lista de usuarios y una posicion devuelve el usuario que se encuentra en esa posicion
E: usuarios(tListaUsuario) es la lista en la que se obtiene el usuario
   pos(int) es la posicion en la que se encuentra el usuario en la lista
*/
tUsuario dameUsuario(const tListaUsuarios &usuarios, const int pos);

#endif