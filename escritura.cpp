#include <iostream>
#include <fstream>
using namespace std;

ofstream fout;    //Instancia de la clase iftream (escritura) para representar le archivo

void escritura(char * str)
{
    cin.ignore(1000, '\n');
    cout << "Ingrese el texto a modificar: "<<endl;
    cin.getline(str, 256);
    fout.open("archivo.txt",ios::app);  //Abrir el archivo para escritura
    fout<<str;          //Escribir en el archivo
    fout.close();       //Cerrar el archivo
}

void actualizarArchivo(string contenido) {
    fout.open("archivo.txt", ios::app); // Borra lo viejo y pone lo nuevo
    if (fout.is_open())
    {
        fout << contenido;
        fout.close();
        cout << "[Archivo actualizado con exito]" << endl;
    }
}
