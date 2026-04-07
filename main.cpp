#include <iostream>
#include "lectura.h"
#include "escritura.h"
#include "rle.h"
#include "rotacionbits.h"
#include <bitset>
#include "xor.h"
#include "lz78.h"
#include "generales.h"
#include <fstream>
#include <iostream>
using namespace std;

ofstream ofst;

int main(){

    int elecc;
    char texto[100];
    string compresText;

    elecc = rleolz78();

    ofst.open("archivo.txt", ios::ate);
    if (ofst.is_open())
    {
        ofst << "Texto original:"<<endl;
        ofst.close();
    }
    else
    {
        cout<<"archivo no encontrado";
    }

    escritura(texto);


    if (elecc == 1)
    {
        compresText = rleCompressPtr(texto);
        ofst.open("archivo.txt", ios::app);
        if (ofst.is_open())
        {
            ofst <<"\n"<<"\n"<< "Texto comprimido (RLE):"<<"\n";
            ofst.close();
        }
        else
        {
            cout<<"archivo no encontrado";
        }
        actualizarArchivo(compresText);
    }
    else
    {
        compresText = compressLZ78(texto);
        ofst.open("archivo.txt", ios::app);
        if (ofst.is_open())
        {
            ofst <<"\n"<<"\n"<< "Texto comprimido (LZ78):"<<"\n";
            ofst.close();
        }
        else
        {
            cout<<"archivo no encontrado";
        }
        actualizarArchivo(compresText);
    }
    return 0;
}
