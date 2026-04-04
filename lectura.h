#ifndef LECTURA_H
#define LECTURA_H

#include <fstream>
using namespace std;

string lecturalinea(ifstream instancia);
void lecturachar(ifstream instancia);
ifstream leer_archiv(string nombre_archivo);

#endif // LECTURA_H
