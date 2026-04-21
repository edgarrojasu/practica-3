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
    fout<<str<<"\n";          //Escribir en el archivo
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

// Cifra/descifra un archivo completo con XOR
void cifrarArchivo(const char* filename, char key)
{
    ifstream fin(filename, ios::binary);
    char buffer[4096];
    int size = 0;
    char ch;
    while (fin.get(ch))
    {
        buffer[size++] = ch ^ key;
    }
    fin.close();

    ofstream fout(filename, ios::out);
    for (int i = 0; i < size; i++)
    {
        fout << buffer[i];
    }
    fout.close();
}

// Copia el contenido de un archivo a archivo.txt
void copiarContenidoArchivo(const char* filename)
{
    ifstream fin(filename);
    ofstream fout("archivo.txt", ios::app);
    char ch;
    while (fin.get(ch))
    {
        fout << ch;
    }
    fin.close();
    fout.close();
}
