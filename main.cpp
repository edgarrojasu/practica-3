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

int main()
{
    int elecc;
    char texto[100];
    char key;
    char ñ = 164;
    string compresTextRLE;

    elecc = rleolz78();

    ofst.open("archivo.txt", ios::out);
    if (ofst.is_open())
    {
        ofst << "Texto original: " << endl;
        ofst.close();
    }

    escritura(texto);

    if (elecc == 1)
    {
        compresTextRLE = rleCompressPtr(texto);
        ofst.open("archivo.txt", ios::app);
        ofst << "\nTexto comprimido (RLE):\n";
        ofst.close();
        actualizarArchivo(compresTextRLE.c_str());
    }
    else
    {
        ofst.open("archivo.txt", ios::app);
        ofst << "\nTexto comprimido (LZ78):\n";
        ofst.close();

        compressLZ78(texto);
    }

    cout<<"Ingrese una contrase"<<ñ<<"a para cifrar el texto: ";
    cin>>key;

    xorCipherPtr(texto,key);
    ofst.open("archivo.txt", ios::app);
    ofst << "\n\nTexto cifrado:\n";
    ofst.close();

    actualizarArchivo(texto);

    system ("cls");
    //cout<<texto<<endl;  //imprimir texto en la terminal

    cout<<"Ingrese la contrase"<<ñ<<"a del cifrado: ";
    cin>>key;

    xorCipherPtr(texto,key);
    ofst.open("archivo.txt", ios::app);
    ofst << "Texto comprimido descifrado:\n";
    ofst.close();

    actualizarArchivo(texto);

    //cout<<texto<<endl;  //imprimir texto en la terminal

    if (elecc == 1)
    {

    }
    else
    {
        decompressLZ78("comprimido.txt");
    }

    ofst.open("archivo.txt", ios::app);
    ofst << "\n\nTexto descomprimido descifrado:\n";
    ofst.close();

    actualizarArchivo(texto);

    return 0;
}
