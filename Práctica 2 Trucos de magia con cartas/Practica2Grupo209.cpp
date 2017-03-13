/*Practica realizada por Nerea Gomez 1º A
He hecho la version opcional , es decir el truco del jugador desconfiado que consiste en cargar un mazo de un archivo,
barajarlo y repartirlo en en 4 montones, uno para cada jugador. Despues se hace el reparto de cartas de forma que cada jugador
formara su mazo uniendo el mazo derecho del de su derecha y el izquiero del de su izquierda, el proceso se repite tres veces.
Pero la ultima, el mazo de cada jugador estara formado por la union de  su mazo derecho y el izquiero del jugador que tiene a la
derecha, al final el jugador1 tendra escalera de color, el 2 un full , el 3 poker y el  4 color */

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

//Constantes y tipos
typedef enum {picas, treboles, diamantes, corazones} tPalo; //Enumerado de los palos 0=picas, 1=treboles, 2=diamantes, 3=corazones
typedef enum {as, dos, tres, cuatro, cinco, seis, siete, ocho, nueve, diez,jota, reina, rey} tNumero; //Enumerado de los numeros de la baraja
const int CARTASPORPALO=13; //Numero de cartas por palo
const int MAXCARTAS=53; //Numero de maximo de cartas
const int CENTINELA=52; //CENTINELA final del mazo
typedef int tCarta; //tipo tCarta
typedef tCarta tMazo[MAXCARTAS]; //Array de cartas 

//PROTOTIPOS VERSION 1
int menu();
tPalo darPalo(tCarta carta);
tNumero darNumero(tCarta carta);
string tPaloToString(tPalo palo);
string tNumeroToString(tNumero numero); 
void escribirCarta(tCarta carta); 
void crearMazoVacio(tMazo mazo);
int cuantasEnMazo(const tMazo mazo);
void escribirMazo(const tMazo mazo);
bool cargarMazo(tMazo mazo) ; 
void barajarMazo(tMazo mazo); 
bool unirMazos(tMazo mazoOriginal, const tMazo nuevoMazo);
bool partirMazo(tMazo mazoOrigen, int cuantasCoger, tMazo mazoDestino); 
void cortarMazo(tMazo mazo, int cuantas);
void guardarMazo(const tMazo mazo);
void opcionCargarMazo(tMazo mazo);
void opcionBarajarMazo(tMazo mazo);
void opcionUnirMontones(tMazo mazo);
void opcionCortarMazo(tMazo mazo);
void indicarMazoVacio(const tMazo mazo, bool &vacio);
int obtenerCarta(char paloCarta, int numCarta);


//PROTOTIPOS VERSION 2
void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo);
void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas);
void repartirIntercalando(const tMazo mazo, int enCuantosMazos, int queMazoPido, tMazo mazoNuevo);
void opcionRepartirNegroRojo(const tMazo mazo);
void opcionRepartirBajaAlta(const tMazo mazo);
void opcionRepartirIntercalando(const tMazo mazo);

//PROTOTIPOS VERSION 3 y 4
void trucoPosada();
void trucoTresMontones();
void habitacionesPosada(tMazo mazo, tMazo mazoMonton1, tMazo mazoMonton2, tMazo mazoMonton3, tMazo mazoMonton4);

//PROTOTIPOS VERSION OPCIONAL
void repartirParImpar(const tMazo mazo, tMazo izq, tMazo der);
void repartirFiguraNoFigura(const tMazo mazo, tMazo izq, tMazo der);
void trucoJugadorDesconfiado();
void inicializarMazos(tMazo mazoJugador1, tMazo mazoJugador2, tMazo mazoJugador3, tMazo mazoJugador4);
void repartirIntercaladoJugadores( const tMazo mazo, tMazo mazoJugador1, tMazo mazoJugador2, tMazo mazoJugador3, tMazo mazoJugador4);
void repartoMazosJugadores (const tMazo mazoJugador1,const tMazo mazoJugador2, const tMazo mazoJugador3, const tMazo mazoJugador4, tMazo mazoNegro, tMazo mazoRojo, tMazo mazoBajas, tMazo mazoAltas, tMazo mazoPares, tMazo mazoImpares, tMazo mazoFiguras, tMazo mazoNumeros);
void unionCartasJugadas(tMazo mazoJugador1, tMazo mazoJugador2, tMazo mazoJugador3, tMazo mazoJugador4,const  tMazo mazoNegro,const tMazo mazoRojo, const tMazo mazoBajas,const  tMazo mazoAltas, const tMazo mazoPares,const tMazo mazoImpares,const tMazo mazoFiguras, const tMazo mazoNumeros);
void unionCartasUltimaJugada(tMazo mazoJugador1, tMazo mazoJugador2, tMazo mazoJugador3, tMazo mazoJugador4,const  tMazo mazoNegro,const tMazo mazoRojo, const tMazo mazoBajas,const  tMazo mazoAltas, const tMazo mazoPares,const tMazo mazoImpares,const tMazo mazoFiguras, const tMazo mazoNumeros);
void escribirCartasJugadores(const tMazo mazoJugador1, const tMazo mazoJugador2, const tMazo mazoJugador3, const tMazo mazoJugador4);

