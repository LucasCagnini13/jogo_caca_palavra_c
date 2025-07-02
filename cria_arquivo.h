#ifndef CRIA_ARQUIVO_H
#define CRIA_ARQUIVO_H

// Inclusões necessárias para as funções e tipos declarados
#include <stdio.h>   // Para FILE, printf, perror, fprintf
#include <stdlib.h>  // Para malloc, free, srand, rand
#include <time.h>    // Para time
#include <string.h>  // Para strlen, strcpy, strncpy
#include <stdarg.h>  // Para strlen, strcpy, strncpy
#include "arquive_log.h" // Inclui o header da sua lib dentro da pasta 'data'
#include "palavra.h" // para usar tipo Palavra 

// --- Constantes e Estruturas ---
// Declara que estas variáveis globais existem e serão definidas em cria_arquivo.c
extern char **textos;
extern int num_textos;

// Funções para manipulação do array de palavras
int palavra_existe(const char *palavra);
void inserir_palavra (int is_print, const char *nova_palavra);
void remover_palavra(int is_print,const char *palavra_a_remover);
void atualiza_palavra(int is_print, const char *palavra_anterior, const char *nova_palavra);
void libera_array(int is_print);
void mostrar_palavras();
void inicializar_dicionario(int valida_para_recriar);
int main();
// --- Declarações de Funções ---
// Funções para sortear e gerenciar listas de palavras em memória
char **retorna_lista (int numero_lista_nova);
Palavra *retorna_lista_n_arquivo(char **lista_textos, int total_palavras);

// Funções para manipulação do arquivo binário (agora com nome de arquivo parametrizado)
int cria_arquivo();
char **retorna_dados_arquivo();
int valida_arquivo_criado();

// Função principal de gerenciamento que orquestra as operações
Palavra *get_palavras(int numero_de_escolhas, int valida_para_recriar);

#endif // CRIA_ARQUIVO_H