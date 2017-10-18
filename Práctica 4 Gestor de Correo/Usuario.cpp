#include"Usuario.h"

using namespace std;

bool cargar(tUsuario& usuario, ifstream& archivo){
	bool ok=false;
	archivo >> usuario.id;
	if(usuario.id != CENTINELA_FIN){
		ok=true;
		archivo >> usuario.contrasenia;
		cargar(usuario.recibidos,archivo);
		cargar(usuario.enviados,archivo);
	}
	return ok;
}

bool validarContrasenia(const tUsuario &usuario, string contrasenia){
	return (usuario.contrasenia == contrasenia);
}

void guardar(const tUsuario& usuario, ofstream& archivo){
	archivo << usuario.id << endl;
	archivo << usuario.contrasenia << endl;
	guardar(usuario.recibidos, archivo);
	guardar(usuario.enviados, archivo);
}

void inicializar(tUsuario& usuario, string id,  string contrasenia){
	usuario.id=id;
	usuario.contrasenia=contrasenia;
	inicializar(usuario.recibidos);
	inicializar(usuario.enviados);
}



