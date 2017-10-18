/*Practica 3 realizada por Nerea Gomez Dominguez, hecha toda la parte opcional descrita en el enunciado
de la practica, es decir, la version 4, que consistía en guardar puntuaciones de los 10 mejores ganadores y partidas cuando se deseara*/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <Windows.h>
#include <cmath>
#include<conio.h.>
using namespace std;

const int DIM=4; //Dimension
const int FICHA_LIBRE=1;
const int FICHA_INICIAL2=2;
const int FICHA_INICIAL4=4;
const int FIN=2048;
const int COLUMNAS=6, MAXRECORD = 10;
const string CENTINELA = "???", ARCHIVORECORD= "records.txt";
typedef int tTablero[DIM][DIM]; //Matriz 4x4
typedef enum{ arriba,abajo,derecha,izquierda,salir} tAccion;


typedef struct {
	string nombre;
	int puntos;
}tJugador;

typedef tJugador tRecord[10];
 
typedef struct {
	tRecord record;
	int cont;
}tLista;



//Prototipos
//Version 1

/*
Procedimiento que le pasan por parametro un entero y segun el entero que le pasen pinta el fondo
E:	-color(int) es el entero que señala el color a pintar
*/
void colorFondo(int color);

/*
Procedimiento que inicializa todo el array tablero a 1, excepto dos casillas al azar que inicializa con dos 2 o con un 2 y un 4,
aunque esta ultima es menos probable que suceda.
S:	-tablero(tTablero) array que entra sin inicializar y sale inicializado
*/
void inicializar(tTablero tablero);

/*Procedimiento que pinta una cuadricula del tamaño del array bidimensional, y en las casillas se muestra los valores
del array recorriedolo junto con el color dependiendo del valor que tenga el array en esa posicion
E:	-tablero(tTablero) el tablero entra para mostrarse por pantalla
	-puntos(int) entra para mostrarse los puntos obtenidos en ese movimiento
	-totalPuntos(int) entra para mostrar por pantalla los puntos obtenidos en esa partida */
void visualiza(const tTablero tablero, int puntos, int totalPuntos);

/*Funcion que devuelve la potencia de 2 que da como resultado num, por las propiedades de los logaritmos sabemos que si num= 2^x
y queremos hallar x (la potencia que devuelve) aplicando log10 a ambos lados de la ecuacion y sabiendo que el logaritmo de una 
potencia es igual al producto del exponente por el logaritmo de la base, despejando obtenemos x de la siguiente forma:
log 10 num = log 10 2^x -> log 10 num = x * (log 10 2) -> x= (log 10 num)/log 10(2);
  E: num (numero de la ficha correspondiente)*/
int log2(int num);
/*Funcion que realiza la carga del tablero a traves de un archivo.txt y devuelve el tablero cargado y un booleano que indica si se ha
realizado la carga correctamente
E/S:  -puntos: indican los puntos que se llevan hasta el momento en la partida
	  -Ok: informa de si se ha realiza correctamente la carga, o ha abido errores 
	  -tablero: sale conteniendo las fichas como indica el archivo de texto*/
void carga(tTablero tablero, int &puntos, bool &ok);

/*
Procedimiento que dependiendo de lo que le pasen por parametos muestra por pantallas una interseccion u otra, pinta tambien las lineas,
las esquinas superiores, las interesecciones que separan las filas y el esquinas inferiores.
E:	-lineaEmpieza: pinta las primeras intersecciones 
	-lineaMedio: pinta las intersecciones intermedias
	-lineaFinal: pinta las intersecciones finales

*/
void pintarBordes(int lineaEmpieza, int lineaMedio, int lineaFinal);

/*
Procedimiento que pinta la lineas que no muestran por pantalla el valor del array, pero se le pasa por parametro
para pintar el fondo del color del valor que tiene el array en esa posicion
y que el cuadro donde este el valor se pinte totalmente con el color que corresponda.
E:	-tablero(tTablero) pasa el tablero para saber de que color pintar el fondo
	-fila(int) señala la fila en la que se encuentra
*/
void lineaEnBlanco(const tTablero tablero, int fila);

