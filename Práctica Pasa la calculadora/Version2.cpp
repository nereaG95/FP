#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

//Constantes
const int MAX_NUMERO=9;
const int ABANDONO=0;
const int MAQUINA=1;
const int PERSONA=2;

//Prototipos
//VERSION 1
int quienEmpieza();  //Funcion que decide aleatoriamente quien empieza (devolvera 1 si empieza A y 2 si empieza B)
bool mismaFila(int ultimo, int nuevo); // Devuelve true si nuevo está en la misma fila que ultimo; en caso contrario devuelve false.
bool mismaColumna(int ultimo, int nuevo); // Devuelve true si nuevo está en la misma columna que ultimo; en caso contrario devuelve false
int digitoAleatorio(); //Devuelve un dígito aleatorio.
bool digitoValido(int ultimo, int nuevo); //Devuelve true si nuevo cumple las reglas del juego con respecto a ultimo; en caso contrario devuelve false
int digitoAutomata(int ultimo); // Devuelve un dígito generado aleatoriamente que cumpla las reglas del juego con respecto a ultimo. 
int digitoPersona(); //Pide un dígito al jugador. Devolverá un valor válido (entre 0 y 9). Para cada valor no válido, mostrará un error y solicitará de nuevo el dígito.
void mostrarTeclado(); //Funcion que muestra el teclado
string pedirDatos(); //Funcion que pide los datos al usuario
int digitoPersona(int ultimo); // Pide un dígito al jugador mostrando el teclado. Sólo devolverá un valor que cumpla las reglas del juego o 0. Para cada valor no válido, mostrará un error y volverá a solicitar el dígito. 
int pasaCalculadora(); //Funcion que va a conducir el desarrollo del juego
int sumaNumeros(int anterior, int nuevo); //Funcion que suma el anterior y el nuevo numero

//VERSION 2
int menu ();
bool mostrar(string nombArch);

//VERSION 3  
void actInforme(int jugadas, int ganadas, int abandonos);
void copiarArchivo(string ArchOrigen , string ArchDestino); //Funcion que copia el archivo origen a uno destino



int main(){
	srand(time(NULL));
	copiarArchivo("auxiliar.txt", "PRUEBA.txt");
	const string ARCHIVO="versionPC.txt";
	int ganador, op, jugadas=0, ganadasMaquina=0, abandonadas=0;
	string dato;
	dato=pedirDatos(); //Pedimos los datos al jugador
	op=menu();
	while (op!=0){
		switch(op){
			case 1: //OPCION DE JUGAR A PASA LA CALCULADORA
			{
				jugadas=1;
				ganador=pasaCalculadora(); 
				if (ganador ==ABANDONO){//Se cancela el juego
					cout << "Abandonas OHHHHHH !!!  " << endl << endl;
					abandonadas=1;
				}else if (ganador==MAQUINA){ //pierde la maquina
					cout << "Enhorabuena, la maquina ha perdido y usted ," << dato << " ,ha ganado :)! " << endl;
				}else if (ganador==PERSONA){ //Pierde el jugador
					cout << "Lo siento , he ganado! " << endl << endl;
					ganadasMaquina=1;
				}
				cout << "Hasta la proxima " << dato << endl<< endl;
				actInforme(jugadas,ganadasMaquina,abandonadas);
			}
			break;
			case 2://OPCION DE ACERCA DE PASA LA CALCULADORA
			{
				mostrar(ARCHIVO);
				actInforme(jugadas,ganadasMaquina,abandonadas);
			}
			break;
		}
		op=menu();
	}
	cout << endl << "Gracias por jugar a pasa la calculadora , Hasta la proxima " << dato << endl;
	system("pause");
	return 0;
}

