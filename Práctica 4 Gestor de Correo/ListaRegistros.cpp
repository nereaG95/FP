#include<iostream>

#include"ListaRegistros.h";

using namespace std;

void inicializar(tListaRegCorreo &listaReg){
	listaReg.cont = 0;
}

void guardar(const tListaRegCorreo &listaReg, ofstream& archivo){
	archivo << listaReg.cont << endl;
	for(int i=0; i < listaReg.cont; i++){
		archivo << listaReg.registros[i].id << "  ";
		archivo << listaReg.registros[i].leido << endl;
	}
}

bool correoLeido(tListaRegCorreo &listaReg, string id) {
	bool ok = false;
	int pos;
	pos = buscar(listaReg,id);
	if(pos!= -1){
		listaReg.registros[pos].leido = true;
		ok = true;
	}
	
	return ok;
}

int buscar(const tListaRegCorreo &listaReg, string id) {
	int pos = 0;
	bool encontrado = false;

	while(pos < listaReg.cont && !encontrado) {
		if(listaReg.registros[pos].id == id)
			encontrado = true;
		else
			pos++;
	}
	if(!encontrado)
		pos = -1;

	return pos;
}

bool insertar(tListaRegCorreo &listaReg, const tRegCorreo &registro){
	bool ok;
	if(listaReg.cont==MAX_REGISTROS){
		ok=false;
	}
	else{
		ok=true;
		listaReg.registros[listaReg.cont]=registro;
		listaReg.cont++;
	}
	return ok;
}

void cargar(tListaRegCorreo &listaReg, ifstream& archivo){
	tRegCorreo registro;
	int contador;
	inicializar(listaReg); //Inicializamos la lista
	archivo >> contador;//numero de registros que tenemos que leer
	for(int i=0; i < contador; i++){
		archivo >> registro.id >> registro.leido;
		insertar(listaReg, registro);
	}
}

bool borrar(tListaRegCorreo &listaReg, string id){
	bool ok=false;
	int pos = buscar(listaReg, id);
	if (pos != -1){ //Esta en la lista y lo borramos
		ok=true; 
		for(int i= pos ; i < listaReg.cont-1; i++){
			listaReg.registros[i]=listaReg.registros[i+1];
		}
		listaReg.cont--;
	}
	return ok;
}


void mostrarAlReves(const tListaRegCorreo &registros,const tListaCorreos &correos) {
	int pos;
	string id;
	for(int i = registros.cont - 1; i >= 0; i--){
		if(!registros.registros[i].leido){
			cout <<"* ";
		}
		else{
			cout <<"  ";
		}
		id=registros.registros[i].id; 
		buscar(correos,id,pos);
		cout  <<(registros.cont -i)<< " " << obtenerCabecera(correos.correo[pos]) << endl;
	}
}

void mostrarRegistros(const tListaRegCorreo &lista){
	for(int i=0; i< lista.cont; i++){
		cout << lista.registros[i].id << " " << lista.registros[i].leido << endl;
	}
}

bool solicitarPos( const tListaRegCorreo& listaReg , int &pos){
	bool ok=false;
	cout << "Introduzca la posicion del correo: ";
	cin >> pos;
	pos = listaReg.cont - pos;
	if(pos<listaReg.cont && pos>=0){
		ok=true;
	}
	return ok;
}