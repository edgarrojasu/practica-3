#include <iostream>
#include <fstream>
using namespace std;

ofstream fout;    //Instancia de la clase iftream (escritura) para representar le archivo

void escritura(char * str)
{
    cin.ignore(1000, '\n');
    cout << "Ingrese el texto a modificar: "<<endl;
    cin.getline(str, 256);
    fout.open("archivo.txt",ios::ate);  //Abrir el archivo para escritura
    fout<<str;          //Escribir en el archivo
    fout.close();       //Cerrar el archivo
}

void actualizarArchivo(const char* contenido)
{
    fout.open("archivo.txt", ios::app);
    if (fout.is_open())
    {
        fout << contenido << endl;
        fout.close();
    }
}