/*
Procedimiento que al igual que el anterior pinta el color de fondo dependiendo del valor que tenga el array en esa posicion,
pero que tambien muestra por pantalla el valor del array
E:	-tablero(tTablero) pasa el tablero para dependiendo del valor pintar el fondo y ademas mostrar el valor por pantalla
	-fila(int) señala la fila en que se encuentra
*/
void lineaOcupada(const tTablero tablero, int fila);


//Version 2

/*Función que devuelve el valor de la direccion que se ha leido desde el teclado,
si se lee un valor distinto de las teclas especiales se seguira leyendo la accion
hasta que sea uno correcto. Si dir es 27, es la tecla Esc, ↑72,↓80,→77,←75*/
tAccion leeAccion();

/*Procedimiento que mueve las fichas en el array en una direccion u otra dependiendo de la accion que se le pase por parametro
E/S:	-tablero(tTablero) mueve el tablero que si se puede mover con la accion que se le a pasado por parametro, sino, el tablero no se modifica
E:		-accion(tAccion) señala la direccion en que se quiere mover el tablero */
void mueveFichas(tTablero tablero, tAccion accion);

/*Procedimiento que segun la accion que le pasan por parametro, devuelve un incremento de x,y y por donde empezar a incrementar para mover ficha
E:	-accion(tAccion) segun la accion que le pasen devuelve un valor inicial y el incremento distinto 
	-i(int) señala la vuelta en la que se encuentra el recorrido del array
S:  -xIni: sale con el valor que tiene que valer la x para mover ficha
	-yIni: sale con el valor que tiene que valer la y para mover ficha
	-incrX: sale con el valor con que hay que incrementar x para mover ficha
	-incrY: sale con el valor con que hay que incrementar y para mover ficha*/
void obtenerParametros(tAccion accion, int i, int &xIni, int &yIni, int &incrX, int &incrY);

/*Subprograma que devuelve  un booleao indicando si el parametro que pasamos es valido ( es decir se encuentra entre 0 y DIM ) o no lo es
 E: parametro, será el parametro que queremos comprobar que sea valido
 S: un booleano que devuelve true si el parametro se encuentra entre 0 y DIM y false en caso contrario  */
bool esValida(int parametro);

//Version 3
/*Funcion que devuelve el numero mayor de la ficha que hay en el tablero, para ello recorremos todo el tablero y comprobamos si la ficha 
actual es mayor que la fichaMayor que tenemos guardada, si es asi actualizamos la fichaMayor
	E:tablero, es el tablero del juego (la matriz DIMxDIM) que nos indica en que posiciones estan las fichas y sus valores*/
int mayor(const tTablero tablero);

/*Funcion que informa del estado de la partida , nos indica si el tablero esta lleno y si hay movimientos posibles. Primero buscamos si 
el tablero esta lleno o hay movimientos posibles en horizontal, si el tablero se encuentra lleno y no hay movimientos posibles buscamos 
si hay movimientos posibles en vertical (2 fichas del mismo valor seguidas).
	E: tablero, es el tablero del juego (la matriz DIMxDIM) que nos indica en que posiciones estan las fichas y sus valores
	S: -LLeno, indica si el tablero está lleno (devuelve true) y si no lo esta (devuelve false)
	   -movPosibles, indica si hay movimientos posibles (devuelve true),es decir si hay dos fichas consecutivas horizontalmente o verticalmente con el
	   mismo valor en el tablero, si no hay movPosibles=false */
void getEstadoPartida(const tTablero tablero, bool &lleno, bool &movPosibles);

/*Procedimiento que depende de la accion se obtienen unos parametros para recorrer el array y 
si al recorrerlo se ven dos posiciones del array que son iguales y estan en el sentido en que se incrementa,entonces se combinan.
E/S:-tablero(tTablero) el tablero si se puede combinar en el sentido de la accion sale combinado, sino sale igual que entro
E:	-accion(tAccion) depende de la accion se intenta combinar en una direccion u en otra
S:	-puntos(int) toma el valor de los puntos que se han conseguido en esa jugada	*/
void combinaFichas(tTablero tablero, tAccion accion, int &puntos);

/*Funcion que crea una nueva ficha aleatoriamente en el tablero, con el 95% de posibilidades de que sea un 2 
y el 5% de que sea un 4, se colocora en una posicion aleatoria, la cual tiene que estar libre 
	E/S: tablero, es el tablero del juego (matriz DIMxDIM) y sale modificado con una nueva ficha que se coloca aleatoriamente en una 
	casilla de la matriz que debe estar libre.*/