//PROGRAMA PRINCIPAL
int main(){
	srand(time(NULL));
	tMazo mazo;
	int op;
	cout << "Bienvenido al simulador de trucos de magia ! " << endl;
	crearMazoVacio(mazo); //Creamos el mazo vacio al principio del programa
	do {
		op=menu();
		switch(op){
		case 1: 
			opcionCargarMazo(mazo);
			break;
		case 2: 
			opcionBarajarMazo(mazo);
			break;
		case 3: 
			opcionUnirMontones(mazo);
			break;
		case 4: 
			opcionCortarMazo(mazo);
			break;
		case 5:
			guardarMazo(mazo);
			break;
		case 6:
			opcionRepartirNegroRojo(mazo);
			break;
		case 7:
			opcionRepartirBajaAlta(mazo);
			break;
		case 8:
			opcionRepartirIntercalando(mazo);
			break;
		case 9:
			trucoTresMontones();
			break;
		case 10:
			trucoPosada();
			break;
		case 11:
			trucoJugadorDesconfiado();
			break;
		}
	}while (op!=0);
	cout << "Adios ! " << endl;
	system("pause");
	return 0;
}

//VERSION 1
//Funcion opcion cortar mazo, 1 muestra el mazo original, pide el numero de cartas para cortar y muestra el mazo cortado
void opcionCortarMazo(tMazo mazo){
	int cuantas;
	cout << "Mazo original : " << endl; 
	escribirMazo(mazo);
	do { //PEDIMOS EL NUMERO DE CARTAS PARA CORTAR 
		cin.clear();
		cin.sync();
		cout << "Cortar el mazo, ¿cuantas cartas de arriba tomas para ponerlas abajo? : ";
		cin >> cuantas;
	}while (cuantas < 0 || cin.fail());

	cout << endl << endl<<  "El mazo cortado queda asi : " << endl;
	cortarMazo(mazo, cuantas);
	escribirMazo(mazo);
	cout << endl;
}

//Funcion opcion añadir mazo,
void opcionUnirMontones(tMazo mazo){
	tMazo nuevoMazo;
	if(cargarMazo(nuevoMazo)){ //Se ha cargado el mazo del fichero
		cout << "Mazo Original : " << endl; //mostramso el mazo original
		escribirMazo(mazo);
		//MOSTRAMOS EL MAZO CARGADO DE ARCHIVO
		cout << endl << "Mazo cargado de archivo : " << endl; 
		escribirMazo(nuevoMazo);
		if(unirMazos(mazo, nuevoMazo)){ //UNIMOS LOS MAZOS 
			cout << endl << "Mazo concatenado : " << endl; 
			escribirMazo(mazo); //Escribimos el mazo concatenado
		}
		else{ //NO SE PUEDE UNIR 
			cout << "Error , la union supera el numero maximo de cartas " << endl; 
		}
	}
	else{ //No se ha cargado el mazo del fichero 
		cout << "Error, no se ha podido cargar el mazo del fichero " << endl;
	}
}

//Funcion opcion barajar mazo, si el mazo esta vacio lo indica, si no escribimos el mazo original, lo barajmos y muestra el mazo barajado
void opcionBarajarMazo(tMazo mazo){
	if (cuantasEnMazo(mazo)==0){ //El mazo esta vacio y no hay nada que barajar
		cout << endl <<  "El mazo esta vacio, no hay nada que barajar " << endl;
	} 
	else{ //Si el mazo no esta vacio
		escribirMazo(mazo); //Escribimos el mazo original
		barajarMazo(mazo);
		cout << endl << "Mazo barajado :" << endl;
		escribirMazo(mazo);
	}
}

//Funcion opcion cargar mazo, si el mazo se ha cargado lo escribimos y si no muestra un error
void opcionCargarMazo(tMazo mazo){
	if (cargarMazo(mazo)){ //Se ha cargado el fichero
		escribirMazo(mazo);
	}
	else{ //Indicamos que no se ha cargado
		cout << "Error , fichero no encontrado " << endl;
	}
}

//Funcion menu
int menu(){
	tCarta op;
	cout << endl;
	cout <<"1.- Cargar un mazo de cartas de fichero " << endl;
	cout <<"2.- Barajar mazo de cartas. " << endl;
	cout <<"3.- Añadir mazo. " << endl;
	cout <<"4.- Cortar mazo. " << endl;
	cout <<"5.- Guardar mazo de cartas en fichero . " << endl;
	cout <<"6.- Separar negros y rojos . " << endl;
	cout <<"7.- Separar en altas y bajas ." << endl;
	cout <<"8.- Repartir un mazo de manera alterna en tres montones . " << endl;
	cout <<"9.- Truco de los tres montones . " << endl;
	cout <<"10.- Truco de la Posada ." << endl;
	cout << "11.- Truco del jugador de poker desconfiado ." << endl;
	cout <<"0.- Salir " << endl;
	cout <<"Escriba su opcion (0-10) : ";
	cin >> op;
	while ( op <0 || op>11|| cin.fail()){
		cin.sync();
		cin.clear();
		cout << "Opcion incorrecta, introduzca una nueva opcion por favor : ";
		cin >> op;
	}
	return op;
}

