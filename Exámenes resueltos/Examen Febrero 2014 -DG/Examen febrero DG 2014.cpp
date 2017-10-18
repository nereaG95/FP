#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int NP=10;
typedef enum{papeleria, alimentacion, limpieza, informatica}tClase;

typedef struct{
	string CIF;
	tClase clase;
	int numPedidos;
	double totalPedidos;
}tProvedor;


typedef double tGastos[4];
typedef tProvedor tLista[NP];

int menu();
tClase numToClase(int num);
int tClaseToNum(tClase clase);
void cargarArchivo(bool &ok, tLista listaProvedores);
void guardarArchivo(const tLista listaProvedores);
int buscarProvedor( const tLista listaProvedores, string CIF);
void nuevoPedido(tLista listaProvedores, string CIF, int euros);
void mostrarProvedor(tProvedor provedor);
void mostrarClases(const tGastos gasto);
void mostrarXInteralo(const tLista listaProvedor, int Max, int Min);
string enumToString(tClase clase);
void totalesXClase(const tLista listaProvedores, tGastos listaGastos);


int main(){
	tLista listaProvedores;
	tGastos gastos;
	string CIF;
	bool ok;
	int op, euros, min , max;
	cargarArchivo(ok,listaProvedores);
	for(int i=0; i<NP; i++){
		cout << listaProvedores[i].CIF << " " << enumToString(listaProvedores[i].clase) << " " << listaProvedores[i].numPedidos << " " << listaProvedores[i].totalPedidos << endl;
	}
	if (ok){
		do {
			op=menu();
			switch (op)
			{
			case 1:
				cout << "Introduzca el CIF del provedor : ";
				cin >> CIF;
				if (buscarProvedor(listaProvedores, CIF) >=0){
					cout << "Introduzca una cantidad de euros ";
					cin >> euros;
					nuevoPedido(listaProvedores, CIF, euros);
				}
				break;
			case 2:
				cout << " MOSTRAR PROVEDORRES POR INTERVALO  ";
				cout << "Introduce el min intervalo : ";
				cin >> min;
				cout << "Introduce el max intervalo : ";
				cin >> max;
				mostrarXInteralo(listaProvedores,max,min);
				break;
			case 3:
				totalesXClase(listaProvedores,gastos);
				mostrarClases(gastos);
				break;
			default:
				break;
			}
		}while (op!=0);
		guardarArchivo(listaProvedores);
	}
	else{
		cout << "No se ha podido cargar el archivo " << endl;
	}
	system("pause");
	return 0;
}

string enumToString(tClase clase){
	string cla;
	if (clase== papeleria){
		cla="Papeleria";
	}
	else if (clase == alimentacion){
		cla="Alimentacion";
	}
	else if (clase == informatica){
		cla="Informatica";
	}
	else if (clase== limpieza){
		cla="Limpieza ";
	}
	return cla;
}


tClase numToClase(int num){
	tClase clas;
	if (num==0){
		clas=papeleria;
	}
	else if (num==1){
		clas=alimentacion;
	}
	else if (num==2){
		clas=limpieza;
	}
	else if (num==3){
		clas=informatica;
	}
	return clas;
}

int tClaseToNum(tClase clase){
	int num;
	if (clase==papeleria){
		num=0;
	}
	else if (clase == alimentacion){
		num=1;
	}
	else if (clase == limpieza){
		num=2;
	}
	else if (clase == informatica){
		num=3;
	}
	return num;
}


void totalesXClase(const tLista listaProvedores, tGastos listaGastos){
	for (int j=0; j<4;j++){
		listaGastos[j]=0;
	}
	for (int i=0; i<NP;i++){
		listaGastos[tClaseToNum(listaProvedores[i].clase)]+= listaProvedores[i].totalPedidos;
	}
}

void mostrarClases(const tGastos gasto){
	for (int i=0; i < 4; i++){
		cout  << left << setw(12) <<  enumToString(numToClase(i)) << "   " << right << setw(10)<< fixed << setprecision(2) <<gasto[i] << " Euros " << endl;
	}
}



void mostrarXInteralo(const tLista listaProvedor, int Max, int Min){
	for (int i=Min; i<=Max; i++){
		mostrarProvedor(listaProvedor[i]);
	}
}

void mostrarProvedor(tProvedor provedor){
	cout <<left << provedor.CIF << "  " << setw (12) << enumToString(provedor.clase) << "    ";
	cout << setw(3)  << provedor.numPedidos << "     "  << setw(10) << provedor.totalPedidos << endl;
}

void guardarArchivo(const tLista listaProvedores){
	ofstream archivo;
	archivo.open("provedores.txt");
	for (int i=0; i < NP; i++){
		archivo << listaProvedores[i].CIF << " " << tClaseToNum(listaProvedores[i].clase) << " " ;
		archivo << listaProvedores[i].numPedidos << " " << listaProvedores[i].totalPedidos << endl;
	}
	archivo.close();	
}

void cargarArchivo(bool &ok, tLista listaProvedores){
	ifstream archivo;
	string CIF;
	ok=false;
	int contador=0, clase;
	tProvedor provedor;
	archivo.open("provedores.txt");
	if (archivo.is_open()){
		archivo >> CIF;
		while (CIF!="X" && contador < NP){
			provedor.CIF=CIF;
			archivo >> clase >> provedor.numPedidos >> provedor.totalPedidos;
			provedor.clase=numToClase(clase);
			listaProvedores[contador]=provedor;
			contador++;
			archivo >> CIF;
		}
		if (contador ==NP){
			ok=true;;
		}
		archivo.close();
	}
}

int buscarProvedor( const tLista listaProvedores, string CIF){
	int pos=0;
	bool encontrado=false;
	while (!encontrado && pos < NP){
		if (listaProvedores[pos].CIF==CIF){
			encontrado=true;
		}
		else{
			pos++;
		}
	}
	if(!encontrado){
		pos=-1;
	}
	return pos;
}

void nuevoPedido(tLista listaProvedores, string CIF, int euros){
	int pos=buscarProvedor(listaProvedores, CIF);
	if (pos >=0){ //Se ha encontrado el provedor
		listaProvedores[pos].numPedidos++;
		listaProvedores[pos].totalPedidos=listaProvedores[pos].totalPedidos+euros;
	}
}

int menu(){
	int op;
	cout << "1-Nuevo Pedido"<< endl;
	cout << "2-Proveedores con numero de pedidos en un intervalo " << endl;
	cout << "3- Gastos por clase de provedor " << endl;
	cout <<"0-Salir " << endl;
	cout << "Opcion : ";
	cin >> op;
	while (op <0 || op >3){
		cout << "Error, nueva op : " ;
		cin >> op;
	}
	return op;
}