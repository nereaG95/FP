#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int NUM_PLAYERS=10;
typedef enum {error,BCN,RMA,ATM,VIL, ATB} tEquipo;
typedef struct{
	string nombre;
	tEquipo equipo;
	int partidos;
	int minutos;
	int goles;
}tJugador;

typedef tJugador tListaJugadores[NUM_PLAYERS];
string enumToString (tEquipo equipo);
tEquipo stringToEnum(string equipo);
void cargarArchivo(bool &ok , tListaJugadores &lista);
bool fallo (const tJugador &lista);
void mostrarJugador(tJugador jugador);
void filtrar(const tListaJugadores &lista, string codigo);
int menu ();
void actualizarJugador (tListaJugadores &lista , string nombre, int minutos, int goles);
int buscarJugador (const tListaJugadores &lista, string nombre);
void consultarMaximoGoleador(const tListaJugadores &lista);
int maxGoles(const tListaJugadores &lista);

int main(){
	bool ok;
	int op, minutos, goles;
	tListaJugadores lista;
	string codigo, nombre;
	cargarArchivo(ok,lista);
	if (ok){
		do{
			op=menu();
			switch (op)
			{
			case 1: 
				cout <<"Codigo del equipo que deseas filtrar : ";
				cin >> codigo;
				filtrar(lista, codigo);
				break;
			case 2:
				cout << "ACTUALIZACION DE JUGADORES " << endl;
				cout << "Introduce el nombre del jugador ";
				cin >> nombre;
				cout << "Introduce los minutos que ha jugado : ";
				cin >> minutos;
				cout << "Introduce los goles que ha marcado : ";
				cin >> goles;
				actualizarJugador(lista,nombre,minutos,goles);
				break;
			case 3:
				cout << "CONSULTA DEL MAXIMO GOLEADOR " << endl;
				consultarMaximoGoleador(lista);
				break;
			default:
				break;
			}
		}while (op!=0);
	}
	else{
		cout << "Error al cargar el archvio " << endl;
	}
	system("pause");
	return 0;
}

int maxGoles(const tListaJugadores &lista){
	int goles=0;
	for (int i=0; i< NUM_PLAYERS; i++){
		if (lista[i].goles>goles){
			goles=lista[i].goles;
		}
	}
	return goles;
}


void consultarMaximoGoleador(const tListaJugadores &lista){
	int maximoGoles = maxGoles(lista);
	int pos;
	cout << "Maximo/a goleador/es : " << endl;
	for (int i=0; i<NUM_PLAYERS; i++){
		if (maximoGoles==lista[i].goles){
			mostrarJugador(lista[i]);
		}
	}
}

int buscarJugador (const tListaJugadores &lista, string nombre){
	bool encontrado=false;
	int contador =0, pos;
	while (contador < NUM_PLAYERS && !encontrado){
		if (nombre== lista[contador].nombre){
			encontrado=true;
			pos=contador;
		}
		else {
			contador++;
		}
	}
	if (!encontrado){
		pos=-1;
	}
	return pos;
}

void actualizarJugador (tListaJugadores &lista , string nombre, int minutos, int goles){
	int pos;
	pos =buscarJugador(lista, nombre);
	if (pos > 0){
		lista[pos].minutos=lista[pos].minutos+minutos;
		lista[pos].goles=lista[pos].goles+goles;
		lista[pos].partidos++;
		mostrarJugador(lista[pos]);
	}
	else{
		cout << "No existe el jugador "  << endl;
	}
	
}

int menu(){
	int op;
	cout << " 1.- Filtrar lista " << endl;
	cout << " 2.- Actualizar jugador " << endl;
	cout << " 3.-Consultar maximo goleador " << endl;
	cout << " 0.- Salir " << endl;
	cout << "Opcion : " ;
	cin >> op;
	while (op < 0 || op >3){
		cout << "Error , nueva opcion : " ;
		cin >> op;
	}
	return op;
}

void mostrarJugador(tJugador jugador){
	cout << "Nombre : "  << jugador.nombre << endl;
	cout << "Equipo : " << enumToString(jugador.equipo) << endl;
	cout << "Partidos : " << jugador.partidos << endl;
	cout << "Minutos : " << jugador.minutos << endl;
	cout << "Goles : " << jugador.goles << endl;
}

void filtrar(const tListaJugadores &lista, string codigo){
	tEquipo siglas;
	if (codigo=="TODOS"){
		for (int i=0; i< NUM_PLAYERS;i++){
			mostrarJugador(lista[i]);
		}
	}
	else{
		siglas=stringToEnum(codigo);
		if (siglas==error){
			cout << "Ese equipo no existe en la lista " << endl;
		}
		else{ //existe el equipo
			for (int i=0; i< NUM_PLAYERS;i++){
				if (siglas==lista[i].equipo){
					mostrarJugador(lista[i]);
				}
			}
		}
	}
}

bool fallo (const tJugador &lista){
	bool fallo =false;
	if ((lista.equipo==error) || (lista.goles < 0 || lista.minutos<0 || lista.partidos <0) || (lista.minutos > lista.partidos*90)
		|| (lista.partidos==0 && lista.goles>0) || (lista.partidos==0 && lista.minutos>0)){
		fallo =true;
	}
	return fallo;
}

void cargarArchivo(bool &ok , tListaJugadores &lista){
	ifstream archivo;
	string jugador, equipo;
	int contador=0;
	bool fallos=false;
	archivo.open("players.txt");
	if (archivo.is_open()){
		archivo >> jugador;
		while (jugador!="XXX" && contador < NUM_PLAYERS && !fallos){
			lista[contador].nombre=jugador;
			archivo >> equipo;
			lista[contador].equipo=stringToEnum(equipo);
			archivo >> lista[contador].partidos >> lista[contador].minutos >> lista[contador].goles;
			if (fallo(lista[contador])){
				fallos=true;
			}
			else {
				contador++;
				archivo >> jugador;
			}
		}
		ok=true;
		archivo.close();

	}
	else{
		ok=false;
	}
	if (fallos){
		ok=false;
	}
}

tEquipo stringToEnum(string equipo){
	tEquipo siglas;
	if (equipo=="RMA"){
		siglas=RMA;
	}
	else if (equipo=="BCN"){
		siglas=BCN;
	}
	else if (equipo=="ATM"){
		siglas=ATM;
	}
	else if (equipo=="VIL"){
		siglas=VIL;
	}
	else if (equipo=="ATB"){
		siglas=ATB;
	}
	else {
		siglas=error;
	}
	return siglas;
}
string enumToString (tEquipo equipo){
	string equip;
	if (equipo==BCN){
		equip="BCN";
	}
	else if (equipo==RMA){
		equip="RMA";
	}
	else if(equipo==ATM){
		equip="ATM";
	}
	else if (equipo==VIL){
		equip="VIL";
	}
	else if(equipo==ATB){
		equip="ATB";
	}
	else{
		equip="NO EXISTE";
	}
	return equip;
}

