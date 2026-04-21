#ifndef LECTURA_H
#define LECTURA_H

#include <fstream>
using namespace std;

void leerArchivoABuffer(const char* filename, char* buffer, int maxLen);

ifstream abrirArchivo(const char* nombre);
void lecturalinea(ifstream& instancia);
void lecturachar(ifstream& instancia);

#endif // LECTURA_H