//Funcion que devuelve el numero de la carta
tNumero darNumero(tCarta carta){
	return tNumero(carta%CARTASPORPALO);
}

//Funcion que devuelve el palo de la carta , 0=picas, 1=treboles, 2= diamantes, 3=corazones
tPalo darPalo(tCarta carta){
	return tPalo(carta/CARTASPORPALO);
}

//Funcion que convierte el enumerado tPalo de la carta a un string
string tPaloToString(tPalo palo){
	string palo_escritura;
	if(palo==picas){
		palo_escritura="picas";
	}else if(palo==treboles){
		palo_escritura="treboles";
	}else if (palo==diamantes){
		palo_escritura="diamantes";
	}else if (palo==corazones){
		palo_escritura="corazones";
	}
	return palo_escritura;
}

//Funcion que convierte el tNumero de la carta a un string
string tNumeroToString(tNumero numero){
	string num_escritura;
	if(numero==as){
		num_escritura="A"; //as
	}else if (numero==jota){
		num_escritura="J"; //jota
	}else if (numero==reina){
		num_escritura="Q"; //Reina
	}else if (numero==rey){
		num_escritura="K"; //k
	}
	else {
		tCarta numeroCarta =tCarta (numero)+1;
		num_escritura=to_string(numeroCarta);
	}
	return num_escritura;
}

//Funcion que escribe la carta
void escribirCarta(tCarta carta){
	tPalo palo=darPalo(carta); //Obtenemos el palo de la carta
	tNumero num=darNumero(carta); //Obtenemos el numero de la carta
	cout << tNumeroToString(num) << " de " << tPaloToString(palo) << endl;
}

//Funcion que crea el mazo vacio ponienedo el centinela en la primera posicion 
void crearMazoVacio(tMazo mazo){
	mazo[0]=CENTINELA; //ponemos el centinela en la primera posicion , asi sera un mazo vacio
}

//Funcion que devuelve cuantas cartas hay en el mazo
int cuantasEnMazo(const tMazo mazo){
	tCarta numCartas=0;
	while (mazo[numCartas]!=CENTINELA && (numCartas < MAXCARTAS)){ //Mientras no sea el centinela se sigue contando 
		numCartas++; //Aumentamos el contador 
	}
	return numCartas;
}

//Funcion que muestra por pantalla el contenido del mazo
void escribirMazo(const tMazo mazo){
	tCarta contador=0;
	if (cuantasEnMazo(mazo)==0){
		cout << "El mazo esta vacio " << endl;
	}
	else{
		while (mazo[contador]!=CENTINELA && (contador < MAXCARTAS)){ //Mientras lo que hay en la posicion sea distinto del centinela
			escribirCarta(mazo[contador]); //Escribimos la carta que hay en esa posicion
			contador++; //Aumentamos el contador
		}
	}
}

//Funcion que optiene la carta , dado el palo y el numero
int obtenerCarta(char paloCarta, int numCarta){
	tCarta carta;
	if (paloCarta=='p'){ //picas
		carta=tCarta(numCarta-1); 
	}else if (paloCarta=='t'){//treboles
		carta=tCarta(CARTASPORPALO + numCarta-1);
	}else if (paloCarta=='d'){//diamantes
		carta=tCarta(2*CARTASPORPALO +  numCarta-1);
	}else if (paloCarta=='c'){//corazones
		carta=tCarta(3*CARTASPORPALO + numCarta -1);
	}
	return carta;
}

//MODIFICAR Funcion que devuelve true si se ha cargado el archivo y false en caso contrario
bool cargarMazo(tMazo mazo){
	bool carga=false;
	ifstream archivo;
	string nomArch;
	char paloCarta;
	tCarta numCarta, contador=0;
	cout << "Introduce el nombre del fichero del que desea coger el mazo : ";
	cin >> nomArch;
	archivo.open(nomArch); //Abrimos el archivo 
	if (archivo.is_open()){
		archivo >> paloCarta; //leemos el palo de la carta
		while (paloCarta!='x' && contador < MAXCARTAS){ //Si es distinto del centinela y contador < MAXCARTAS , obtenemos el numero y lo guardamos en el array
			archivo >> numCarta; //leemos el numero de la carta
			mazo[contador]=obtenerCarta(paloCarta,numCarta); //Guardamos la carta en la posicion del array;
			contador++; //Actualizamos el contador
			archivo >> paloCarta;  //Volvemos a leer el palo de la carta
		}
		mazo[contador]=CENTINELA; //Escribimos el centinela en la posicion siguiente a la ultima ocupada
		carga=true;
		archivo.close();
	}
	return carga;
}

