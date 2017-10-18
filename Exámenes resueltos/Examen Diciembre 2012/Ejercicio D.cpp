#include <iostream>
#include <fstream>
using namespace std;

int invertir(int numero);

int main(){
	ifstream in;
	ofstream out;
	int num;
	in.open("input.txt");
	if(in.is_open()){
		in >> num;
		out.open("out.txt");
		while (num !=0){
			if (num>0){
				out << invertir(num) << endl;
			}
			in >> num;
		}
		out.close();
		in.close();
	}
	system("pause");
	return 0;
}

int invertir(int numero){
	int invertido=0,num;
	while (numero > 0){
		num=numero%10;
		invertido=(invertido*10)+num;
		numero=numero/10;
	}
	return invertido;
}

