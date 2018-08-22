#include<iostream>
#include<string>
#include<stdlib.h>
#include<iomanip>
#include<fstream>
using namespace std;
const int NUM=10;
struct Libro{
	int clave;
	string Titulo;
	string Autor;
	string Resumen;
	double Precio;
};
Libro libro[NUM];
string reemplazarEspacios(string);
string reemplazarSharp(string);
void insertar(int, string, string, string, double);
void mostrarDatos();
void escribirEnArchivo();
void recuperarDeArchivo();
void pedirDatos();
void inicializar();
int buscarLugarVacio();
void menu();
int main(){
	inicializar();

	int opcion;
	do{
		menu();
		cin>>opcion;
		switch(opcion){
			case 1:
				pedirDatos();
				escribirEnArchivo();
				break;
			case 2:
				mostrarDatos();
				break;
			case 3:
				break;
			default:
				cout<<"Opcion no valida"<<"\n";
				break;
		}
	}while(opcion!=3);
	return 0;
}
void menu(){
	cout<<"\n         DATOS PERSONALES"<<"\n";
	cout<<"    ELIGE TU OPCION"<<"\n";
	cout<<"1.-  ALTA DE LIBROS"<<"\n";
	cout<<"2.-  REPORTE GENERAL"<<"\n";
	cout<<"3.-  SALIR"<<"\n";
}
void pedirDatos(){
	int clavex;
	string Titulox;
	string Autorx;
	string Resumenx;
	double Preciox;
	cout<<"Escribe datos del libro."<<"\n";
	cout<<"Dame clave:";
	cin>>clavex;
	cout<<"Dame Titulo:";
	getline(cin, Titulox);
	getline(cin, Titulox);
	cout<<"\nDame Autor:";
	getline(cin, Autorx);
	cout<<"\nDame Resumen:";
	getline(cin, Resumenx);
	cout<<"\nDame costo del libro:";
	cin>>Preciox;
	insertar(clavex, Titulox, Autorx, Resumenx, Preciox);
}
string reemplazarEspacios(string texto){
	for(int i=0; i<(int)texto.length(); ++i){
		if(texto[i]==' '){
			texto.replace(i, 1, "#");
		}
	}
	return texto;
}
string reemplazarSharp(string texto){
	for(int i=0; i<(int) texto.length(); ++i) {
		if(texto[i]=='#'){
			texto.replace(i, 1, " ");
		}
	}
	return texto;
}
void insertar(int clavex, string Titulox, string Autorx, string Resumenx,
 double Preciox){
	int lugarVacio = buscarLugarVacio();
	if(lugarVacio == -1){
		cout<<"Ya no hay lugar"<<"\n";
		return;
	}
	libro[lugarVacio].clave=clavex;
	libro[lugarVacio].Titulo=Titulox;
	libro[lugarVacio].Autor=Autorx;
	libro[lugarVacio].Resumen=Resumenx;
	libro[lugarVacio].Precio=Preciox;
}
void mostrarDatos() {
	cout<<endl;
	cout<< setw(6)<<"CLAVE"
			<<setw(20)<<"Titulo"
			<<setw(15)<<"Autor"
			<<setw(15)<<"Resumen"
			<<setw(7)<<"Precio"<<"\n";
	for(int i=0; i<NUM; i++){
		if(libro[i].clave !=0){
			cout<<setw(6)<<libro[i].clave
					<<setw(20)<< libro[i].Titulo
					<<setw(15)<<libro[i].Autor
					<<setw(15)<<libro[i].Resumen
					<<setw(7)<<libro[i].Precio<<"\n";
		}
	}
system.pause();
}
void recuperarDeArchivo(){
	ifstream lecturaArchivo("libro.txt", ios::in);
	if(!lecturaArchivo){
		cerr<<"No se puede abrir el arhivo"<<"\n";
		exit(1);
	}
	int clavex;
	string Titulox;
	string Autorx;
	string Resumenx;
	double Preciox;
	while(lecturaArchivo >> clavex >> Titulox >> Autorx >>
	Resumenx >> Preciox){
		insertar(clavex, reemplazarSharp(Titulox),
		reemplazarSharp(Autorx),
		reemplazarSharp(Resumenx), Preciox);
	}
}
void escribirEnArchivo(){
	ofstream salidaArchivo("libro.txt", ios::out);
	if(!salidaArchivo){
		cerr<<"EL DOCUMENTO NO PUEDE ABRISE "<<"\n";
		exit(1);
	}
	for (int i=0; i<NUM; i++){
		if(libro[i].clave !=0){
			salidaArchivo<< libro[i].clave<<' '
					<< reemplazarEspacios(libro[i].Titulo)<<' '
					<< reemplazarEspacios(libro[i].Autor)<<' '
					<< reemplazarEspacios(libro[i].Resumen)<<' '
					<< libro[i].Precio<< ' '<<"\n";
		}
	}
}
void inicializar () {
	for(int i=0; i<NUM; i++) {
		libro[i].clave=0;
		libro[i].Titulo="";
		libro[i].Autor="";
		libro[i].Resumen="";
		libro[i].Precio=0;
	}
}
int buscarLugarVacio() {
	for(int i=0; i<NUM; i++){
		if(libro[i].clave==0){
			return i;
		}
	}
	return -1;
}
