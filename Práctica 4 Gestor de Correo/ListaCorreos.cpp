#include<iostream>
#include<fstream>
#include<sstream>

#include"ListaCorreos.h"

using namespace std;

/*Subprograma que dada una lista de correos y una posicion , desplaza los correos a la derecha
a partir de la posicion dada*/
void desplazarALaDerecha(tListaCorreos &correos, int pos);

/*Subprograma que dado un correo lo inserta en la lista de correos en la posicion
indicada y aumentamos el contador de la lista de correos*/
void insertarCorreo(tListaCorreos &correos, const tCorreo &correo, int pos);

bool cargar(tListaCorreos &correos, string dominio){
	ifstream archivo;
	stringstream aux;
	string nombre;
	tCorreo correo;
	bool ok = false;

	aux << dominio << TERMINACION_ARCHIVOCORREO;
	nombre = aux.str();
	archivo.open(nombre);
	if(archivo.is_open()) {
		ok = true;
		inicializar(correos);
		while((cargar(correo, archivo)) && ok){
			ok=insertar(correos, correo);
		}
		ok=true;
		archivo.close();
	}
	return ok;
}

void inicializar(tListaCorreos &correos){
	correos.cont=0;
}

bool insertar(tListaCorreos &correos, const tCorreo &correo){
	bool ok=true;
	int pos;
	if(correos.cont==MAX_CORREOS){
		ok=false;
	}
	else{
		//1.buscamos
		if(!buscar(correos,correo.id,pos)){
			//2.Desplazamos a la derecha
			desplazarALaDerecha(correos,pos);
			//3. Insertamos
			insertarCorreo(correos, correo, pos);
		}
		else{
			ok=false;
		}	
	}
	return ok;
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
	for(int i=0; i < correos.cont; i++){
		guardar(correos.correo[i], archivo);
	}
	archivo << CENTINELA_FIN_ARCH;
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