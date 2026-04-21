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
    char texto[1024];          // buffer para el texto leido del archivo
    char cifradoBuf[1024];     // buffer para el texto cifrado (char[], sin string)
    const char key = 'k';      // clave XOR predeterminada

    try
    {
        // 1. Elegir metodo de compresion
        elecc = rleolz78();

        // 2. Pedir n para la rotacion de bits
        int n = askN();

        // 3. Leer el texto desde el archivo de entrada
        leerArchivoABuffer("entrada.txt", texto, 1024);
        cout << "Texto leido: " << texto << endl;

        // 4. Iniciar archivo.txt limpio con el texto original
        ofst.open("archivo.txt", ios::out);
        if (!ofst.is_open())
        {
            throw runtime_error("No se pudo abrir archivo.txt para escritura");
        }
        ofst << "Texto original:\n" << texto << "\n";
        ofst.close();

        if (elecc == 1)
        {
            // ── RLE ────────────────────────────────────────────────────────────
            // string PERMITIDO solo aqui (compresion RLE)
            string comprimido = rleCompressPtr(texto);

            ofst.open("archivo.txt", ios::app);
            if (!ofst.is_open()) throw runtime_error("Error al abrir archivo.txt");
            ofst << "\nTexto comprimido (RLE):\n" << comprimido << "\n";
            ofst.close();

            // Copiar el texto comprimido a un char[] para cifrar sin usar string
            int len = 0;
            while (comprimido[len] != '\0') len++;
            for (int i = 0; i <= len; i++)
            {
                cifradoBuf[i] = comprimido[i];
            }

            // Cifrar in-place sobre char[] (rotacion + XOR): NO se usa string aqui
            cifrarTexto(cifradoBuf, n, key);

            ofst.open("archivo.txt", ios::app);
            if (!ofst.is_open()) throw runtime_error("Error al abrir archivo.txt");
            ofst << "\nTexto cifrado (rotacion " << n << " bits + XOR clave '" << key << "'):\n"
                 << cifradoBuf << "\n";
            ofst.close();

            // Descifrar in-place sobre el mismo char[] (XOR + rotacion inversa)
            descifrarTexto(cifradoBuf, n, key);

            ofst.open("archivo.txt", ios::app);
            if (!ofst.is_open()) throw runtime_error("Error al abrir archivo.txt");
            ofst << "\nTexto descifrado (XOR + rotacion inversa):\n" << cifradoBuf << "\n";
            ofst.close();

            // Descomprimir RLE — string permitido porque es parte del modulo RLE
            string descomprimido = rleDecompress(cifradoBuf);

            ofst.open("archivo.txt", ios::app);
            if (!ofst.is_open()) throw runtime_error("Error al abrir archivo.txt");
            ofst << "\nTexto descomprimido:\n" << descomprimido << "\n";
            ofst.close();

            cout << "Proceso completado. Resultados en archivo.txt" << endl;
        }
        else
        {
            // ── LZ78 ───────────────────────────────────────────────────────────
            // Limpiar comprimido.txt
            ofstream limpiar("comprimido.txt", ios::out);
            if (!limpiar.is_open()) throw runtime_error("No se pudo crear comprimido.txt");
            limpiar.close();

            // Comprimir: guarda los pares en archivo.txt y en comprimido.txt
            ofst.open("archivo.txt", ios::app);
            if (!ofst.is_open()) throw runtime_error("Error al abrir archivo.txt");
            ofst << "\nTexto comprimido (LZ78):\n";
            ofst.close();
            compressLZ78(texto);

            // Cifrar comprimido.txt en sitio (rotacion + XOR) y volcar a archivo.txt
            cifrarArchivoCombinado("comprimido.txt", n, key);

            ofst.open("archivo.txt", ios::app);
            if (!ofst.is_open()) throw runtime_error("Error al abrir archivo.txt");
            ofst << "\nTexto cifrado (rotacion " << n << " bits + XOR clave '" << key << "'):\n";
            ofst.close();
            copiarContenidoArchivo("comprimido.txt");

            // Descifrar comprimido.txt en sitio (XOR + rotacion inversa) y volcar a archivo.txt
            descifrarArchivoCombinado("comprimido.txt", n, key);

            ofst.open("archivo.txt", ios::app);
            if (!ofst.is_open()) throw runtime_error("Error al abrir archivo.txt");
            ofst << "\nTexto descifrado (XOR + rotacion inversa):\n";
            ofst.close();
            copiarContenidoArchivo("comprimido.txt");

            // Descomprimir LZ78 y volcar resultado a archivo.txt
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