// Funcion que conduce el desarrolo del juego y devuelve que jugador es el ganador
int pasaCalculadora(){
	const int MAX_SUMA=31;
	int jugador,numero, suma=0;
	bool final=false;

	jugador=quienEmpieza(); //Generamos el numero aleatorio para ver que jugador empieza
	if (jugador==MAQUINA){ //empieza a jugar el ordernador
		cout << endl << "Empiezo yo jugador ! " << endl;
		numero=digitoAleatorio(); //Generamos el digito aleatorio del ordenador
		cout << "Yo pulso : " << numero << endl;
	}
	else{ //Empieza a jugar la persona
		cout << "Empiezas tu :)" << endl;
		mostrarTeclado();
		numero=digitoPersona();
	}

	while (numero!=ABANDONO && !final){
		suma=sumaNumeros(suma,numero);
		cout << "Suma : " << suma << endl;
		if (suma >= MAX_SUMA){ //Si la suma es mayor o igual a 31 se acaba el juego
			final=true; 
		}
		if (!final){
			if (jugador==MAQUINA){ //Juega la pesona
				numero=digitoPersona(numero);
				jugador=PERSONA; //El ultimo jugador seria la persona
			}
			else{ //Juega la maquina 
				numero=digitoAutomata(numero);
				jugador=MAQUINA; //El ultimo jugador seria la maquina
				cout << "Yo pulso : " << numero << endl;
			}
		}
	}

	if(numero==ABANDONO){
		jugador=ABANDONO;
	}
	return jugador;
}

// Funcion que devuelve true si cumple las reglas
bool digitoValido(int ultimo, int nuevo){
	return ((mismaFila(ultimo,nuevo) || mismaColumna(ultimo,nuevo)) && nuevo!=ultimo);
}

// Funcion que decide aleatoriamente quien empieza devuelve 1 si el automata y 2 si es el jugador
int quienEmpieza(){
	return ((rand()%2 )+1);
}

//Funcion que devuelve si nuevo esta en la misma fila que ultimo 
bool mismaFila(int ultimo, int nuevo){
	int filaUltimo, filaNuevo;
	filaUltimo= (ultimo- 1)/3;
	filaNuevo=(nuevo-1)/3;
	return filaUltimo==filaNuevo;
}

//Funcion que devuelve true si estan en la misma columna
bool mismaColumna(int ultimo, int nuevo){
	int columnaUltimo, columnaNuevo;
	columnaUltimo= (ultimo-1)%3;
	columnaNuevo=(nuevo-1)%3;
	return columnaUltimo==columnaNuevo;
}

//Funcion que genera un digito aleatorio entre 1 y 9
int digitoAleatorio(){
	return ((rand() % MAX_NUMERO) + 1 );
}

//Devuelve digito aleatorio que cumpla las normas
int digitoAutomata(int ultimo){
	int digito;
	digito=  digitoAleatorio();
	while (!digitoValido(ultimo,digito)){
		digito=  digitoAleatorio();
	}
	return digito;
}

// Pide un dígito al jugador. Devolverá un valor válido (entre 0 y 9).
int digitoPersona(){
	int digito;
	cout << "Introduce un digito (0 para abandonar) : ";
	cin >> digito;
	cin.sync();
	while ((digito < 0 || digito>9) || cin.fail()){
		cin.clear();
		cin.sync();
		cout << "Error, Introduce un digito (0 para abandonar) : ";
		cin >> digito;
	}
	return digito;
}

// Funcion que pide un digito al jugador mostrando el teclado 
int digitoPersona(int ultimo){
	int nuevo;
	mostrarTeclado();
	nuevo=digitoPersona();
	while (nuevo!=0 && !digitoValido(ultimo,nuevo)){
		cout << "Error: tiene que ser distinto de " << ultimo << " y estar en la misma fila o columna" << endl;
		mostrarTeclado();
		nuevo=digitoPersona();
	}
	return nuevo;
}

//Funcion que suma lo anterior con el nuevo numero
int sumaNumeros(int anterior, int nuevo){
	int suma;
	suma=anterior+nuevo;
	return suma;
}

