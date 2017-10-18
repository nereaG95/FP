#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main(){
	const int DESCUENTO=15;
	const int IVA =21;
	string nombre, nif, producto, direccion;
	double precio, precioTotal, precioDescuento, totalDescuento, precioIva, precioFinal;
	int unidades;
	char descuento;

	do{
		cin.clear();
		//cin.sync();
		cout << "Precio del producto : ";
		cin >> precio;
	}while(cin.fail());
	do{
		//cin.clear(); cin.sync();
		cout << "Unidades : ";
		cin >> unidades; 
	}while(cin.fail());
	
	cout << "Descuento (s/n) : ";
	cin >> descuento;
	cin.sync();
	cout << "Nombre del cliente : ";
	getline(cin, nombre);
	cout << "NIF del cliente : " ;
	getline(cin,nif);
	cout << "Direccion del cliente : ";
	getline(cin,direccion);
	cout << "Nombre del producto : ";
	getline(cin, producto);
	
	cout << endl;
	cout <<"Factura :" << endl;
	cout <<setw(70) << right << nombre << endl;
	cout <<setw(70) << direccion<< endl;
	cout << setw(70) << nif<<endl;
	cout << endl << "Producto : " << producto << endl;
	cout << "Precio unitario " << endl;
	cout << setw(70) <<  fixed << setprecision (2) << precio << endl;
	cout << "Unidades " << endl;
	cout << setw(70) << fixed <<  setprecision (2) << unidades << endl;
	precioTotal= precio*unidades;
	cout << "Total  " << endl;
	cout << setw(70) << setprecision (2) << precioTotal << endl;

	if (descuento == 's' || descuento == 'S'){
		precioDescuento = (precioTotal*DESCUENTO)/100;
	}
	else {
		precioDescuento = 0;
	}
		cout << "Descuento (15%)" << endl;
		cout << setw (70) << fixed <<  setprecision (2) << -precioDescuento << endl;
		cout << "Total tras desdscuento  "<< endl;
		totalDescuento=precioTotal-precioDescuento;
		cout << setw(70) <<right << fixed << setprecision (2) <<totalDescuento << endl;
		precioIva= (totalDescuento*IVA)/100;
		cout <<"I.V.A (21%)  " << endl;
		cout << setw(70) << right << fixed << setprecision (2) << precioIva << endl;
		precioFinal=totalDescuento+precioIva;
		cout << "Precio Final  " << endl;
		cout << setw(70) << right << fixed << setprecision (2) << precioFinal << endl;

	system("pause");
	return 0;
}