void nuevaFicha(tTablero tablero);

/*Subprograma que busca si hay movimientos posibles verticalmente. Hacemos una busqueda en el tablero de manera que si hay dos fichas 
verticales consecutivamente con el mismo valor habra movPosibles y la busqueda parara.
	E: tablero, es el tablero del juego (la matriz DIMxDIM) que nos indica en que posiciones estan las fichas y sus valores
	S: -movPosibles, indica si hay movimientos posibles (devuelve true),es decir si hay dos fichas consecutivas verticalmente con el
	   mismo valor en el tablero, si no movPosibles=false*/
void busquedaMovimientosVertical(const tTablero tablero, bool &movPosibles);

/*Subprograma que realiza una busqueda en un array bidimensional para ver si el tablero esta lleno (no hay fichas libres) y si esta lleno
miramos si hay movimientos posibles horizontalmente (2 fichas consecutivascon el mismo valor) y si el tablero esta lleno.
La busqueda para cuando hayamos encontrado una posicion libre o movPosibles.
	E: tablero, es el tablero del juego (la matriz DIMxDIM) que nos indica en que posiciones estan las fichas y sus valores
	S: -LLeno, indica si el tablero está lleno (devuelve true) y si no lo esta (devuelve false)
	   -movPosibles, indica si hay movimientos posibles (devuelve true),es decir si hay dos fichas consecutivas horizontalmente con el
	   mismo valor en el tablero, si no movPosibles=false*/
void busquedaMovimientosHorizontal(const tTablero tablero,bool &lleno, bool &movPosibles);


//Version 4

/*Subprograma que guarda un nuevo record si es de los 10 primeros e informa si se ha guardado o no. Primero se lee el archivo records.txt,
preguntamos el nombre al usuario y buscamos la posicion en la que debemos insertarlo, si es menor que MAXRECORD, lo insertamos y aumentamos
el contador si este es menor que MAXRECORDS. Por ultimo, reescribimos el archivo con las nuevas puntuaciones
	E: puntosAcumulados, nos indica los puntos que ha conseguido el jugador en la partida
	S: hecho, informa de si se ha añadido a lista al jugador con su puntuacion, devolvera false cuando no se añada al jugador porque la lista
	esta llena y la puntuacion es mas pequeña que la ultima.*/
void nuevoRecord(int puntos, bool &hecho);

/*Funcion que muestra los Records (nombre y puntos del jugador) del archivo de texto records.txt si este se ha abierto correctamente. Primero
leemos el archivo e insertamos los datos en la lista y si esto se ha hecho correctamente mostramos la lista por pantalla */
void muestraRecords();

/*Funcion que guarda una partida en un archivo de texto, para ello guarda el tablero y los puntos acumulado
	E: - tablero : es el tablero del juego (la matriz DIMxDIM) que nos indica en que posiciones estan las fichas y sus valores
	   - puntos: son los puntos acumulados en la partida */
void guarda(const tTablero tablero, int puntos);

/*Funcion que busca en una lista mediante una busqueda binaria la posicion que debe de ocupar un nuevo record,
buscando primero por puntuaciones y si coindide, por el nombre, devuelve la posicion en la que deberia de estar el nuevo record.
E/S:-lista(tLista) array donde se guardan los record y en donde se va a buscar la posicion que debe de ocupar el nuevo record
E:	-nombre(string) nombre que se va a comparar si los puntos coinciden
	- puntos(int) puntos con los cuales se hace la busqueda */
int buscar(const tLista &lista, string nombre, int puntos);

/*Procedimiento que carga un archivo en un array, que contiene los record que hay hasta ese momento
E/S:	-lista(tLista) lista en donde se carga el archivo con los record
S:		-ok(bool) toma el valor true si se a cargado con exitoy false en caso contrario*/
void leerArchivoRecord(tLista &lista, bool &ok);

/*Procedimiento que guarda el array que contiene los record en un archivo
E: lista(tLista) entra la lista en la que estan los record y que se van a grabar en el archivo
S: ok(bool) devuelve true si se a guardado el array con exito en el archivo y false en caso contrario*/
void escribirArchivoRecord(const tLista &lista, bool &ok);

