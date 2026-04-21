#include <iostream>
#include <fstream>
#include <stdexcept>
#include "lz78.h"
using namespace std;

struct Entry
{
    int prefix;
    char c;
};

Entry* growDict(Entry* dict, int& capacity)
{
    int newCap = capacity * 2;
    Entry* newDict = new Entry[newCap];
    for (int i = 0; i < capacity; i++)
    {
        newDict[i] = dict[i];
    }
    delete[] dict;
    capacity = newCap;
    return newDict;
}

int findEntry(Entry* dict, int size, int prefix, char c)
{
    for (int i = 1; i < size; i++)
    {
        if (dict[i].prefix == prefix && dict[i].c == c) return i;
    }
    return -1;
}

void compressLZ78(const char* input)
{
    int capacity = 256;
    Entry* dict = new Entry[capacity];
    int dictSize = 1;
    int currentPrefix = 0;

    ofstream fout;
    fout.open("archivo.txt", ios::app);
    if (!fout.is_open())
    {
        throw runtime_error("Error al abrir archivo.txt en compressLZ78");
    }

    ofstream fcomp;
    fcomp.open("comprimido.txt", ios::out);
    if (!fcomp.is_open())
    {
        throw runtime_error("Error al abrir comprimido.txt en compressLZ78");
    }

    for (int i = 0; input[i] != '\0'; i++)
    {
        char c = input[i];
        int index = findEntry(dict, dictSize, currentPrefix, c);

        if (index != -1)
        {
            currentPrefix = index;
        }
        else
        {
            fout  << "(" << currentPrefix << "," << c << ") ";
            fcomp << "(" << currentPrefix << "," << c << ") ";

            if (dictSize >= capacity)
            {
                dict = growDict(dict, capacity);
            }
            dict[dictSize].prefix = currentPrefix;
            dict[dictSize].c = c;
            dictSize++;
            currentPrefix = 0;
        }
    }

    if (currentPrefix != 0)
    {
        fout  << "(" << dict[currentPrefix].prefix << "," << dict[currentPrefix].c << ") ";
        fcomp << "(" << dict[currentPrefix].prefix << "," << dict[currentPrefix].c << ") ";
    }

    fout.close();
    fcomp.close();
    delete[] dict;
}

void buildPhrase(Entry* dict, int index, char* buffer, int& len)
{
    if (index == 0) return;
    buildPhrase(dict, dict[index].prefix, buffer, len);
    buffer[len++] = dict[index].c;
}

void decompressLZ78(const char* filename)
{
    ifstream fin;
    fin.open(filename);
    if (!fin.is_open())
    {
        throw runtime_error("Error al abrir archivo para descomprimir");
    }

    int capacity = 256;
    Entry* dict = new Entry[capacity];
    int dictSize = 1;

    ofstream fout;
    fout.open("archivo.txt", ios::app);
    if (!fout.is_open())
    {
        fin.close();
        delete[] dict;
        throw runtime_error("Error al abrir archivo.txt en decompressLZ78");
    }

    char ch;
    while (fin.get(ch))
    {
        if (ch != '(') continue;

        // Leer el índice
        int idx = 0;
        while (fin.get(ch) && ch != ',' && ch != ')')
        {
            idx = idx * 10 + (ch - '0');
        }

        if (ch == ')')
        {
            char phrase[1024];
            int len = 0;
            buildPhrase(dict, idx, phrase, len);
            phrase[len] = '\0';
            fout << phrase;
            continue;
        }

        char c;
        fin.get(c);
        fin.get(ch);

        char phrase[1024];
        int len = 0;
        buildPhrase(dict, idx, phrase, len);
        phrase[len++] = c;
        phrase[len] = '\0';

        fout << phrase;

        if (dictSize >= capacity)
        {
            dict = growDict(dict, capacity);
        }
        dict[dictSize].prefix = idx;
        dict[dictSize].c = c;
        dictSize++;
    }

    fin.close();
    fout.close();
    delete[] dict;
}
