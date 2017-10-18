#include<iostream>
#include<fstream>
#include<sstream>

#include"ListaCorreos.h"

using namespace std;

/*
Es un procedimiento que dado una lista de correos llena incrementa la capacidad para que haya espacio para mas elementos
E/S: correos(tlistaCorreos) es la lista que se amplia su capacidad
E: nuevaCapacidad(int) es la capacidad que queremos para la lista
*/
void redimensionar(tListaCorreos &correos, int nuevaCapacidad);
/*
Es un procedimiento que inicializa la lista con n posiciones que le pasan por parametro
E/S: correos(listaCorreos) es la lista que queremos inicializar, 
E: n(int) señala las posiciones con las que queremos inicializar la lista
*/
void inicializar(tListaCorreos &correos, int n);

/*Subprograma que dada una lista de correos y una posicion , desplaza los correos a la derecha
a partir de la posicion dada*/
void desplazarALaDerecha(tListaCorreos &correos, int pos);

/*Subprograma que dado un correo lo inserta en la lista de correos en la posicion
indicada y aumentamos el contador de la lista de correos*/
void insertarCorreo(tListaCorreos &correos, const tCorreo &correo, int pos);


void inicializar(tListaCorreos &correos){
	inicializar(correos,MAX_CORREOS);
}

void redimensionar(tListaCorreos &correos, int nuevaCapacidad){
	tPuntCorreo correosAux = new tCorreo[nuevaCapacidad];
	//Copiamos el array en el aux;
	for(int i=0; i< correos.cont; i++){
		correosAux[i]=correos.correo[i];
	}
	delete [] correos.correo;
	correos.correo=correosAux;
	correos.capacidadActual=nuevaCapacidad;
}

bool cargar(tListaCorreos &correos, string dominio){
	ifstream archivo;
	stringstream aux;
	string nombre, id;
	tCorreo correo;
	int maximo;
	int  i = 0;
	bool ok = false;

	aux << dominio << TERMINACION_ARCHIVOCORREO;
	nombre = aux.str();
	archivo.open(nombre);
	if(archivo.is_open()) {
		ok = true;
		archivo >> maximo;
		inicializar(correos,(maximo - (maximo % 10)) + 10);
		for(int i=0; i< maximo; i++){
			cargar(correo, archivo);
			insertar(correos, correo);
		}
	
		ok=true;
		archivo.close();
	}
	return ok;
}

void inicializar(tListaCorreos &correos, int n){
	correos.cont=0;
	correos.capacidadActual=n;
	correos.correo = new tCorreo [n];
}

void insertar(tListaCorreos &correos, const tCorreo &correo){
	int pos;
	if(correos.cont==correos.capacidadActual){
		redimensionar(correos, (correos.capacidadActual*3)/2+1);
	}
	//1.buscamos
	if(!buscar(correos,correo.id,pos)){
		//2.Desplazamos a la derecha
		desplazarALaDerecha(correos,pos);
		//3. Insertamos
		insertarCorreo(correos, correo, pos);
	}
}

void desplazarALaDerecha(tListaCorreos &correos, int pos){
	for(int i=correos.cont; i > pos;i--){
		correos.correo[i] = correos.correo[i-1];
	}
}

void insertarCorreo(tListaCorreos &correos, const tCorreo &correo, int pos){
	correos.correo[pos]=correo;
	correos.cont++;
}

bool buscar(const tListaCorreos &correos, string id, int &pos){ 
	int mitad, fin=correos.cont-1, ini=0;
	bool  encontrado=false;
	tCorreo correo;

	while((ini <=fin)  && !encontrado){
		mitad=(ini+fin)/2;
		correo =  correos.correo[mitad];
		if(id == correo.id){
			encontrado=true;
			pos=mitad;
		}
		else{
			if(id < correo.id){
				fin=mitad-1;
			}
			else{
				ini=mitad+1;
			}
		}
	}
	if(!encontrado){
		pos=ini;
	}
	return encontrado;
}

void ordenar_AF(tListaCorreos &correos){
	bool inter = true;
	int i = 0;

	while ((i < correos.cont) && inter){
		inter = false;
		for(int j = correos.cont - 1; j > i; j--){
			if(correos.correo[j - 1] > correos.correo[j]){
				tCorreo tmp;
				tmp = correos.correo[j];
				correos.correo[j] = correos.correo[j - 1];
				correos.correo[j - 1] = tmp;
				inter = true;
			}
		}
		if(inter)
			i++;
	}
}

void guardar(const tListaCorreos &correos, string dominio){
	ofstream archivo;
	stringstream aux;
	string nombreArch, id;
	int i=0;

	aux << dominio << TERMINACION_ARCHIVOCORREO;
	nombreArch = aux.str();
	archivo.open(nombreArch);
	archivo << correos.cont << endl;
	for(int i=0; i < correos.cont; i++){
		guardar(correos.correo[i], archivo);
	}
	archivo.close();
}

tCorreo obtenerCorreo(const tListaCorreos &correos, int pos){
	return correos.correo[pos];
}

void mostrarCorreos(const tListaCorreos &correos){
	for(int i=0; i<correos.cont;i++){
		cout << aCadena(correos.correo[i]) << endl;
	}
}

void destruir(tListaCorreos &correos){
	delete [] correos.correo;
	correos.cont=0;
}