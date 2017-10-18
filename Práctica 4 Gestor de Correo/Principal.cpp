#include<iostream>

#include"Correo.h"
#include"ListaCorreos.h"
#include"ListaRegistros.h"
#include"Usuario.h"
#include"ListaUsuarios.h"
#include"Gestor.h"

using namespace std;

/*Funcion que devuelve la opcion elegida del menu principal, es decir iniciar sesion, crear cuenta o salir */
int menuPrincipal();

int main(){
	tGestor gestor;
	bool entrada=true, arranca;
	int op=-1;
	arranca=arrancar(gestor, DOMINIO); //Arrancamos el gestor
	if(!arranca){
		cout << "La aplicacion comenzara con listas vacias " << endl;
	}
	//if(arrancar(gestor, DOMINIO)){ //Arrancamos el gestor
	do{
		op=menuPrincipal();
		system("cls");
		switch (op)
		{
		case 0:
			apagar(gestor);
			break;
		case 1:
			if(iniciarSesion(gestor)){
				ejecutarBandeja(gestor, entrada);
			}
			else{
				cout << "ERROR, el id de usuario o contraseña no son validos" <<endl << endl;
			}
			break;
		case 2:
			if(crearCuenta(gestor)){
				cout << "La cuenta se ha creado correctamente. Va a iniciar su primera sesion en " << DOMINIO << endl;
				system("pause");
				ejecutarBandeja(gestor,entrada);
			}
			else{
				cout << "Error, esta cuenta ya existe en el sistema" << endl;
			}
			break;
		default:
			break;
		}
	}while(op!=0);
	/*}
	else{ //Si no se ha podido arrancar, informamos del error
		cout << "Error, no se ha podido arrancar el gestor"<<endl;
	}-*/

	system("pause");
	return 0;
}


int menuPrincipal(){
	int op=-1;
	cout << "1- Iniciar Sesion" << endl;
	cout << "2- Crear nueva cuenta" << endl;
	cout << "0- Salir" << endl;
	do{
		cout << "Opcion : ";
		cin >> op;
	}while(op<0 || op>2);

	return op;
}
