#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Para srand(time(NULL));
#include "cria_arquivo.h" // Inclui o header da sua lib 
#include "arquive_log.h" // Inclui o header da sua lib 
#include "jogo.h" // inclui função de jogabilidade
#include "palavra.h" // para usar o type palavra
void limpar_tela() {
    // Código ANSI para limpar a tela e mover o cursor para o canto superior esquerdo
    printf("\033[2J\033[H");
}
int main() {
    // Inicializa o gerador de números aleatórios APENAS UMA VEZ
    log_to_file("log_programa.log",  LOG_INFO,"Inicio do log\n");
    srand(time(NULL));

    inicializar_dicionario(0);
    while (1){

    int escolha;

    printf("\n|===CAÇA PALAVRAS===|\n");
    printf("1 - Iniciar Jogo\n");
    printf("2 - Inserir palavra\n");
    printf("3 - Atualizar palavra\n");
    printf("4 - Remover Palavra\n");
    printf("5 - Mostrar Palavras\n");
    printf("6 - Salvar Palavras\n");
    printf("7 - Limpar lista de palavras\n");
    printf("8 - Carregar lista de palavras base\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção : \n");
    scanf("%d",&escolha);
    limpar_tela();


    if(escolha == 1){
        // sorteia e captura 5 palavras do arquivo
        Palavra *palavras = get_palavras(5,0);
        //inicia o jogo
        iniciarJogo(palavras);
    }else if(escolha == 2){
        //inserir palavras do arquivo
        char novaPalavra[20];
        printf("\ndigite a plavara que você quer inserir: ");
        scanf("%s",novaPalavra);
        inserir_palavra(1,novaPalavra);

    }else if(escolha == 3){
        //atualizar palavras do arquivo
        char novaPalavra[20],anteriorPlavra[20];
        printf("\ndigite a plavara que você quer subtituir: ");
        scanf("%s",novaPalavra);
        printf("\ndigite a nova plavara: ");
        scanf("%s",anteriorPlavra);
        atualiza_palavra(1,novaPalavra,anteriorPlavra);

    }else if(escolha == 4){
        //remover palavras do arquivo
        char removePalavra[20];
        printf("\ndigite a plavara que você quer remover: ");
        scanf("%s",removePalavra);
        remover_palavra(1,removePalavra);

    }else if(escolha == 5){
        //mostra palavras do arquivo
        mostrar_palavras();

    }else if(escolha == 6){
        //Salva palavras em arquivo
        cria_arquivo();

    }else if(escolha == 7){
        //Limpa lista de palavras
        libera_array(1);

    }else if(escolha == 8){
        //recarrega Lista de palavras
        inicializar_dicionario(1);

    }else{
        //retorna 0 para finalizar o programa
        return 0;
        }
    }
    
    // Libera a memória quando não precisar mais do dicionário
    libera_array(1);
    log_to_file("log_programa.log",  LOG_INFO,"Fim do log\n");

    return 0;
}