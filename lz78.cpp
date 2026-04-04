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

void compressLZ78(const char* input) {
    Entry* dict = new Entry[1000]; // tamaño fijo simple
    int dictSize = 1; // índice 0 vacío

    int currentPrefix = 0;

    cout << "Salida (indice, caracter):\n";

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        int index = findEntry(dict, dictSize, currentPrefix, c);

        if (index != -1) {
            currentPrefix = index;
        } else {
            cout << "(" << currentPrefix << ", " << c << ")\n";

            dict[dictSize].prefix = currentPrefix;
            dict[dictSize].c = c;
            dictSize++;

            currentPrefix = 0;
        }
    }

    delete[] dict;
}

