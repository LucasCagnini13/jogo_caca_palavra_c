#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "palavra.h"

//utilitarios
void linnhasColunasResgatar(int*linhasMatriz, int*colunasMatriz);
int posicaoCabe(char* palavra, int linha, int coluna, int direcao, int tamanhoLinha, int tamanhoColuna);
int posicaoNaoPreenchida(char** matriz,char* palavra, int linha, int coluna, int direcao, int tamanhoLinha, int tamanhoColuna);
void inserirPalavraMatriz(char** matriz, Palavra* palavra,int linha, int coluna, int direcao);
void letrasAleatoriasPreencher(char** matriz, int linhas, int colunas);
void imprimirMatriz(char** matrizPalavras, int linhasMatriz, int colunasMatriz);
int verificarPalavraEncontrada(
    char** matrizPalavras,
    Palavra* palavras,
    int linhaInicialPalavra,
    int colunaInicialPalavra,
    int linhaFinalPalavra,
    int colunaFinalPalavra,
    int tentativas
); 

//menus
void iniciarJogo(Palavra *palavras);

//joganilidade
void jogar(char** matrizPalavras, int linhasMatriz, int colunasMatriz,Palavra* palavras);