/*Subprograma que guardar las puntuaciones del usuario si este dice que si, si la lista de puntuaciones esta llena y la nueva puntuacion es menor
que la ultima se informara al usuario del error
	E: puntosAcumulados, pasamos los puntosAcumulados para crear el nuevoRecord*/
void opcionGuardarPuntuaciones(int puntosAcumulados);

/*Subprograma para mostrar las puntuaciones, el cualpregunta al usuario si quiere ver los records registrados, en caso de que indique
que si se mostraran a traves de la funcion muestraRecords*/
void opcionMostrarPuntuaciones();

/*Subprograma que muestra el mensaje correspondiente dependiendo si se ha ganado, se ha perdido o se ha abandonado
	E: accion, pasamos la accion porque si es igual a salir significa que hemos abandonado la partida y preguntaremos si queremos guardarla
	  -tablero,puntosAcumulado : pasamos el tablero y los puntosAcumulados para guardarlo en caso de que el jugador quiera guardar la partida
	  cuando abandone
	  -fichaMayor, comprobamos si la fichaMayor es 2048 para ver si se ha ganado el juego*/
void mostrarMensajesFinDeJuego(const tTablero tablero,int fichaMayor, int puntosAcumulados, tAccion accion);

/*Pocedimiento que pregunta al usuario si quiere o no cargar una partida de un archivo, en caso de que no quiera cargar se inicializa el tablero
S:  -tablero (tTablero) el tablero sale inicializado o cargado depende de la opcion que elija el usuario*/
void cargarInicializar(tTablero &tablero);

/*Procedimiento que en caso de que el usuario pulse esc, pregunta si de verdad quiere salir, si pulsa 's' sale, si pulsa 'n' vuelve a mostrar el tablero y a pedir una accion
E:	-tablero (tTablero): en caso de que no se quiera salir se llama a visualizar para mostrar el tablero
	-puntosAcumilado (int): en caso de que no se quiera salir se llama a visualizar para mostrar los puntos acumulados
	-puntos (int): en caso de que no se quiera salir se llama a visualizar para mostrar los puntos
S:	-accion(tAccion) en caso de que se elija la opcion de que no se quiere salir pide al usuario otra accion y sale 
	-Ok (bool) devuelve false si no se quiere salir del juego y true en caso contrario*/
void confirmarSalir(const tTablero tablero, tAccion &accion, int puntosAcumulados, int puntos, bool &ok);



int main(){
	srand(time(NULL));
	tTablero tablero;
	tAccion accion;
	tLista lista;
	int puntos=0, puntosAcumulados=0, fichaMayor = 0;
	bool lleno=false, movPosibles=true, ok=false;

	cargarInicializar(tablero);
	visualiza(tablero,puntos, puntosAcumulados); //Mostramos el tablero

	accion = leeAccion(); //Leemos la direccion
	while(accion == salir && !ok){
		confirmarSalir(tablero, accion, puntosAcumulados, puntos, ok);
	}
	while(accion!=salir &&  fichaMayor!=FIN  && movPosibles){
		mueveFichas(tablero, accion); //Inclinamos el tablero
		combinaFichas(tablero, accion, puntos); //Combinamos las fichas
		mueveFichas(tablero, accion);  //Volvemos a inclinar
		puntosAcumulados+=puntos; //Actualizamos los Puntos acumulados
		getEstadoPartida(tablero, lleno, movPosibles); //Comprobamos si el tablero esta lleno o no hay mov posibles

		if(!lleno) //Si no esta lleno incluimos la nueva ficha
			nuevaFicha(tablero);
		visualiza(tablero,puntos, puntosAcumulados); //Mostramos el tablero

		fichaMayor=mayor(tablero); //Vemos cual es la ficha mayor
		if(fichaMayor!=FIN){
			accion = leeAccion(); //Leemos la direccion
			while(accion == salir && !ok){ //Mientras la accion sea salir , confirmamos la salida
				confirmarSalir(tablero, accion, puntosAcumulados, puntos, ok);
			}
		}
	}
	
	mostrarMensajesFinDeJuego(tablero, fichaMayor, puntosAcumulados, accion); //Muestra el mensaje correspondiente
	opcionMostrarPuntuaciones(); //Muestra las puntuaciones al usuario si lo desea 

	cout << endl << "Hasta la proxima!!" << endl;

	system("pause");
	return 0;
}