//Funcion que baraja el mazo
void barajarMazo(tMazo mazo){
	tCarta numCartas, intercambios, contBarajar=0, pos1,pos2,aux;
	numCartas=cuantasEnMazo(mazo); //Calculamos el numero de cartas que hay en el mazo
	intercambios=3*numCartas; //Numero total de intercambios
	while (contBarajar < intercambios){
		do{
			pos1= rand() % ((numCartas-1) +1); //numCartas - 1 porque hay una posicion menos que numero de cartas, porque las posiciones empiezan desde 0
			pos2= rand() % ((numCartas-1) +1);
		}while (pos1==pos2); //Las posiciones tienen que ser distintas , posiciones validas?

		//Se intercambian esas posiciones aleatorias
		aux=mazo[pos1]; //Guardamos en la variable auxiliar lo que hay en la pos 1
		mazo[pos1]=mazo[pos2]; //En la pos1 guardamos lo que hay en la pos 2
		mazo[pos2]=aux; //En la pos2 guardamos lo que hay en la variables auxiliar es decir lo de la pos1
		contBarajar++; //a
	}
}

//Funcion que dado dos mazos los une
bool unirMazos(tMazo mazoOriginal, const tMazo nuevoMazo){
	bool unido=false;
	tCarta cartasOriginal ,cartasNuevo,contador,contMazoNuevo=0;
	cartasOriginal=cuantasEnMazo(mazoOriginal); // Cartas que hay en el mazoOriginal
	cartasNuevo=cuantasEnMazo(nuevoMazo); //Cartas que hay en el nuevoMazo
	if ((cartasNuevo+cartasOriginal)< MAXCARTAS){ //Si la suma de las cartas no supera el maximo se unen  
		contador=cartasOriginal; //La Ultima posicion ocupada del mazoOriginal sera cartasOriginal-1, por lo que el contador empieza en cartasOriginal
		while (nuevoMazo[contMazoNuevo]!=CENTINELA && (contMazoNuevo < MAXCARTAS)){
			mazoOriginal[contador]=nuevoMazo[contMazoNuevo]; //Guardamos en el mazoOriginal a partir del contador lo que hay en el nuevoMazo
			contMazoNuevo++;
			contador++;
		}
		mazoOriginal[contador]=CENTINELA; //En la ultima posicion colocamos el centinela
		unido=true;
	}
	return unido;
}

//Funcion que parte el mazo 
bool partirMazo(tMazo mazoOrigen, int cuantasCoger, tMazo mazoDestino){
	bool partir=false;
	tCarta contador; 
	if (cuantasEnMazo(mazoOrigen) >= cuantasCoger){ //HAY SUFICIENTES CARTAS
		partir=true; //Se parte el mazo
		crearMazoVacio(mazoDestino); //Creamos el mazo vacio
		for (int i=0; i< cuantasCoger;i++){ 
			mazoDestino[i]=mazoOrigen[i]; //Ponemos las cartas que hemos indicado que vamos a coger en el mazoDestino
		}
		mazoDestino[cuantasCoger]=CENTINELA; //Ponemos el centinela despues de la ultima carta

		//Desplazamos hacia la izquierda las cartas que quedan 
		contador=cuantasCoger; //Porque es en la posicion en la que tenemos que empezar a desplazar cartas
		while (mazoOrigen[contador]!=CENTINELA && (contador < MAXCARTAS)){
			mazoOrigen[contador-cuantasCoger]=mazoOrigen[contador];
			contador++;
		}
		mazoOrigen[contador-cuantasCoger]=CENTINELA; //Ponemos el centinela en la ultima posicion correspondiente
	}
	return partir;
}

//Funcion que corta el mazo por cuantas
void cortarMazo(tMazo mazo, int cuantas){
	tMazo mazoAuxiliar;
	if(partirMazo(mazo,cuantas,mazoAuxiliar)){ //si se ha partido el mazo
		unirMazos(mazo,mazoAuxiliar); //Se unen los mazos (el original con el que se ha creado);
	}
}

//Funcion que guarda el mazo en el fichero que indique el usuario
void guardarMazo(const tMazo mazo){
	string nomArch, paloString;
	int contador=0; //tCarta contador=0, numCarta;
	ofstream archivo;
	cout << "Introduce un nombre de archivo : ";
	cin >> nomArch;
	archivo.open(nomArch);
	while (mazo[contador]!=CENTINELA && (contador < MAXCARTAS)){
		paloString=tPaloToString(darPalo(mazo[contador])); //obtenemos el palo de la carta y lo convertimos a un string
		tNumero num =darNumero(mazo[contador]);//obtenemos el numero de la carta
		archivo << paloString.substr(0,1) << " " << int(num)+1 << endl; //Escribimos en el archivo el palo de la carta (solo con una letra) y el numero
		contador++;
	}
	archivo << "x" << endl; //CENTINELA FINAL 
	archivo.close();
}

