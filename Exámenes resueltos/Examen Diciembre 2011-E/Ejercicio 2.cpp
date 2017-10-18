#include <iostream>
#include <fstream>
using namespace std;


int main(){
	ifstream arch;
	int num, par=0;
	arch.open("fibo.txt");
	if(arch.is_open()){
		arch >> num;
		while (num!=-1){
			if (num%2==0){
				par++;
			}
			arch >> num;
		}
		arch.close();
	}
	cout << " Hay " << par <<" numeros pares" << endl;
	system("pause");
	return 0;
}