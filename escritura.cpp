#include <iostream>
#include <fstream>
using namespace std;

ofstream fout;    //Instancia de la clase iftream (escritura) para representar le archivo

void escritura(char * str){
    cout << "Ingrese caracteres: ";
    cin.getline(str, 256);
    fout.open("archivoprueba.txt",ios::ate);  //Abrir el archivo para escritura
    fout<<str;          //Escribir en el archivo
    fout.close();       //Cerrar el archivo
}
