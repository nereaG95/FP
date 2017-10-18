#include "Gestor.h"
#include <iostream>
#include <sstream>
using namespace std;


/*Es un procedimiento que solicita al usuario una contrase?a y un identificador
S: contrasenia(string) toma el valor de la contrase?a introducida por el usuario
   id(string) toma el valor del identificador introducido por el usuario*/
void solicitarDatosNuevaCuenta(string &id , string &contra);
/*
Es una funcion de tipo string que dado un identificador lo devuelve con el @fdimail.com
E: id( string) es el identificador al cual le queremos a?adir @fdimail.com
*/
string dameIdConDominio(string id);
/*
Es una funcion de tipo int que muestra por pantalla las distintas opciones que hay, y segun el valor de entrada mostrar bandeja de entrada o de 
salida, devuelve un valor int introducido por el susuario que se?ala la opcion que a seleccionado el usuario
E: entrada(bool) segun el valor que tenga mostrara bandeja de entrada o badeja de salida
*/
int mostrarOpciones(bool entrada);
/*
Es un procedimiento que muestra por pantalla una barra de separacion
*/
void barraSeparacion();
/*
Es una funcion de tipo int que muestra por pantalla el menu de leer correo y devuelve un int que pide al usuario como opcion, hasta que no se
introduce una opcion valida, no se le para de solicitar al usuario una opcion
*/
int opcionLeerCorreo();

/*
Es un procedimiento que ejecuta la opcion lectura, dependiendo de si estamos en la bandejada
de entrada o de salida. Si no se puede leer el correo, informa del error.
*/
void opcionLecturaCorreo(tGestor &gestor, bool entrada);

void inicializar(tGestor &gestor,const string dominio){
	gestor.dominio = dominio;
	gestor.usuarioActivo = -1;
	inicializar(gestor.listaCorreos);
	inicializar(gestor.listaUsuarios);
}

void solicitarContrId(string &contrasenia,string &id) {
	cout << "Introduzca un id de usuario: ";
	cin >> id;
	cout << "Introduzca una contrasenia: ";
	cin >> contrasenia;
}

bool arrancar(tGestor& gestor,const string dominio){
	bool ok = false;
	inicializar(gestor,dominio);
	if(cargar(gestor.listaUsuarios, dominio) && cargar(gestor.listaCorreos, dominio))
		ok = true;
	return ok;
}

void solicitarDatosNuevaCuenta(string &id , string &contra){
	string contra2;
	do{
		solicitarContrId(contra, id);
		cout << "Introduce de nuevo la contraseña :";
		cin >> contra2;
		if(contra!=contra2){
			cout <<"Las contraseñas no coinciden, no se ha podido crear la cuenta" << endl;
			system("pause");
			system("cls");
		}
	}while(contra!=contra2);
}


bool crearCuenta(tGestor &gestor){
	string contrasenia, id;
	tUsuario usuario;
	int pos;
	bool ok = false;

	solicitarDatosNuevaCuenta(id , contrasenia);
	id=dameIdConDominio(id);
	if(!buscarUsuario(gestor.listaUsuarios, id, pos)){
		inicializar(usuario,id,contrasenia);
		if(aniadir(gestor.listaUsuarios, usuario)){
			gestor.usuarioActivo = pos;
			ok = true;
		}
	}
	return ok;
}

void apagar(const tGestor &gestor){
	guardar(gestor.listaUsuarios,gestor.dominio); //Guardamos la lista de usuarios
	guardar(gestor.listaCorreos, gestor.dominio); //Guardamos la lista de correos
}

bool iniciarSesion(tGestor &gestor){
	tUsuario usuario;
	int pos;
	bool ok = false, encontrado;
	string id,contra;

	solicitarContrId(contra,id);
	id=dameIdConDominio(id);
	encontrado=buscarUsuario(gestor.listaUsuarios, id, pos);
	usuario=dameUsuario(gestor.listaUsuarios,pos);
	if (encontrado && validarContrasenia(usuario,contra)){ //si la contrase?a es correcta y el usuario se encuentra en la lista
		gestor.usuarioActivo = pos; 
		ok = true;
	}
	else //No se encuentra el usuario o la contrase?a es incorrecta
		gestor.usuarioActivo=INACTIVO;

	return ok;
}