//VERSION2
//Funcion opcion repartir un mazo de manera alterna en 3 montones, si el mazo esta vacio lo indica y sino hace el reparto
void opcionRepartirIntercalando(const tMazo mazo){
	tMazo primerMonton, segundoMonton, tercerMonton;
	if (cuantasEnMazo(mazo)==0){
		cout << "El mazo esta vacio, no hay nada que repartir " << endl;
	}
	else{
		cout << "Mazo original " << endl;
		escribirMazo(mazo);
		cout << endl << "Primer monton :" << endl;
		repartirIntercalando(mazo,3,1,primerMonton);
		escribirMazo(primerMonton);
		cout << endl << "Segundo monton :" << endl;
		repartirIntercalando(mazo,3,2, segundoMonton);
		escribirMazo(segundoMonton);
		cout << endl << "Tercer monton :" << endl;
		repartirIntercalando(mazo,3,3,tercerMonton);
		escribirMazo(tercerMonton);
	}
}

//Funcion que reparte intercalando las cartas en los mazos que quieras y pone en mazoNuevo el mazo que pides
void repartirIntercalando(const tMazo mazo, int enCuantosMazos, int queMazoPido, tMazo mazoNuevo){
	int numCartas=cuantasEnMazo(mazo); //vemos cuantas cartas tiene el mazo
	int cont=0;
	for (int i=(queMazoPido-1); i <numCartas; i=i+(enCuantosMazos)){  
		mazoNuevo[cont]=mazo[i]; //Guardamos en el mazoNuevo las cartas del mazo que hemos pedido
		cont++;
	}
	mazoNuevo[cont]=CENTINELA;
}

//Funcion opcion repatir en altas y bajas, si el mazo esta vacio lo indica y si no hace el reparto en bajas y alta y lo muestra
void opcionRepartirBajaAlta(const tMazo mazo){
	tMazo mazoBajas, mazoAltas;
	if (cuantasEnMazo(mazo)==0){ //Primero comprobamos que el mazo no esta vacio
		cout << "El mazo esta vacio, no hay nada que repartir" << endl;
	}
	else{
		cout << "Mazo Original : " << endl;
		escribirMazo(mazo);
		repartirBajaAlta(mazo,mazoBajas,mazoAltas);
		cout << "Mazo bajas " << endl; //Escribimos el mazo de bajas
		escribirMazo(mazoBajas);
		cout << "Mazo altas " << endl; //Escribimos el mazo altas
		escribirMazo(mazoAltas);
	}
}

//Funcion que reparte en bajas y altas, recorre el mazo y si la carta es baja la guarda en mazoBajas y si no en mazoAltas
void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas){
	tCarta contador=0, contadorBajas=0, contadorAltas=0; 
	const tNumero LimSuperior=siete;
	while (mazo[contador]!=CENTINELA && (contador < MAXCARTAS)){
		if (darNumero(mazo[contador]) <= LimSuperior){ //Si es menor o igual que siete lo guardamos en mazoBajas
			mazoBajas[contadorBajas]=mazo[contador];
			contadorBajas++;
		}
		else{ //Si es mayor que siete lo guardamos en mazoAltas
			mazoAltas[contadorAltas]=mazo[contador];
			contadorAltas++;
		}
		contador++;
	}
	mazoBajas[contadorBajas]=CENTINELA;
	mazoAltas[contadorAltas]=CENTINELA;
}

/*Funcion opcion repartir en negros y rojos, si el mazo esta vacio lo indica y si no muestra el mazo original lo reparte en 
negros y rojos y escribe ambos mazos*/
void opcionRepartirNegroRojo(const tMazo mazo){
	tMazo mazoNegro, mazoRojo;
	if (cuantasEnMazo(mazo)==0){
		cout << "El mazo esta vacio, no se puede repartir en Negros y Rojos " << endl;
	}
	else{
		cout << "Mazo Original : " << endl;
		escribirMazo(mazo);
		repartirNegroRojo(mazo, mazoNegro,mazoRojo);
		cout << endl <<  "Mazo negro : " <<endl;
		escribirMazo(mazoNegro);
		cout << endl << "Mazo rojo : " << endl;
		escribirMazo(mazoRojo);
	}

}

//Funcion que reparte los negros y los rojos separados
void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo){
	int contador=0,contadorNegro=0, contadorRojo=0;
	while (mazo[contador]!=CENTINELA){
		if (darPalo(mazo[contador])==picas || darPalo(mazo[contador])==treboles){
			mazoNegro[contadorNegro]=mazo[contador];
			contadorNegro++;
		}
		else {
			mazoRojo[contadorRojo]=mazo[contador];
			contadorRojo++;
		}
		contador++;
	}
	mazoRojo[contadorRojo]=CENTINELA;
	mazoNegro[contadorNegro]=CENTINELA;
}

