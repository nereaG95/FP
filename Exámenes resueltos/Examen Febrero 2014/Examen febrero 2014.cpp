#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int NPO = 8;
const int NPNecesitados=4;
typedef struct{
	string denominacion;
	double cantidad;
	double precio;
}tProducto;

typedef tProducto tLista[NPO];
typedef struct{
	string denominacion;
	double cantidad;
}tProductoCompra;

typedef tProductoCompra tListaCompra[NPNecesitados];

int menu();
void cargar(tLista lista, bool &ok);
void leerCesta(tListaCompra lista);
int buscarProducto(tLista lista, string producto);
void realizarCompra(tLista lista, const tListaCompra listacompra);
void mostrarAgotados(const tLista lista);
void guardar(const tLista lista);

int main(){
	int opcion = 0;
	tLista lista;
	tListaCompra listacompra;
	bool ok;
	cargar(lista, ok);
	if (ok){
		while(opcion!=3){
			opcion=menu();
			switch(opcion){
			case 1:
				cout << endl;
				leerCesta(listacompra);
				realizarCompra(lista, listacompra);
			break;
			case 2:
				 mostrarAgotados(lista);
			}
		}
		guardar(lista);
	}
	else{
		cout << "Error al cargar el archivo. No existe."<< endl;
	}

	system("pause");
	return 0;
}
int menu(){
	int opcion=0;

	cout << "1.Realizar la compra de un pescadero." << endl;
	cout << "2.Visualizar los productos agotados." << endl;
	cout << "3. Salir." << endl;
	cout << "Selecciona una opcion: " << endl;
	cin >> opcion;
	while(opcion < 1 || opcion > 3 || cin.fail()){
		cin.sync();
		cin.clear();
		cout << "Error! Selecciona una opcion valida: ";
		cin >> opcion;
	}
	return opcion;
}
void cargar(tLista lista, bool &ok){
	ok=false;
	int i = 0;
	char aux;
	tProducto producto;
	ifstream archivo;
	archivo.open("almacen.txt");
	if(archivo.is_open()){
		ok = true;
		getline(archivo, producto.denominacion);
		while(producto.denominacion != "XXX" && i < NPO){
			archivo >> producto.cantidad >> producto.precio;
			archivo.get(aux);
			//Comprobamos que no se repita la denominacion
			lista[i]=producto;
			i++;
			getline(archivo, producto.denominacion);
		}
	}
	archivo.close();
}
void guardar(const tLista lista){
	ofstream archivo;
	archivo.open("almacen.txt");
	if (archivo.is_open()){
		for (int i=0;i < NPO; i++){
			archivo << lista[i].denominacion << endl;
			archivo << lista[i].cantidad << endl;
			archivo << lista[i].precio << endl;
		}
		archivo << "XXX" ;
	}
	archivo.close();
}
void leerCesta(tListaCompra lista){
	for (int i=0; i < NPNecesitados; i++){
		cout << "Producto que quieras comprar:";
		cin.ignore();
		getline(cin, lista[i].denominacion);
		cout << endl << "Que cantidad quieres comprar? ";
		cin >> lista[i].cantidad;
	}
}
int buscarProducto(tLista lista, string producto){
	int i=0, pos=0;
	bool encontrado = false;
	while(!encontrado && i < NPO){
		if (lista[i].denominacion == producto){
			encontrado = true;
			pos = i;
		}
		else{
			i++;
		}
	}
	if(!encontrado){
		pos=-1;
	}
	return pos;
}
void realizarCompra(tLista lista, const tListaCompra listacompra){
	int pos = 0;
	double totalPrecio=0;
	for (int i=0; i <NPNecesitados;i++){
		pos = buscarProducto(lista,listacompra[i].denominacion);
		if(pos >=0){
			if(listacompra[i].cantidad <= lista[pos].cantidad){
				lista[pos].cantidad = lista[pos].cantidad - listacompra[i].cantidad;
				totalPrecio = totalPrecio + (lista[pos].precio * listacompra[i].cantidad);
			}
			else{
				cout << "Cantidad de producto excesiva." << endl;
			}
		}
		else{
			cout << "No existe en el catalogo dicho producto." << endl;
		}
	}
	cout << "El precio total es: " << totalPrecio << endl;
}
void mostrarAgotados(const tLista lista){
	bool agotado = false;
	for (int i=0; i <NPO; i++){
		if(lista[i].cantidad ==0){
			agotado = true;
			cout << lista[i].denominacion << "esta agotado." << endl;
		}
	}
	if(!agotado){
		cout << "No hay productos agotados." << endl;
	}
}