bool leerCorreo(tGestor& gestor, tListaRegCorreo& listaReg){
	int pos;
	bool ok=false;
	bool prueba;
	tCorreo correo;
	if(solicitarPos(listaReg,pos)){
		if(correoLeido(listaReg,listaReg.registros[pos].id)){
			ok=true;
			//prueba=buscar(gestor.listaCorreos, listaReg.registros[pos].id , pos);
			if(buscar(gestor.listaCorreos, listaReg.registros[pos].id , pos)){
				system("cls");
				correo=obtenerCorreo(gestor.listaCorreos,pos);
				menuLeerCorreo(gestor, correo);
			}
			else{
				cout << "ERROR: no se pudo mostrar, porque no se encuentra en la lista de correos"<<endl;
			}
		}
	}
	else{
		cout << "El numero de correo proporcionado no es valido :s" << endl;
	}
	return ok;
}

void menuLeerCorreo(tGestor &gestor, const tCorreo &correoOriginal){
	int op;
	tCorreo correoConst;
	tUsuario usuario;
	cout << aCadena(correoOriginal); 
	op=opcionLeerCorreo();
	if(op == 1){
		usuario=dameUsuario(gestor.listaUsuarios,gestor.usuarioActivo);
		correoContestacion(correoOriginal,correoConst,usuario.id);
		enviarCorreo(gestor , correoConst);
	}
	else{
		cout << "Hasta luego!" << endl;
	}
}

void borrarCorreo(tGestor& gestor, tListaRegCorreo& listaReg){
	int pos;
	string id;

	if(solicitarPos(listaReg,pos)){
		id = listaReg.registros[pos].id;
		if(buscar(listaReg,id) != -1){// si se encuentra el registro
			borrar(listaReg, id);
		}
	}
	else{
		cout << "La posicion introducida no es correcta, no se puede borrar el correo" << endl;
	}
}

int menuBandeja(tGestor &gestor, bool entrada){
	int op=-1;
	tUsuario usuarioActivo = dameUsuario(gestor.listaUsuarios, gestor.usuarioActivo);
	system("cls");
	cout << "Correo de : " << usuarioActivo.id << endl;
	cout << "----------------------- BANDEJA DE ";
	if(entrada){
		cout << "ENTRADA ";
	}
	else{
		cout <<"SALIDA ";
	}
	cout <<  "----------------------"<<endl;

	barraSeparacion();
	cout <<"L N" <<"	EMISOR"<<"		ASUNTO"<<"				FECHA"<<endl << endl;
	barraSeparacion();
	if(entrada)
		mostrarAlReves(usuarioActivo.recibidos, gestor.listaCorreos);
	else
		mostrarAlReves(usuarioActivo.enviados, gestor.listaCorreos);

	barraSeparacion();
	op=mostrarOpciones(entrada);
	return op;
}

void lecturaRapida(tGestor& gestor, tListaRegCorreo& listaReg){
	tListaCorreos correosAux;
	tCorreo correo;
	string id;
	int pos;
	correosAux.cont = 0;
	for(int i = 0; i < listaReg.cont; i++){
		if(!listaReg.registros[i].leido){
			listaReg.registros[i].leido = true;
			id = listaReg.registros[i].id;
			if(buscar(gestor.listaCorreos, id, pos)){
				correo=obtenerCorreo(gestor.listaCorreos,pos);
				insertar(correosAux,correo);
				//correosAux.correo[correosAux.cont]=obtenerCorreo(gestor.listaCorreos,pos);
				//correosAux.cont++;
			}
		}
	}
	ordenar_AF(correosAux);
	for(int i=0; i < correosAux.cont; i++){
		cout << aCadena(correosAux.correo[i]);
	}

}

