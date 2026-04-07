#include <iostream>
using namespace std;

struct Entry {
    int prefix;
    char c;
};

// Buscar si (prefijo, carácter) ya existe
int findEntry(Entry* dict, int size, int prefix, char c) {
    for (int i = 1; i < size; i++) {
        if (dict[i].prefix == prefix && dict[i].c == c) {
            return i;
        }
    }
    return -1;
}

string compressLZ78(const char* input) {
    Entry* dict = new Entry[1000];
    int dictSize = 1;
    int currentPrefix = 0;

    // Aquí acumularemos el resultado en lugar de usar cout
    string resultado = "";

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        int index = findEntry(dict, dictSize, currentPrefix, c);

        if (index != -1) {
            currentPrefix = index;
        } else {
            // Construimos la cadena: (prefijo, caracter)
            resultado += "(";
            resultado += to_string(currentPrefix);
            resultado += ", ";
            resultado += c;
            resultado += ") ";

            // Guardamos en el diccionario
            dict[dictSize].prefix = currentPrefix;
            dict[dictSize].c = c;
            dictSize++;

            currentPrefix = 0;
        }
    }

    delete[] dict;
    return resultado; // Devolvemos la cadena completa
}