//VERSION3
/*El truco de los tres montones consiste en cargar un mazo, si se ha cargado barajarlo, repartimos el mazo en 3 montones 
intercaladamente, el usuario dira en que monton esta la carta que quiere y uniremos los mazos de forma que el mazo donde 
esta la carta del usuario sera el del medio, este proceso se realiza tres veces, la maquina adivinara la carta
que sera la cata de la posicion 11 */
void trucoTresMontones(){
	const int CARTAELEGIDA=10;
	tMazo mazo,mazo1,mazo2,mazo3;
	int monton; //tCarta monton;
	if (cargarMazo(mazo)){
		barajarMazo(mazo);
		for (int i=0; i<3; i++){
			//MOSTRAMOS LOS TRES MAZOS
			cout << "Mazo 1 " << endl ;
			repartirIntercalando(mazo,3,1,mazo1);
			escribirMazo(mazo1);
			cout << endl <<"Mazo 2 " << endl;
			repartirIntercalando(mazo,3,2,mazo2);
			escribirMazo(mazo2);
			cout << endl <<"Mazo 3 " << endl;
			repartirIntercalando(mazo,3,3,mazo3);
			escribirMazo(mazo3);
			do{//PEDIMOS  AL USUARIO LA CARTA SI NO ES LA 1 VEZ SE LE RECUERDA QUE ES LA DE ANTES
				cin.clear(); cin.sync(); 
				if (i==0){ //si es la 1 iteracion , se le pide al usuario que memorice la carta
					cout << "Memoriza alguna carta de algun monton y di en que monton esta : " ;
					cin >> monton;
				}
				else{ //Se le recuerda que ebe ser la misma carta
					cout << "Indica en que monton esta la carta que memorizaste antes : " ;
					cin >> monton;
				}
			}while (monton <1 || monton >3 || cin.fail());

			crearMazoVacio(mazo); //Ponemos el mazo vacio para guardar ahi el mazo unido
			if (monton==1){ //SE UNEN LOS MAZOS PONIENDO EL INDICADO POR EL USUARIO EN EL MEDIO
				unirMazos(mazo,mazo2);
				unirMazos(mazo,mazo1);
				unirMazos(mazo,mazo3);
			}else if (monton==2){
				unirMazos(mazo,mazo1);
				unirMazos(mazo, mazo2);
				unirMazos(mazo,mazo3);
			}else if (monton==3){
				unirMazos(mazo,mazo1);
				unirMazos(mazo, mazo3);
				unirMazos(mazo,mazo2);
			}
			cout << endl << "Mazo tras unir los montones : " << endl;
			escribirMazo(mazo); //MOSTRAMOS EL MAZO UNIDO
			cout << endl;
		}
		cout << " Tu carta es : " ;
		escribirCarta(mazo[CARTAELEGIDA]); //Carta 11 posicion 10
	}
	else {
		cout << "Ha habido un error al cargar el archivo " << endl;
	}
}

//VERSION 4
/*Funcion que hace el reparto de las habitaciones de la posada que consiste en repartir intercalado en 4 montones, 
es decir cada monton corresponde a una habitacion y escribimos lo que hay en cada habitacion*/
void habitacionesPosada(tMazo mazo, tMazo mazoMonton1, tMazo mazoMonton2, tMazo mazoMonton3, tMazo mazoMonton4){
	cout << endl << "Habitacion 1 : "<<endl;
	repartirIntercalando(mazo,4,1,mazoMonton1);
	escribirMazo(mazoMonton1);
	cout << endl << "Habitacion 2 : "<<endl;
	repartirIntercalando(mazo,4,2,mazoMonton2);
	escribirMazo(mazoMonton2);

	cout << endl << "Habitacion 3 :" << endl;
	repartirIntercalando(mazo,4,3,mazoMonton3);
	escribirMazo(mazoMonton3);

	cout << endl << "Habitacion 4:" << endl;
	repartirIntercalando(mazo,4,4,mazoMonton4);
	escribirMazo(mazoMonton4);
}

/*Funcion que gestiona el truco de la posada, que consiste en cargar un mazo y si este se ha podido cargar divide el mazo en 
4 montones (4 habitaciones), lo unimos en 4 montones , cortamos el mazo por donde queramos y se mostraran de nuevo las cuatro
habitaciones , de manera que una habitacion tendra los 4 reyes, otra las reinas, otra las J y en otra los A*/
void trucoPosada(){
	tMazo mazo,mazoMonton1,mazoMonton2,mazoMonton3,mazoMonton4;
	int cuantas;
	if(cargarMazo(mazo)){
		cout << "Mazo  Original : ";
		escribirMazo(mazo);
		cout << endl;
		habitacionesPosada(mazo,mazoMonton1, mazoMonton2,mazoMonton3,mazoMonton4);
		//concatenamos en un mazo solo
		cout << "Ahora uniremos los cuatro mazos en un mazo " << endl;
		crearMazoVacio(mazo); //Ponemos el mazo vacio
		unirMazos(mazo,mazoMonton1);
		unirMazos(mazo,mazoMonton2);
		unirMazos(mazo,mazoMonton3);
		unirMazos(mazo,mazoMonton4);
		cout << "¿Por cuantas cartas deseas cortar el mazo ? : ";
		cin >> cuantas;
		cortarMazo(mazo, cuantas);
		habitacionesPosada(mazo,mazoMonton1,mazoMonton2,mazoMonton3,mazoMonton4);
	}
	else{ 
		cout << "No se ha cargado el fichero " << endl;
	}
}

