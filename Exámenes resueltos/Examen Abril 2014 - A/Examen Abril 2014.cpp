#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int N=10;
const string CENTINELA="XXX";
const string ARCHIVO="peliculas.txt";
typedef struct{
	string titulo;
	int anio;
	double puntuacion;
}tPelicula;

typedef tPelicula tArrayPelis[N];
typedef struct{
	tArrayPelis peliculas;
	int cont;
}tListaPeliculas;

void inicializarLista(tListaPeliculas &lista);
bool cargarPeliculas(tListaPeliculas &listaPelis);
bool buscarPelicula(const tListaPeliculas &listaPelis, string titulo, int &pos);
bool peliValida(const tListaPeliculas &listaPelis, tPelicula pelicula);
void mostrarPeliculas(const tListaPeliculas &listaPelis);
void importarEstrenos(tListaPeliculas &listaPelis, bool &ok);
void insertarPeliculas(tListaPeliculas &listaPelis , bool &ok);
void abrirHueco(tListaPeliculas &listaPelis, int pos);
void insertarEnLista(tListaPeliculas &listaPelis, tPelicula pelicula,int pos);
void nuevoVoto(tListaPeliculas &listaPelis, bool &ok);
void ordenar(tListaPeliculas &lista);
bool operator>(tPelicula izq, tPelicula der );

int main(){
	tListaPeliculas peli;
	bool ok=false;
	if(cargarPeliculas(peli)){
		mostrarPeliculas(peli);
		importarEstrenos(peli, ok);
		if(ok){
			cout << endl << endl << "IMPORTACION DE NUEVAS PELIS " <<endl;
			mostrarPeliculas(peli);
			nuevoVoto(peli, ok);
			if(!ok){
				cout << "La pelicula no se encuentra disponible " << endl;
			}
			else{
				cout << "ACTUALIZACION" << endl;
				mostrarPeliculas(peli);
			}
			//Ordenar
			cout << endl << endl <<" LISTA ORDENADA POR PUNTUACION " << endl;
			ordenar(peli);
			mostrarPeliculas(peli);
		}
		else{
			cout << "No se ha podido insertar pq el fichero no se ha abierto " << endl;
		}
	}
	else{
		cout << "No se ha podido cargar";
	}
	system("pause");
	return 0;
}

void ordenar(tListaPeliculas &lista){
	for (int i = 0; i < N - 1; i++) { 
		int mayor = i; 
		for (int j = i + 1; j < N; j++) { 
			if (lista.peliculas[j] > lista.peliculas[mayor]) { 
				mayor = j; 
			 } 
		} 
		if (mayor > i) { 
			tPelicula tmp; 
			tmp = lista.peliculas[i]; 
			lista.peliculas[i] = lista.peliculas[mayor]; 
			lista.peliculas[mayor] = tmp; 
		}
	}}
bool operator>(tPelicula izq, tPelicula der ){
	bool mayorQe=true;
	if(izq.puntuacion < der.puntuacion){
		mayorQe=false;
	}
	else if (izq.puntuacion == der.puntuacion){
		if(izq.titulo > der.titulo){
			mayorQe=false;
		}
	}
	return mayorQe;
}

void nuevoVoto(tListaPeliculas &listaPelis, bool &ok){
	string titulo;
	ok=false;
	int pos, puntuacion, media;
	cout << "Introduce el titulo de la pelicula que quieres votar: ";
	getline(cin, titulo);
	if(buscarPelicula(listaPelis,titulo, pos)){
		ok=true;
		cout << "Nueva puntuacion : " ;
		cin >> puntuacion;
		media= (listaPelis.peliculas[pos].puntuacion + puntuacion)/2;
		listaPelis.peliculas[pos].puntuacion=media;
	}
}

void mostrarPeliculas(const tListaPeliculas &listaPelis){
	for(int i=0; i< listaPelis.cont;i++){
		cout << "------------------------------------"<< endl;
		cout << "Titulo : " << listaPelis.peliculas[i].titulo << endl;
		cout << "Año : " << listaPelis.peliculas[i].anio << endl;
		cout << "Puntuacion : " << listaPelis.peliculas[i].puntuacion << endl;
	}
}

void inicializarLista(tListaPeliculas &lista){
	lista.cont=0;
}

bool cargarPeliculas(tListaPeliculas &listaPelis){
	ifstream archivo;
	string titulo;
	tPelicula peli;
	char aux;
	int pos=0;
	bool ok=false;
	archivo.open(ARCHIVO);
	if(archivo.is_open()){
		inicializarLista(listaPelis);
		ok=true;
		getline(archivo,titulo);
		while(titulo!=CENTINELA && listaPelis.cont < N){
			archivo >> peli.anio >> peli.puntuacion;
			peli.titulo=titulo;
			archivo.get(aux);
			if(peliValida(listaPelis, peli)){
				insertarEnLista(listaPelis, peli, listaPelis.cont);
			}
			getline(archivo,titulo);
		}
	}
	return ok;
}

bool peliValida(const tListaPeliculas &listaPelis, tPelicula pelicula){
	int pos=0;
	return (!buscarPelicula(listaPelis, pelicula.titulo, pos) && pelicula.puntuacion>=0 && pelicula.puntuacion<=10);
}

bool buscarPelicula(const tListaPeliculas &listaPelis, string titulo, int &pos){
	bool encontrado=false;
	int ini=0, fin=listaPelis.cont-1, mitad;
	while(ini<=fin && !encontrado){
		mitad=(ini+fin)/2;
		if(titulo==listaPelis.peliculas[mitad].titulo){
			encontrado=true;
			pos=mitad;
		}
		else if(titulo < listaPelis.peliculas[mitad].titulo){
			fin=mitad-1;
		}
		else{
			ini=mitad+1;
		}
	}
	if(!encontrado){
		pos=ini;
	}
	return encontrado;
}

void abrirHueco(tListaPeliculas &listaPelis, int pos){
	for(int i=listaPelis.cont; i > pos; i--){
		listaPelis.peliculas[i]=listaPelis.peliculas[i-1];
	}
}

void insertarEnLista(tListaPeliculas &listaPelis, tPelicula pelicula,int pos){
	listaPelis.peliculas[pos]=pelicula;
	listaPelis.cont++;
}

void insertarPeliculas(tListaPeliculas &listaPelis , tPelicula pelicula,bool &ok){
	int pos;
	if(listaPelis.cont==N){
		ok=false;
	}
	else{
		ok=true;
		buscarPelicula(listaPelis, pelicula.titulo, pos);
		abrirHueco(listaPelis,pos);
		insertarEnLista(listaPelis, pelicula, pos);
	}
}

void importarEstrenos(tListaPeliculas &listaPelis, bool &ok){
	ifstream archivo;
	string titulo;
	tPelicula peli;
	char aux;
	int pos;
	peli.puntuacion=0;
	ok=false;
	archivo.open("estrenos.txt");
	if(archivo.is_open()){
		getline(archivo,titulo);
		ok=true;
		while (titulo!=CENTINELA && ok){
			archivo >> peli.anio;
			peli.titulo=titulo;
			insertarPeliculas(listaPelis, peli,ok);
			archivo.get(aux);
			getline(archivo,titulo);
		}
		ok=true;
	}
}