void confirmarSalir(const tTablero tablero, tAccion &accion, int puntosAcumulados, int puntos, bool &ok) {
	char opcion;
	ok=true;
	cout << "Seguro que quiere salir(S/N): ";
	cin >> opcion;
	opcion = toupper(opcion);
	if(opcion == 'N'){
		ok=false;
		visualiza(tablero,puntos, puntosAcumulados);
		accion = leeAccion();
	}
}

void cargarInicializar(tTablero &tablero) {
	char opcion;
	bool ok = false;
	int puntosAcumulados = 0;

	cout << "Quieres cargar una partida [S/N] : ";
	cin >> opcion;
	opcion=toupper(opcion);
	if(opcion=='S'){// Si se ha marcado S , Cargamos el tablero
		carga(tablero,puntosAcumulados, ok); 
	}
	if(!ok){ //Si no se puede cargar o marcamos no lo inicializamos
		inicializar(tablero); 
	}
}

void mostrarMensajesFinDeJuego(const tTablero tablero,int fichaMayor, int puntosAcumulados, tAccion accion){
	char opcion;
	if (fichaMayor==FIN){
		cout << endl <<  "FELICIDADES HAS GANADO AL 2048 :)! " << endl;
		opcionGuardarPuntuaciones(puntosAcumulados); //Pide al usuario si quiere guardar su puntuacion
	}
	else if (accion==salir){
		cout << "Has abanadonado la partida..." << endl;
		cout << "Desea guardar la partida(S/N): ";
		cin >> opcion;
		opcion = toupper(opcion);
		if(opcion == 'S'){
			guarda(tablero, puntosAcumulados);
		}
	}
	else{
		cout << "Lo siento no quedan movimientos!! :( " << endl;
	}
}

void opcionMostrarPuntuaciones(){
	char opcion;
	cout << "Desea ver los records registrados (S/N): ";
	cin >> opcion;
	opcion = toupper(opcion);
	if(opcion == 'S'){
		muestraRecords();
	}
}

void opcionGuardarPuntuaciones(int puntosAcumulados){
	char opcion;
	bool ok=false;
	cout << "Desea guardar su puntuacion(S/N): ";
	cin >> opcion;
	opcion = toupper(opcion);
	if(opcion == 'S'){
		nuevoRecord(puntosAcumulados,ok);
		if(!ok){
			cout << "No se ha podido añadir su record, la puntuacion es muy baja!" << endl;
		}
	}
}

void colorFondo(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);  
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

void carga(tTablero tablero, int &puntos, bool &ok){
	ifstream archivo;
	string nomArch;
	int dim;
	cout <<"Introduce el nombre de archivo a cargar :"; //Pedimos el nombre del fichero
	cin >> nomArch;
	archivo.open(nomArch);
	if(archivo.is_open()){
		archivo >> dim; //Leemos la dimension
		if (dim ==DIM){ //Si coinciden las dimensiones cargamos el tablero
			for(int fila=0; fila < DIM; fila++){
				for(int columna=0; columna < DIM; columna++){
					archivo >> tablero[fila][columna];
				}
			}
			archivo >> puntos; //Leemos los puntos acumulados
			ok=true;
		}
		archivo.close();
	}
}

int log2(int num){
	return log10(num)/log10(FICHA_INICIAL2);
}

void inicializar(tTablero tablero) {
	int filAleatoria1, colAleatoria1, filAleatoria2, colAleatoria2;
	bool cuatroColocado = false;
	for(int fil = 0; fil < DIM; fil++) {
		for(int col = 0; col < DIM; col++) {
			tablero[fil][col] = 1; // inicializamos a 1 todas las posiciones del array
		}
	}

	filAleatoria1 = rand() % DIM;
	colAleatoria1 = rand() % DIM;// elegimos posicion aleatoria del array
	if(((rand() % 100) + 1) <= 95){
		tablero[filAleatoria1][colAleatoria1] = FICHA_INICIAL2;
	}
	else {
		tablero[filAleatoria1][colAleatoria1] = FICHA_INICIAL4;
		cuatroColocado = true;
	}

	//LA FILA Y COLUMNA DE LA FICHA 1 DEBEN SER DIFERENTES A LA DE LA 2 
	do {
		filAleatoria2 = rand() % DIM;
		colAleatoria2 = rand() % DIM;
	} while (filAleatoria1==filAleatoria2  && colAleatoria1==colAleatoria2);

	if(cuatroColocado)
		tablero[filAleatoria2][colAleatoria2] = FICHA_INICIAL2;
	else {
		if(((rand() % 100) + 1) <= 95){
			tablero[filAleatoria2][colAleatoria2] = FICHA_INICIAL2;
		}
		else{
			tablero[filAleatoria2][colAleatoria2] = FICHA_INICIAL4;
		}
	}

}

