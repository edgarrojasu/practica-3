#include <iostream>
#include <fstream>

using namespace std;

ifstream leer_archiv(string nombre_archivo){
    ifstream fin;

    fin.open(nombre_archivo, ios::in);
    if(!fin.is_open()){
        cout << "No abierto" << endl;
    }
    else{
        return fin;
    }
    fin.close();
    return fin;
}

string lecturalinea(ifstream instancia){
    string lectura;
    while(getline(instancia, lectura)){
        cout << lectura << endl;
        return lectura;
    }
    cout << lectura << endl;
    return lectura;
}

void lecturachar(ifstream instancia){
    char letra;
    while(instancia.good()){
        letra=instancia.get();
        if(letra != '\n'){
            cout << letra;
        }
        else{
            cout << endl;
        }
    }
}
