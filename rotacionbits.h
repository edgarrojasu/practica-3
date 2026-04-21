#ifndef ROTACIONBITS_H
#define ROTACIONBITS_H

unsigned char rotateLeft(unsigned char value, int shift);
unsigned char rotateRight(unsigned char value, int shift);

// Cifra in-place: rotacion izquierda n bits, luego XOR con key
void cifrarTexto(char* text, int n, char key);

// Descifra in-place: XOR con key, luego rotacion derecha n bits
void descifrarTexto(char* text, int n, char key);

// Cifra un archivo en sitio: rotacion izquierda + XOR
void cifrarArchivoCombinado(const char* filename, int n, char key);

// Descifra un archivo en sitio: XOR + rotacion derecha
void descifrarArchivoCombinado(const char* filename, int n, char key);

#endif // ROTACIONBITS_H