void visualiza(const tTablero tablero, int puntos, int totalPuntos){
	system("cls");
	cout << endl << "Puntuacion parcial: " << setw(6) << left << puntos << "Puntuacion total: " << totalPuntos << endl;
	pintarBordes(218,194,191); //Pintamos el borde superior
	for(int i=0; i < DIM; i++){
		lineaEnBlanco(tablero, i); //Dibujamos la 1 linea
		lineaOcupada(tablero,i); //Dibujamos la 2 linea
		lineaEnBlanco(tablero,i); //Dibujamos la 3 linea
		if( i< DIM-1){
			pintarBordes(195,197,180); //Dibujamos el borde intermedio, excepto en la ultima vuelta
		}
	}
	pintarBordes(192,193,217); //Pintamos el borde inferior
	cout << endl << " Usa las teclas de flecha o ESC " << endl;
}

void lineaEnBlanco(const tTablero tablero, int fila){
	cout << "   ";
	cout << char(179);
	for(int i=0; i< DIM; i++){
		for(int j=0; j< 6; j++){
			colorFondo(log2(tablero[fila][i]));
			cout << " ";
		}
		colorFondo(0);
		cout << char(179);
	}
	cout << endl;
}

void lineaOcupada(const tTablero tablero, int fila){
	colorFondo(0);
	cout << "   ";
	for(int i=0; i< DIM; i++){
		cout << char(179);
		colorFondo(log2(tablero[fila][i]));
		cout << " " << setw(4);
		if (tablero[fila][i]>1){
			cout << tablero[fila][i];
		}
		else {
			cout <<" ";
		}
		cout << " ";
		colorFondo(0);
	}
	cout << char(179);
	cout << endl;
}

void pintarBordes(int lineaEmpieza, int lineaMedio, int lineaFinal){
	colorFondo(0);
	cout <<"   ";
	cout<< char(lineaEmpieza); //Esquina superior izquierda
	for(int j=0; j<DIM-1; j++){ 
		for(int y=0; y<COLUMNAS; y++){
			cout<<char(196);
		}
		cout<<char(lineaMedio);
	}
	for(int i=0; i<COLUMNAS; i++){ //Ultima esquina
		cout<<char(196);
	}
	cout<<char(lineaFinal); //Esquina superior derecha
	cout << endl;
}

tAccion leeAccion() {
	cin.sync();
	bool ok = false;
	const int Esp = 0xe0, Esc = 27;
	tAccion accion;
	int dir; // dir: tipo int
	do {
		dir =_getch();
		if (dir == Esp) {
			dir = _getch();
			if(dir == 72) 
				accion = arriba;
			else if(dir == 80)
				accion=abajo;
			else if (dir == 77)
				accion=derecha;
			else if(dir == 75)
				accion=izquierda;
			ok = true;
		}
		else if(dir == Esc) {
			accion = salir;
			ok = true;
		}
	}while(!ok);
	return accion;
}

bool esValida(int parametro){
	return (parametro <DIM) && (parametro>=0);
}

void mueveFichas(tTablero tablero, tAccion accion) {
	int xIni, yIni, incrX, incrY, aux;
	for(int i = 0; i < DIM; i++) {
		obtenerParametros(accion, i, xIni, yIni, incrX, incrY);
		int x = xIni, y = yIni; //Inicializamos la fila y la columna
		while(esValida(x) && esValida(y)) {
			if(tablero[x][y] != 1){
				aux = tablero[x][y]; //Guardamos la ficha en una variable auxiliar 
				tablero[x][y] = tablero[xIni][yIni];
				tablero[xIni][yIni] = aux; 
				 xIni+=incrX;
				 yIni+=incrY;
			}
			x += incrX;
			y += incrY;
		}
	}
}

