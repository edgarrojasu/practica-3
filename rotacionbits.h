#ifndef ROTACIONBITS_H
#define ROTACIONBITS_H

unsigned char rotateLeft(unsigned char value, int shift);
unsigned char rotateRight(unsigned char value, int shift);

void cifrarTexto(char* text, int n, char key);

void descifrarTexto(char* text, int n, char key);

void cifrarArchivoCombinado(const char* filename, int n, char key);

void descifrarArchivoCombinado(const char* filename, int n, char key);

#endif // ROTACIONBITS_H

