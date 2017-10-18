#include <iostream>
using namespace std;

int main(){
	int num, mayor=0;
	bool esCreciente=true;
	cout << "Introduce una secuencia : ";
	cin >> num;
	while (num !=0){
			if (num >= mayor && esCreciente){
				mayor=num;
			}
			else{
				esCreciente=false;
			}
		cout << "Introduce un numero : ";
		cin >> num;
	}

	if (esCreciente){
		cout << "La secuencia es Creciente " << endl;
	}
	else{
		cout << "La secuencia no es Creciente " << endl;
	}
	system("pause");
	return 0;
}