void obtenerParametros(tAccion accion, int i, int &xIni, int &yIni, int &incrX, int &incrY) {
	if(accion == arriba){
		xIni = 0;
		yIni = i;
		incrX = 1;
		incrY = 0;
	}
	else if(accion == abajo) {
		xIni = DIM - 1;
		yIni = i;
		incrX = -1;
		incrY = 0;
	}
	else if(accion == derecha){
		xIni = i;
		yIni = DIM - 1;
		incrX = 0;
		incrY = -1;
	}
	else if(accion == izquierda) {
		xIni = i;
		yIni = 0;
		incrX = 0;
		incrY = 1;
	}
}

int mayor(const tTablero tablero){
	int numMayor= FICHA_LIBRE; 
	for(int fila = 0; fila < DIM; fila++) {
		for(int col = 0; col < DIM; col++){
			if(tablero[fila][col] > numMayor)
				numMayor = tablero[fila][col];
		}
	}
	return numMayor;
}

void nuevaFicha(tTablero tablero){
	int filAleatoria, colAleatoria;
	do {
		filAleatoria = rand() % DIM;
		colAleatoria = rand() % DIM;
	} while (tablero[filAleatoria][colAleatoria]!=FICHA_LIBRE);

	if(((rand() % 100) + 1) <= 95){
		tablero[filAleatoria][colAleatoria] = FICHA_INICIAL2;
	}
	else {
		tablero[filAleatoria][colAleatoria] = FICHA_INICIAL4;
	}
}

void combinaFichas(tTablero tablero, tAccion accion, int &puntos) {
	int xIni, yIni, incrX, incrY, x, y;
	puntos=0;
	for(int i = 0; i < DIM; i++) {
		obtenerParametros(accion, i, xIni, yIni, incrX, incrY);
		x = xIni, y = yIni;
		while( esValida(x) && esValida(y)) { 
			if(tablero[x][y] != FICHA_LIBRE && (xIni != x || yIni != y)){
				if(tablero[x][y] != tablero[xIni][yIni])
					xIni = x, yIni = y;
				else { 
					puntos=puntos+tablero[xIni][yIni] + tablero[x][y];
					tablero[xIni][yIni] = tablero[xIni][yIni] + tablero[x][y];
					tablero[x][y] = FICHA_LIBRE;
					xIni+=incrX;
					yIni+=incrY;
				}
			}
			x += incrX;
			y += incrY;
		}
	}

}

void getEstadoPartida(const tTablero tablero, bool &lleno, bool &movPosibles) {
	busquedaMovimientosHorizontal(tablero,lleno,movPosibles);
	if(lleno && !movPosibles){
		busquedaMovimientosVertical(tablero,movPosibles);
	}
}

void busquedaMovimientosHorizontal(const tTablero tablero,bool &lleno, bool &movPosibles){
	lleno=true;
	movPosibles=false;
	int fichaUltima=-1, columnas=0, filas=0;
	while (filas < DIM && !movPosibles && lleno){ //Buscamos horizontalmente aumentando primero las filas y despues las columnas
		while (columnas < DIM && !movPosibles && lleno ){
			if(tablero[filas][columnas]==FICHA_LIBRE){ //Comprobamos que el tablero no este lleno
				lleno=false;
				movPosibles=true;
			}
			if(lleno){
				if(fichaUltima==tablero[filas][columnas]){
					movPosibles=true;
				}
				else{
					fichaUltima=tablero[filas][columnas]; //Si es distinto de 1 le ponemos su valor 
				}
				columnas++;
			}
		}
		if(!movPosibles && lleno){
			fichaUltima=-1;
			columnas=0;
			filas++;
		}
	}
}

