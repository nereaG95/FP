#include<iostream>
#include<vld.h>

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
	bool entrada=true, arranca, lleno;
	int op=-1;
	arranca=arrancar(gestor, DOMINIO); //Arrancamos el gestor
	if(!arranca){
		cout << "La aplicacion comenzara con listas vacias " << endl;
	}

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
			if(crearCuenta(gestor, lleno) && !lleno){
				cout << "La cuenta se ha creado correctamente. Va a iniciar su primera sesion en " << DOMINIO << endl;
				system("pause");
				ejecutarBandeja(gestor,entrada);
			}
			else if (lleno){
				cout << "No se ha podido crear cuenta, porque la lista de usuarios esta llena" << endl;
			}
			else{
				cout << "Error, esta cuenta ya existe en el sistema" << endl;
			}
			break;
		default:
			break;
		}
	}while(op!=0);

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