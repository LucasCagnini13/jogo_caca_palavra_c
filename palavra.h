#ifndef PALAVRA_H
#define PALAVRA_H


// Estrutura que representa uma palavra e suas posições no jogo
typedef struct palavra_s {
    char palavra[20];// texto da palavra
    int inicio[2];   // posição inicial (linha, coluna)
    int fim[2];      // posição final (linha, coluna)
} Palavra;

#endif