//VERSION OPCIONAL
//Funcion que inicializa los mazos para el truco del jugador desconfiado
void inicializarMazos(tMazo mazoJugador1, tMazo mazoJugador2, tMazo mazoJugador3, tMazo mazoJugador4){
	crearMazoVacio(mazoJugador1);
	crearMazoVacio(mazoJugador2);
	crearMazoVacio(mazoJugador3);
	crearMazoVacio(mazoJugador4);
}

//Funcion que hace el reparto de cartas intercalado a los jugadores en 4 mazos,uno para cada uno
void repartirIntercaladoJugadores( const tMazo mazo, tMazo mazoJugador1, tMazo mazoJugador2, tMazo mazoJugador3, tMazo mazoJugador4){
	repartirIntercalando(mazo,4,1,mazoJugador1);//Jugador 1
	repartirIntercalando(mazo,4,2,mazoJugador2);//Jugador 2
	repartirIntercalando(mazo,4,3,mazoJugador3); //Jugador 3
	repartirIntercalando(mazo,4,4,mazoJugador4); //Jugador 4 
}

//Funcion que hace el reparto de cartas a los jugadores para el truco del jugador desconfiado, de modo que cada uno tendra un mazo izquierdo y uno derecho
void repartoMazosJugadores (const tMazo mazoJugador1,const tMazo mazoJugador2, const tMazo mazoJugador3, const tMazo mazoJugador4, tMazo mazoNegro, tMazo mazoRojo, tMazo mazoBajas, tMazo mazoAltas, tMazo mazoPares, tMazo mazoImpares, tMazo mazoFiguras, tMazo mazoNumeros){
	//jugador 1
	repartirNegroRojo(mazoJugador1, mazoNegro, mazoRojo);
	//jugador 2
	repartirBajaAlta(mazoJugador2, mazoBajas, mazoAltas);
	//jugador 3
	repartirParImpar(mazoJugador3, mazoPares, mazoImpares);
	//jugador 4
	repartirFiguraNoFigura(mazoJugador4, mazoFiguras, mazoNumeros);
}

/*Funcion que une los mazos de los jugadores para el truco del jugador desconfiado , que consiste en coger el mazo derecho del de su derecha y 
y el iquierdo del de su izquierda*/
void unionCartasJugadas(tMazo mazoJugador1, tMazo mazoJugador2, tMazo mazoJugador3, tMazo mazoJugador4,const  tMazo mazoNegro,const tMazo mazoRojo, const tMazo mazoBajas,const  tMazo mazoAltas, const tMazo mazoPares,const tMazo mazoImpares,const tMazo mazoFiguras, const tMazo mazoNumeros){
	//jugador 1
	unirMazos(mazoJugador1,mazoBajas);
	unirMazos(mazoJugador1, mazoNumeros);
	//jugador 2
	unirMazos(mazoJugador2,mazoPares);
	unirMazos(mazoJugador2, mazoRojo);
	//jugador 3
	unirMazos(mazoJugador3,mazoFiguras);
	unirMazos(mazoJugador3, mazoAltas);
	//jugador 4
	unirMazos(mazoJugador4,mazoNegro);
	unirMazos(mazoJugador4, mazoImpares);
}

/*Funcion que une los mazos de los jugadores en la ultima jugada para el truco del jugador desconfiado, la union consiste en unir el mazo derecho del
propio jugador con el mazo izquiero del jugador de la derecha */
void unionCartasUltimaJugada(tMazo mazoJugador1, tMazo mazoJugador2, tMazo mazoJugador3, tMazo mazoJugador4,const  tMazo mazoNegro,const tMazo mazoRojo, const tMazo mazoBajas,const  tMazo mazoAltas, const tMazo mazoPares,const tMazo mazoImpares,const tMazo mazoFiguras, const tMazo mazoNumeros){
	//Union de los mazos la ultima vez 
	//jugador 1
	unirMazos(mazoJugador1,mazoRojo);
	unirMazos(mazoJugador1, mazoBajas);
	//jugador 2
	unirMazos(mazoJugador2,mazoAltas);
	unirMazos(mazoJugador2, mazoPares);
	//jugador 3
	unirMazos(mazoJugador3,mazoImpares);
	unirMazos(mazoJugador3, mazoFiguras);
	//jugador 4
	unirMazos(mazoJugador4,mazoNumeros);
	unirMazos(mazoJugador4, mazoNegro);
}

//Funcion que escribe los mazos de cada uno de los jugadores 
void escribirCartasJugadores(const tMazo mazoJugador1, const tMazo mazoJugador2, const tMazo mazoJugador3, const tMazo mazoJugador4){
	cout << endl <<"Cartas del Jugador 1 : " << endl;
	escribirMazo(mazoJugador1);
	cout << endl << "Cartas del Jugador 2 : " << endl;
	escribirMazo(mazoJugador2);
	cout << "Cartas del Jugador 3 : " << endl;
	escribirMazo(mazoJugador3);
	cout << "Cartas Jugador 4 : " << endl;
	escribirMazo(mazoJugador4);
}

