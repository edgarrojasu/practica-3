#include <iostream>

using namespace std;

unsigned char rotateLeft(unsigned char value, int shift) {
    return (value << shift) | (value >> (8 - shift));
}

unsigned char rotateRight(unsigned char value, int shift) {
    return (value >> shift) | (value << (8 - shift));
}


