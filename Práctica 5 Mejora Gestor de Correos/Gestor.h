#ifndef Gestor_h
#define Gestor_h

#include <string>
#include "ListaUsuarios.h"
#include "ListaCorreos.h"
#include "Correo.h"
#include "Usuario.h"
#include "ListaRegistros.h"
using std:: string;

const string DOMINIO="fdimail.com";
const int INACTIVO=-1;
typedef struct{
	string dominio;
	tListaUsuarios listaUsuarios;
	tListaCorreos listaCorreos;
	int usuarioActivo;
}tGestor;
/*
Es un procedimiento que daod un gestor y un dominio, inicializa el gestor
S: gestor(tGestor) es el gestor que sale inicializado
E: es el dominio que se le va a adjudicar al gestor
*/
void inicializar(tGestor &gestor,const string dominio);
/*
Es un procedimiento que solicita al usuario una contrase?a y un identificador
S: contrasenia(string) toma el valor de la contrase?a introducida por el usuario
   id(string) toma el valor del identificador introducido por el usuario
*/
void solicitarContrId(string &contrasenia,string &id);
/*
Es un procedimiento que muestra el correo por pantalla y le da la opcion de responderlo o no
E/S: gestor(tGestor) se usa para en caso de que el usuario quiera responder al correo se obtenga los registros y se busquen a los destinatarios
E: correoOriginal(tCorreo) es el correo que se va a mostrar por pantalla
*/
void menuLeerCorreo(tGestor &gestor, const tCorreo &correoOriginal);
/*
Es una funcion de tipo booleano que inicializa el gestor y devuelve true si se a cargado la lista de correos y la lista de usuarios correctamente y false en caso contrario
S: gestor(tGestor) es el gestor que inicializamos y en donde se cargan las listas
E: dominio(string) es el dominio con que se inicializa el gestor
*/
bool arrancar(tGestor& gestor,const string dominio);
/*
Es un procedimiento que guarda los regitro de usuarios y de correos del gestor en un archivo
E: gestor(tGestor) es donde se encuentran los registros de usuarios y de correos que se van a guardar
*/
void apagar(tGestor &gestor);
/*
Es una funcion de tipo booleano que pide al usuaario un id y una contrase?a, si el id no existe en el gestor, crea una cuenta y devuelve true,
en caso contrario devuelve false
E/S: gestor(tGestor) es donde se encuentra la lista de usuarios donde se compruebra si existe el id y si no existe lo a?ade
*/
bool crearCuenta(tGestor &gestor, bool &lleno);
/*
Es una funcion de tipo booleano que solicita al usuario un identificador y una contrase?a, y si existe el identificador y su contrase?a coincide
con la introducida por el usuario, la funcion devuelve true y pone como usuario activo la posicion donde se encuentra el identificador,
en caso contrario devuelve false
E/S: gestor(tGestor) es donde se busca si existe o no el usuario, valida la contrase?a y si se cumplen las dos condiciones pone usuario activo en la
     posicion donde se encuentra el usuario en la lista
*/
bool iniciarSesion(tGestor &gestor);
/*
Es una funcion de tipo booleano que solicita una posicion de correos al usuario y si existe, la marca como leido, lo muestra por pantalla y le da
al usuario la opcion de contestarle o no, en este caso la funcion devuelve true en caso contrario devuelve false
E/S: gestor(tGestor) es donde se busca el correo con el identificador
	 listaReg(tListaRegCorreo) es la lista de registro en donde le pedimos al usuario que seleccione un correo
*/
bool leerCorreo(tGestor& gestor, tListaRegCorreo& listaReg);
/*
Es una funcion de tipo booleano que inserta un correo en la lista de correo del gestor y en cada usuario pone el identificador en los registros
en enviados en el usuario que corresponda con leido a true y en el de recibidos en el usuario que corresponda con leido a false
E/S: gestor(tGestor) es donde se inserta el la lista de correos y en los registros de recibidos y enviados de los usuarios
E: correo (tCorreo) es el correo que se quiere enviar
*/
bool enviarCorreo(tGestor& gestor, const tCorreo &correo);
/*
Es un procedimiento que dado un gestor y una lista de registros, pide al usuario una posicion donde se encuentra el correo que se desea borrar y si
existe, borra el correo del registro del usuario
E/S: gestor(tGestor) 
	 listaReg(tListaRegCorreo) es la lista en la que se busca el correo que el usuario quiere borrar
*/
void borrarCorreo(tGestor& gestor, tListaRegCorreo& listaReg);
/*
Es un procedimiento que muestra por pantalla los correos no leidos 
E: gestor(tGestor) es donde se buscan los correos no leidos para mostrarlos por pantalla 
   listaReg(tListaRegCorreo) es la lista donde busca los correos que han sido y los que no han sido leidos
*/
void lecturaRapida(tGestor& gestor, tListaRegCorreo& listaReg);
/*
Es una funcion de tipo int que muestra por pantalla el usuario activo en ese momento y dependiendo del valor del parametro entrada muestra los
mensajes de salida o de entrada , taqmbien muestra las opciones al usuario llamando a otro subprograma y devuelve la opcion introducida por el 
usuario
E: gestor(tGestor) contine los correos y el usuario activo
   entrada(bool) si entrada= true es mensaje de entrada, false=mensaje de salida
*/
int menuBandeja(tGestor &gestor, bool entrada);
/*
Es un procedimiento que dependiendo de la oopcion que le llega por parametro ejecuta una opcion u otra
E/S: gestor(tGestor) se usa de una manera u otra segun que opcion llegue por parametro
     entrada(bool ) segun su valor se muesta la bandeja de entrada o la bandeja de salida, se cambia de valor si la opcion que le llega por parametro
	 es ver la otra badeja
E: op(int) segun el valor que tenga se ejecutara una funcion u otra
*/
void ejecutarMenuBandeja(tGestor &gestor, bool &entrada, int op);
/*
Es un procedimiento que hasta que pide al usuario un opcion y se ejecuta.
E/S: gestor(tGestor) segun la opcion introducida se llamara a un subprograma u a otro donde se le usara
E: entrada(bool) segun el valor que tenga se mostrara la bandeja de entrada o la de salida
*/
void ejecutarBandeja(tGestor &gestor, bool entrada);
#endif