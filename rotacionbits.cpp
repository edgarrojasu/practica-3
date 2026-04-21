#include <iostream>
#include <fstream>
#include <stdexcept>
#include "rotacionbits.h"
using namespace std;

unsigned char rotateLeft(unsigned char value, int shift)
{
    shift = shift % 8;
    if (shift == 0) return value;
    return (value << shift) | (value >> (8 - shift));
}

unsigned char rotateRight(unsigned char value, int shift)
{
    shift = shift % 8;
    if (shift == 0) return value;
    return (value >> shift) | (value << (8 - shift));
}

// Cifra in-place sobre char*: primero rotacion izquierda, luego XOR
void cifrarTexto(char* text, int n, char key)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        unsigned char c = (unsigned char)text[i];
        c = rotateLeft(c, n);
        c = c ^ (unsigned char)key;
        text[i] = (char)c;
    }
}

// Descifra in-place sobre char*: primero XOR, luego rotacion derecha
void descifrarTexto(char* text, int n, char key)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        unsigned char c = (unsigned char)text[i];
        c = c ^ (unsigned char)key;
        c = rotateRight(c, n);
        text[i] = (char)c;
    }
}

// Cifra un archivo en sitio: rotacion izquierda + XOR
void cifrarArchivoCombinado(const char* filename, int n, char key)
{
    ifstream fin(filename, ios::binary);
    if (!fin.is_open())
    {
        throw runtime_error("No se pudo abrir el archivo para cifrar");
    }

    char buffer[8192];
    int size = 0;
    char ch;
    while (fin.get(ch))
    {
        unsigned char c = (unsigned char)ch;
        c = rotateLeft(c, n);
        c = c ^ (unsigned char)key;
        buffer[size++] = (char)c;
    }
    fin.close();

    ofstream fout(filename, ios::out | ios::binary);
    if (!fout.is_open())
    {
        throw runtime_error("No se pudo escribir el archivo cifrado");
    }
    for (int i = 0; i < size; i++)
    {
        fout << buffer[i];
    }
    fout.close();
}

// Descifra un archivo en sitio: XOR + rotacion derecha
void descifrarArchivoCombinado(const char* filename, int n, char key)
{
    ifstream fin(filename, ios::binary);
    if (!fin.is_open())
    {
        throw runtime_error("No se pudo abrir el archivo para descifrar");
    }

    char buffer[8192];
    int size = 0;
    char ch;
    while (fin.get(ch))
    {
        unsigned char c = (unsigned char)ch;
        c = c ^ (unsigned char)key;
        c = rotateRight(c, n);
        buffer[size++] = (char)c;
    }
    fin.close();

    ofstream fout(filename, ios::out | ios::binary);
    if (!fout.is_open())
    {
        throw runtime_error("No se pudo escribir el archivo descifrado");
    }
    for (int i = 0; i < size; i++)
    {
        fout << buffer[i];
    }
    fout.close();
}
