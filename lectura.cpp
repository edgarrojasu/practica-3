#include <iostream>
#include <fstream>
#include <stdexcept>
#include "lectura.h"
using namespace std;

void leerArchivoABuffer(const char* filename, char* buffer, int maxLen)
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        throw runtime_error("No se pudo abrir el archivo de entrada");
    }
    int i = 0;
    char ch;
    while (fin.get(ch) && i < maxLen - 1)
    {
        if (ch == '\n') break;
        buffer[i++] = ch;
    }
    buffer[i] = '\0';
    fin.close();
}

ifstream abrirArchivo(const char* nombre)
{
    ifstream fin(nombre);
    if (!fin.is_open())
    {
        throw runtime_error("No se pudo abrir el archivo");
    }
    return fin;
}

void lecturalinea(ifstream& instancia)
{
    char linea[1024];
    while (instancia.getline(linea, 1024))
    {
        cout << linea << endl;
    }
}

void lecturachar(ifstream& instancia)
{
    char letra;
    while (instancia.good())
    {
        letra = instancia.get();
        if (instancia.good())
        {
            if (letra != '\n')
                cout << letra;
            else
                cout << endl;
        }
    }
}