void ejecutarMenuBandeja(tGestor &gestor, bool &entrada, int op){
	tCorreo correo;
	tListaRegCorreo registro;
	tUsuario usuario = dameUsuario(gestor.listaUsuarios, gestor.usuarioActivo); //Obtenemos el usuario
	switch (op){
	case 1:
		opcionLecturaCorreo(gestor,entrada);
		system("pause");
		break;
	case 2:
		correoNuevo(correo, usuario.id);
		if(!enviarCorreo(gestor,correo)){
			cout << "No se ha podido enviar el correo, lista de correos llena!!! " << endl;
		}
		break;
	case 3:
		if(entrada){ //Actualizamos el registro de recibidos o enviados del gestor
			borrarCorreo(gestor, gestor.listaUsuarios.usuario[gestor.usuarioActivo].recibidos);
		}
		else{
			borrarCorreo(gestor, gestor.listaUsuarios.usuario[gestor.usuarioActivo].enviados);
		}
		break;
	case 4:		//Ver bandeja de salida o entrada segun el valor de entrada 
		entrada=!entrada;
		break;
	case 5:
		system("cls");
		lecturaRapida(gestor, gestor.listaUsuarios.usuario[gestor.usuarioActivo].recibidos);
		system("pause");
		break;
	default:
		break;
	}
}

void opcionLecturaCorreo(tGestor &gestor, bool entrada){
	bool ok;
	if(entrada){
		ok=leerCorreo(gestor, gestor.listaUsuarios.usuario[gestor.usuarioActivo].recibidos);
	}
	else{
		ok=leerCorreo(gestor, gestor.listaUsuarios.usuario[gestor.usuarioActivo].enviados);
	}
	if(!ok){
		cout << "No se ha podido leer el correo " << endl;
	}
}

int mostrarOpciones(bool entrada){
	int op=-1;
	cout << "Elija una opcion : " << endl;
	cout << "1- Leer Correo" << endl;
	cout << "2- Enviar Correo" << endl;
	cout << "3- Borrar correo" << endl;
	cout << "4- Ver bandeja de ";
	if(entrada){
		cout << "salida" << endl;
	}
	else{
		cout << "entrada " << endl;
	}
	cout << "5- Lectura rapida de correos sin leer " << endl;
	cout <<"0 - Salir " << endl;
	do{
		cout << "Introduzca una opcion : ";
		cin >> op;
	} while (op<0 || op>5);
	return op;
}

void barraSeparacion(){
	cout << "-----------------------------------------------------------------"<< endl;
}

bool enviarCorreo(tGestor& gestor, const tCorreo &correo){
	tRegCorreo regUsuarioActivo;
	tListaRegCorreo recibidos, enviados;
	int pos;
	bool ok=false;
	if(insertar(gestor.listaCorreos, correo)){ //Insertamos el correo en la lista de correos del gestor
		ok=true;
		regUsuarioActivo.id = correo.id;
		regUsuarioActivo.leido = true;
		if(insertar(gestor.listaUsuarios.usuario[gestor.usuarioActivo].enviados,regUsuarioActivo)){
			regUsuarioActivo.leido = false;
			if(buscarUsuario(gestor.listaUsuarios, correo.destinatario, pos)){
				if(!insertar(gestor.listaUsuarios.usuario[pos].recibidos, regUsuarioActivo)){
					cout << "No se ha podido enviar, porque la bandeja de salida del destinatario esta llena" << endl;
				}
			}
			else{
				cout<< "No se ha encontrado el destinatario " << endl;
			}
		}
		else{
			cout << "No se ha podido enviar, porque el registro de salida esta lleno" << endl;
		}
	}
	return ok;
}

int opcionLeerCorreo(){
	int op=-1;
	barraSeparacion();
	cout << "Elija una opcion:" << endl;
	cout << "1-Contestar al correo"<< endl;
	cout << "0- Volver a la bandeja " <<endl;
	barraSeparacion();
	cout <<"Opcion : ";
	do{
		cin >>op;
	}while(op<0 || op>1);

	return op;
}

void ejecutarBandeja(tGestor &gestor, bool entrada){
	int opMenu=-1;
	do{
		opMenu=menuBandeja(gestor, entrada);
		ejecutarMenuBandeja(gestor,entrada,opMenu);
	}while(opMenu!=0);
}

//Dado el id, devuelve el id con el @+Dominio
string dameIdConDominio(string id){
	stringstream usuarioId;
	usuarioId << id << "@"<< DOMINIO;
	id=usuarioId.str();
	return id;
}