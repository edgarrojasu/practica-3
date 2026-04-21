#include <iostream>
#include <fstream>
#include <stdexcept>
#include "lectura.h"
#include "escritura.h"
#include "rle.h"
#include "rotacionbits.h"
#include "lz78.h"
#include "generales.h"
using namespace std;

ofstream ofst;

int main()
{
    int elecc;
    char texto[1024];
    char cifradoBuf[1024];
    const char key = 'k';

    try
    {
        elecc = rleolz78();
        int n = askN();

        leerArchivoABuffer("entrada.txt", texto, 1024);
        cout << "Texto leido: " << texto << endl;

        ofst.open("archivo.txt", ios::out);
        if (!ofst.is_open())
        {
            throw runtime_error("No se pudo abrir archivo.txt para escritura");
        }
        ofst << "Texto original:\n" << texto << "\n";
        ofst.close();

        if (elecc == 1)
        {
            string comprimido = rleCompressPtr(texto);

            ofst.open("archivo.txt", ios::app);
            if (!ofst.is_open()) throw runtime_error("Error al abrir archivo.txt");
            ofst << "\nTexto comprimido (RLE):\n" << comprimido << "\n";
            ofst.close();

            int len = 0;
            while (comprimido[len] != '\0') len++;
            for (int i = 0; i <= len; i++)
            {
                cifradoBuf[i] = comprimido[i];
            }

            cifrarTexto(cifradoBuf, n, key);

            ofst.open("archivo.txt", ios::app);
            if (!ofst.is_open()) throw runtime_error("Error al abrir archivo.txt");
            ofst << "\nTexto cifrado (rotacion " << n << " bits + XOR clave '" << key << "'):\n"<< cifradoBuf << "\n";
            ofst.close();

            descifrarTexto(cifradoBuf, n, key);

            ofst.open("archivo.txt", ios::app);
            if (!ofst.is_open()) throw runtime_error("Error al abrir archivo.txt");
            ofst << "\nTexto descifrado (XOR + rotacion inversa):\n" << cifradoBuf << "\n";
            ofst.close();

            string descomprimido = rleDecompress(cifradoBuf);

            ofst.open("archivo.txt", ios::app);
            if (!ofst.is_open()) throw runtime_error("Error al abrir archivo.txt");
            ofst << "\nTexto descomprimido:\n" << descomprimido << "\n";
            ofst.close();

            cout << "Proceso completado. Resultados en archivo.txt" << endl;
        }
        else
        {
            ofstream limpiar("comprimido.txt", ios::out);
            if (!limpiar.is_open()) throw runtime_error("No se pudo crear comprimido.txt");
            limpiar.close();

            ofst.open("archivo.txt", ios::app);
            if (!ofst.is_open()) throw runtime_error("Error al abrir archivo.txt");
            ofst << "\nTexto comprimido (LZ78):\n";
            ofst.close();
            compressLZ78(texto);

            cifrarArchivoCombinado("comprimido.txt", n, key);

            ofst.open("archivo.txt", ios::app);
            if (!ofst.is_open()) throw runtime_error("Error al abrir archivo.txt");
            ofst << "\nTexto cifrado (rotacion " << n << " bits + XOR clave '" << key << "'):\n";
            ofst.close();
            copiarContenidoArchivo("comprimido.txt");

            descifrarArchivoCombinado("comprimido.txt", n, key);

            ofst.open("archivo.txt", ios::app);
            if (!ofst.is_open()) throw runtime_error("Error al abrir archivo.txt");
            ofst << "\nTexto descifrado (XOR + rotacion inversa):\n";
            ofst.close();
            copiarContenidoArchivo("comprimido.txt");

            ofst.open("archivo.txt", ios::app);
            if (!ofst.is_open()) throw runtime_error("Error al abrir archivo.txt");
            ofst << "\nTexto descomprimido:\n";
            ofst.close();
            decompressLZ78("comprimido.txt");

            cout << "Proceso completado. Resultados en archivo.txt" << endl;
        }
    }
    catch (const runtime_error& e)
    {
        cerr << "Error de ejecucion: " << e.what() << endl;
        return 1;
    }
    catch (const exception& e)
    {
        cerr << "Error inesperado: " << e.what() << endl;
        return 1;
    }

    return 0;
}