//Funcion que muestra el teclado
void mostrarTeclado(){
	const int ESPACIO=8;
	cout << endl;
	for (int i=MAX_NUMERO; i>=1; i=i-3){
		cout << right << setw(ESPACIO)<<i-2 <<" "<<setw(ESPACIO)<< i-1 <<" " <<setw(ESPACIO)<< i << endl;
	}
}

//Funcion que pide los datos del usuario
string pedirDatos(){
	string nombre;
	cout << "Bienvenido a pasa la calculadora !" << endl;
	cout << "¿Como te llamas ? : ";
	getline(cin,nombre);
	cout << "Hola " << nombre << endl;
	return nombre;
}

//Funcion que muestra el menu y devuelve la opcion elegida
int menu(){
	int opcion=-1;
	cout <<"Selecciona una opcion : " << endl;
	cout <<"	1 - Jugar al nivel 1" << endl;
	cout <<"	2 - Acerca de Pasa la calculadora " << endl;
	cout <<"	0 - Salir " << endl;
	cout << "Opcion : ";
	cin >> opcion;
	while ((opcion<0) || (opcion >2) ||cin.fail()){
		cin.clear();
		cin.sync();
		cout << "Opcion incorrecta, Introduzca de nuevo la opcion : ";
		cin >> opcion ;
	}
	return opcion;
}

//Funcion que muestra el archivo de texto acerca de pasa la calculadora, devuelve true si se encuentra y false si no
bool mostrar(string nombArch){
	const string CENTINELA="XXX";
	ifstream archivo;
	bool encontrado;
	archivo.open(nombArch);
	if(archivo.is_open()){
		encontrado=true;
		while (getline(archivo,nombArch) && nombArch!=CENTINELA){ //LEEMOS EL ARCHIVO HASTA QUE EL STRING SEA CENTINELA
			cout << nombArch << endl;
		}
		archivo.close();
	}
	else{
		encontrado=false;
		cout << "No se ha podido encontrar el archivo " << endl;
	}
	return encontrado;
}

//Funcion que actualiza el archivo de informacion o lo crea si no existe
void actInforme(int jugadas, int ganadas, int abandonos){
	const string ARCH_INFORMACION="informePC.txt";
	int contador=0,total_jugadas,total_ganadas,total_abandonadas;
	string aux="auxiliar.txt"; 
	ifstream archExiste; //archivo de entrada
	ofstream archEscritura; //archivo de salida
	archExiste.open(ARCH_INFORMACION);
	if(archExiste.is_open()){ //Si el archivo existe leemos los datos 
		archExiste >> contador;
		archExiste >> total_jugadas;
		archExiste >> total_ganadas;
		archExiste >> total_abandonadas;

		//Abrimos un archivo auxiliar y escribimos los datos que hemos leido actualizados
		archEscritura.open(aux,ios::trunc);
		archEscritura << (contador++) << endl;
		archEscritura << (total_jugadas+jugadas) << endl;
		archEscritura << (total_ganadas+ganadas )<< endl;
		archEscritura << (total_abandonadas+abandonos) << endl;
		archExiste.close();
		archEscritura.close();
		copiarArchivo(aux,ARCH_INFORMACION); //Copiamos los datos del archivo auxiliar al de informacion
	}
	else{ //El archivo no existe y lo creamos 
		archEscritura.open(ARCH_INFORMACION);
		archEscritura << (contador+1) << endl;
		archEscritura << jugadas << endl;
		archEscritura << ganadas<< endl;
		archEscritura << abandonos << endl;
	}
}

//Funcion que copia un archivo origen en un archivo destino
void copiarArchivo(string ArchOrigen , string ArchDestino){
	int lectura;
	ifstream origen;
	ofstream destino;
	origen.open(ArchOrigen);
	if (origen.is_open()){
		origen >> lectura;
		destino.open(ArchDestino);
		while (!origen.eof()){
			destino << lectura << endl;
			origen >> lectura;
		}
		origen.close();
		destino.close();
	}		
}

