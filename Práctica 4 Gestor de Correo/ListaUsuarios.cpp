#include<fstream>
#include<sstream>

#include"ListaUsuarios.h"
#include"ListaRegistros.h"

using namespace std;

void inicializar(tListaUsuarios &usuarios){
	usuarios.cont = 0;
}

void guardar(const tListaUsuarios& usuarios, const string dominio){
	ofstream archivo;
	stringstream aux;
	string nombre;
	int i = 0;
	
	aux << dominio << TERMINACION_ARCHIVOUSUARIO;
	nombre = aux.str();
	archivo.open(nombre);

	for(int i=0; i < usuarios.cont; i++){
		guardar(usuarios.usuario[i], archivo);
	}
	archivo << CENTINELA_FIN;
	archivo.close();
	
}

bool aniadir(tListaUsuarios& usuarios, const tUsuario& usuario) {
	int pos;
	bool ok = true;

	//Se inserta si la lista de usuario no esta completa
	if( usuarios.cont == MAX_USUARIO)
		ok = false;
	else{
		if(!buscarUsuario(usuarios, usuario.id, pos)){// si no ha tenido exito la busqueda, se abre hueco y se introduce
			desplazarALaDerecha(usuarios, pos);
			insertar(usuarios, usuario, pos);
		}
		else
			ok = false;
	}

	return ok;
}

void insertar(tListaUsuarios &usuarios, const tUsuario usuario, const int pos){
	usuarios.usuario[pos] = usuario;
	usuarios.cont++;		

}

void desplazarALaDerecha(tListaUsuarios &usuarios,const int pos){
	for(int i = usuarios.cont; pos < i; i--){
			usuarios.usuario[i] = usuarios.usuario[i -1];
	}
}

bool buscarUsuario(const tListaUsuarios& usuarios, string id, int& posicion){
	int ini=0, fin=usuarios.cont-1, mitad;
	bool encontrado=false;
	while(ini<=fin && !encontrado){
		mitad= (ini + fin )/2;
		if(usuarios.usuario[mitad].id == id){
			encontrado=true;
			posicion=mitad;
		}
		else if ( usuarios.usuario[mitad].id <id){
			ini=mitad+1;
		}
		else{
			fin=mitad-1;
		}
	}
	if(!encontrado){
		posicion=ini;
	}
	return encontrado;
}

bool cargar(tListaUsuarios& usuarios, const string dominio){
	ifstream archivo;
	stringstream aux;
	string nombreArch;
	tUsuario usuario;
	bool ok=false;

	aux <<  dominio << TERMINACION_ARCHIVOUSUARIO;
	nombreArch=aux.str();
	archivo.open(nombreArch);
	if(archivo.is_open()){
		ok=true;
		inicializar(usuarios);
		while(cargar(usuario, archivo) && ok){ //Mientras no hallamos llegado al centinela y haya espacio seguimos leyendo
			ok= aniadir(usuarios,usuario);
		}
		ok=true;
	}
	return ok;
}

tUsuario dameUsuario(const tListaUsuarios &usuarios,const int pos){
	tUsuario usuario = usuarios.usuario[pos];
	return usuario;
}
