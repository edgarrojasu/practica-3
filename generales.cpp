#include "generales.h"
#include <iostream>
using namespace std;

int rleolz78()
{
    int seleccion;

    while (true)
    {
        cout<<"Seleccione el metodo de compresion(con numeros)"<<endl<<"1:RLE"<<endl<<"2:Lz78"<<endl;
        while (!(cin >> seleccion))
        {
            cout<<"ingrese 1(RLE) o 2(LZ78)"<<endl;
            cin.clear();
            cin.ignore(10000,'\n');
        }
        if (seleccion == 1 || seleccion == 2)
        {
            return seleccion;
        }
        else
        {
            cout<<"ingrese 1(RLE) o 2(LZ78)"<<endl;
        }
    }
}

char askKey ()
{
    char key[1000];
    int cont;
    char letraActu;
    char ñ = '164';

    while (true)
    {
        cout << "Ingrese una contrase" << ñ << "a para cifrar el texto (un solo caracter): ";
        cin >> key;
        letraActu = key[0];
        cont = 0;
        while (letraActu !='\0')
        {
            letraActu = key[cont+1];

            if (letraActu =='\0' && cont == 0)
            {
                return key[0];
            }

            cont +=1;
        }
    }
}

int askN()
{
    int n;
    while (true)
    {
        cout << "Ingrese la cantidad de bits a rotar (1-7): ";
        while (!(cin >> n))
        {
            cout << "Valor invalido. Ingrese un numero entero entre 1 y 7: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        if (n >= 1 && n <= 7)
        {
            return n;
        }
        cout << "Ingrese un valor entre 1 y 7." << endl;
    }
}
