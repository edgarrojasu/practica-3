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