void busquedaMovimientosVertical(const tTablero tablero, bool &movPosibles){
	int fichaUltima=-1, columnas=0, filas=0;
	while (columnas < DIM && !movPosibles){ //Buscamos horizontalmente aumentando primero las filas y despues las columnas
		while (filas < DIM && !movPosibles){
			if(fichaUltima==tablero[filas][columnas]){ 
				movPosibles=true;
			}
			else if (fichaUltima==FICHA_LIBRE){
				fichaUltima=-1;
			}
			else{
				fichaUltima=tablero[filas][columnas]; //Si es distinto de 1 le ponemos su valor 
			}
			filas++;
		}
		if(!movPosibles){
			fichaUltima=-1;
			filas=0;
			columnas++;
		}
	}
}

void leerArchivoRecord(tLista &lista, bool &ok){
	lista.cont=0;
	ok=false;
	ifstream leerRecord;
	string nombre;
	tJugador jugador;
	leerRecord.open(ARCHIVORECORD);
	if(leerRecord.is_open()) {
		leerRecord >> nombre;
		while( nombre != CENTINELA && lista.cont < MAXRECORD)  { // carga la lista del archivo al array
			jugador.nombre = nombre;
			leerRecord >> jugador.puntos;
			lista.record[lista.cont]=jugador;
			lista.cont++;
			leerRecord >> nombre;
		}
		ok=true;
		leerRecord.close();
	}
}

void escribirArchivoRecord(const tLista &lista, bool &ok){
	ofstream escribirRecord;
	escribirRecord.open(ARCHIVORECORD);
	for(int i=0; i < lista.cont; i++){
		escribirRecord << lista.record[i].nombre << " " << lista.record[i].puntos << endl;
	}
	escribirRecord << CENTINELA;
	escribirRecord.close();
}

void nuevoRecord(int puntosAcumulados, bool &hecho) {
	string nombre;
	tLista lista;
	int pos;
	hecho=false;
	bool ok=false;
	lista.cont = 0;
	leerArchivoRecord(lista, ok);//Leemos el archivo de records
	if(ok){
		cout << "Introduzca su nombre: "; 
		cin >> nombre;// pide el nombre al usuario
		pos = buscar(lista, nombre, puntosAcumulados);
		if(pos < MAXRECORD) {// si la busqueda nos da una posicion que sea de las 10 primeras la colocamos, si no no hace falta añadirla
			for(int i = lista.cont; i > pos; i--) {
				if(i < MAXRECORD){ 
					lista.record[i] = lista.record[i-1];
				}
			}
			if(lista.cont < MAXRECORD){ //Si es menor que el maximo de Records aumentamos el contador
				lista.cont++;
			}
			lista.record[pos].nombre = nombre;
			lista.record[pos].puntos = puntosAcumulados;
			escribirArchivoRecord(lista, ok);
			hecho=true;
		}
	}
}

int buscar(const tLista &lista, string nombre, int puntos){
	int ini =0,fin= (lista.cont - 1) ,mitad;
	bool encontrado= false;
	while ((ini <=fin) && !encontrado){
		mitad= (ini +fin)/2;
		if (puntos == lista.record[mitad].puntos){
			encontrado = true;
			if(lista.record[lista.cont].nombre > nombre)
				mitad++;
		}
		else {
			if (puntos > lista.record[mitad].puntos)
				fin= mitad - 1;
			else
				ini = mitad + 1;
		}
	}
	if(!encontrado)
		mitad = ini;// cuando se sale del bucle por que (ini <=fin) ini coincide con la posicion a sustituir
	
	return mitad;
}

void muestraRecords(){
	tLista lista;
	string nombre;
	lista.cont = 0;
	bool ok;
	leerArchivoRecord(lista, ok);
	if(ok){ //Si se ha leido correctamente el archivo mostramos la lista de records por pantalla
		cout <<endl <<  "----RANKING 2048---- " << endl;
		for(int i = 0; i < lista.cont; i++) { // mostramos la lista por pantalla
			cout << lista.record[i].nombre <<"	" << lista.record[i].puntos << endl;
		}
	}
}

void guarda(const tTablero tablero, int puntos){
	ofstream archivo;
	string nombreArch;
	cout << "Introduce el nombre del archivo donde quieres guardar la partida : ";
	cin >> nombreArch;
	archivo.open(nombreArch);
	archivo << DIM << endl;
	for (int fila=0; fila < DIM ; fila++){
		for(int columna=0; columna <DIM; columna++){
			archivo << tablero[fila][columna] << endl;
		}
	}
	archivo << puntos << endl;
	archivo.close();
	
}