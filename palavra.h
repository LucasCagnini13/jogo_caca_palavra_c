#ifndef PALAVRA_H
#define PALAVRA_H

// Definição da struct Palavra
typedef struct palavra_s {
    char palavra[20];
    int inicio[2];
    int fim[2];
} Palavra;

#endif