/*Funcion que gestiona el truco del jugador desconfiado , que consiste en cargar un mazo , si se ha cargado se barajan las cartas y se reparte intercalando
en 4 montones, uno para cada jugador. Despues tenemos que hacer el reparto de cartas como indica el truco (cada  jugador tendra un mazo izquierdo y uno
derecho ) y se unen de la forma que cada jugador coge el mazo derecho del de su derecha y el izquiero del de su izquierda, esto se repite tres veces, 
pero la ultima vez se unen de forma que cada jugador coge su mazo derecho y el izquiero del jugador que tiene a la derecha, de forma que al final
el jugador1 tendra escalera de color, el 2 un full , el 3 poker y el  4 color*/
void trucoJugadorDesconfiado(){
	 tMazo mazo, mazoJugador1,mazoJugador2,mazoJugador3,mazoJugador4, mazoNegro,mazoRojo,mazoBajas, mazoAltas, mazoPares, mazoImpares;
	 tMazo mazoFiguras, mazoNumeros;
	 if(cargarMazo(mazo)){
		cout << "Se repartiran las siguientes 20 cartas entre los cuatro jugadores : " << endl;
		barajarMazo(mazo);
		escribirMazo(mazo); //Barajamos y escribimos el mazo
		cout << endl << "Reparto inicial de cartas entre los cuatro jugadores " << endl;
		repartirIntercaladoJugadores(mazo, mazoJugador1,mazoJugador2,mazoJugador3,mazoJugador4);
		escribirCartasJugadores(mazoJugador1,mazoJugador2,mazoJugador3,mazoJugador4); //Escribimos las cartas despues del reparto
		for (int i=0; i<=2; i++){
			//Hacemos el reparto de cartas a los jugadores
			repartoMazosJugadores(mazoJugador1,mazoJugador2,mazoJugador3,mazoJugador4,mazoNegro, mazoRojo, mazoBajas, mazoAltas, mazoPares, mazoImpares, mazoFiguras, mazoNumeros);
			inicializarMazos(mazoJugador1, mazoJugador2, mazoJugador3, mazoJugador4);
			if (i < 2 ){
				unionCartasJugadas( mazoJugador1,mazoJugador2, mazoJugador3,  mazoJugador4, mazoNegro, mazoRojo, mazoBajas, mazoAltas, mazoPares,mazoImpares,mazoFiguras, mazoNumeros);
			}
			else{  //union de cartas de la ultima jugada
				unionCartasUltimaJugada(mazoJugador1,mazoJugador2, mazoJugador3, mazoJugador4, mazoNegro, mazoRojo, mazoBajas,mazoAltas, mazoPares, mazoImpares, mazoFiguras, mazoNumeros);
			}
			//Escribimos las cartas
			cout << "Distribucion tras el " ;
			if (i==0){
				cout << " primer " ;
			} else if (i==1){
				cout << "segundo " ;
			} else if (i==2){
				cout << "tercer ";
			}
			cout << " paso : " << endl;
			escribirCartasJugadores(mazoJugador1, mazoJugador2, mazoJugador3, mazoJugador4);
		 }
	 }
	 else{
		 cout << "No se ha podido cargar el archivo " << endl;
	 }
 }

//Funcioon que reparte el mazo original en un mazo izquierdo que contiene las cartas pares y en el dercho que contiene las impares
void repartirParImpar(const tMazo mazo, tMazo izq, tMazo der){
	int contador =0, contadorIzq=0, contadorDer=0,numero;
	crearMazoVacio(izq);
	crearMazoVacio(der);
	while (mazo[contador]!=CENTINELA && contador < MAXCARTAS){
		tNumero num = darNumero(mazo[contador]);//obtenemos el numero de la carta
		numero= int (num) +1 ; //Pasamos el enumerado a un numero
		if (numero%2==0){
			izq[contadorIzq]=mazo[contador]; //Pares
			contadorIzq++;
		}
		else{
			der[contadorDer]=mazo[contador]; //impares
			contadorDer++;
		}
		contador++;
	}
	izq[contadorIzq]=CENTINELA;
	der[contadorDer]=CENTINELA;
}

//Funcion que reparte el mazo original en un mazo izquierdo que contiene las figuras y en uno derecho que contiene los numeros
void repartirFiguraNoFigura(const tMazo mazo, tMazo izq, tMazo der){
	int contador=0, contIzq=0 , contDer=0;
	crearMazoVacio(izq);
	crearMazoVacio(der);
	while (mazo[contador]!=CENTINELA &&  contador < MAXCARTAS){
		tNumero num = darNumero(mazo[contador]);//obtenemos el numero de la carta
		if (num==as || num==jota || num==reina || num==rey){
			izq[contIzq]=mazo[contador]; //FIGURAS
			contIzq++;
		}
		else {
			der[contDer]=mazo[contador];
			contDer++;
		}
		contador++;
	}
	izq[contIzq]=CENTINELA;
	der[contDer]=CENTINELA;
}