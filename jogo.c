#include "jogo.h"
#include "palavra.h"
#include "cria_arquivo.h"

void linnhasColunasResgatar(int*linhasMatriz, int*colunasMatriz){
    
    // inicialização de variaveis de validação
    int validacaoLinha = 0;
    int validacaoColuna = 0;
    
    while(validacaoLinha == 0){

    printf("\nquantas linhas vai ter o caça palavras? min=7 max=9 \n");
    scanf("%d",linhasMatriz);
    
        // verifica se esta entre 7 e 9
        if(*linhasMatriz > 9 || *linhasMatriz < 7){
            printf("\nA quantidade de linhas deve estar entre 7 e 9!\n");
            continue;
        }
        
        //valida e sai do loop
        validacaoLinha = 1;
    
    }
    
    while(validacaoColuna == 0){

    printf("\nquantas colunas vai ter o caça palavras? min=7 max=9 \n");
    scanf("%d",colunasMatriz);
    
        // verifica se esta entre 7 e 9
        if(*colunasMatriz > 9 || *colunasMatriz < 7){
            printf("\nA quantidade de linhas deve ser menor que 7 e maior que 9!\n");
            continue;
        }
        //valida e sai do loop
        validacaoColuna = 1;
    }   
}

// função responsavel por verificar se a palavra cabe na matriz
int posicaoCabe(char* palavra, int linha, int coluna, int direcao, int tamanhoLinha, int tamanhoColuna) {
    int tamanho = strlen(palavra);

    if (direcao == 0) return coluna + tamanho <= tamanhoLinha; // horizontal
    if (direcao == 1) return linha + tamanho <= tamanhoColuna; // vertical
    if (direcao == 2) return linha + tamanho <= tamanhoLinha && coluna + tamanho <= tamanhoColuna; //vertical

    return 0;
}

//verifica se a posição já não foi preenchida na matriz
int posicaoNaoPreenchida(char** matriz,char* palavra, int linha, int coluna, int direcao, int tamanhoLinha, int tamanhoColuna) {
    int tamanho = strlen(palavra);

    if (direcao == 0){  // horizontal
        for(int i = 0;i < tamanho && coluna+i < tamanhoColuna;i++){
            if(matriz[linha][coluna+i] != ' '){
                return 0; 
            }    
        }
        
        return 1;
    }else if (direcao == 1){ // vertical
        for(int i = 0;i < tamanho && linha+i < tamanhoLinha;i++){
            if(matriz[linha+i][coluna] !=  ' '){
                return 0; 
            }    
        }
        
        return 1;
    }else if (direcao == 2){ // diagonal
        for(int i = 0;i < tamanho && linha+i < tamanhoLinha && coluna+i < tamanhoColuna;i++){
            if(matriz[linha+i][coluna+i] !=  ' '){
                return 0; 
            }    
        }
        
        return 1;
    }

    return 0;
}

void inserirPalavraMatriz(char** matriz, Palavra* palavra,int linha, int coluna, int direcao) {
    int i;
    for (i = 0; i < strlen(palavra->palavra); i++) {
        if (direcao == 0)
            matriz[linha][coluna + i] = palavra->palavra[i];         // horizontal

        else if (direcao == 1)
            matriz[linha + i][coluna] = palavra->palavra[i];           // vertical
        else if (direcao == 2)
            matriz[linha + i][coluna + i] = palavra->palavra[i];         // diagonal
    }

        palavra->inicio[0] = linha;
        palavra->inicio[1] = coluna;

        if (direcao == 0){
            palavra->fim[0] = linha; 
            palavra->fim[1] = coluna+i-1;        // horizontal
        }else if (direcao == 1){
            palavra->fim[0] = linha+i-1; 
            palavra->fim[1] = coluna;       // vertical
        }else if (direcao == 2){
            palavra->fim[0] = linha+i-1; 
            palavra->fim[1] = coluna+i-1;    // diagonal
        }
}

//preenche o resto das posições da matriz com letras aleatorias
void letrasAleatoriasPreencher(char** matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == ' ') { // se não foi preenchido ainda
                matriz[i][j] = 'a' + (rand() % 26); // letra aleatória A-Z
            }
        }
    }
}

//função responsavel por impremir matriz
void imprimirMatriz(char** matrizPalavras, int linhasMatriz, int colunasMatriz){

    // Cabeçalho das colunas
    printf("    ");  // Espaço para alinhar com os índices das linhas
    for (int j = 0; j < colunasMatriz; j++) {
        printf("%2d ", j);  // Imprime o índice da coluna com 2 dígitos
    }
    printf("\n");

    // Separador
    printf("   ");
    for (int j = 0; j < colunasMatriz; j++) {
        printf("---");
    }
    printf("\n");

    // Linhas com dados e índices laterais
    for (int i = 0; i < linhasMatriz; i++) {
        printf("%2d| ", i);  // Índice da linha
        for (int j = 0; j < colunasMatriz; j++) {
            printf("%2c ", matrizPalavras[i][j]);
        }
        printf("\n");
    }
}

// Função que verifica se a posição digitada corresponde a alguma palavra escondida na matriz
// Se sim, substitui as letras pela tentativa (um número) e retorna 1, senão retorna 0
int verificarPalavraEncontrada(
    char** matrizPalavras,           // Matriz do caça-palavras
    Palavra* palavras,               // Vetor de palavras escondidas
    int linhaInicialPalavra,         // Linha da posição inicial informada pelo jogador
    int colunaInicialPalavra,        // Coluna da posição inicial
    int linhaFinalPalavra,           // Linha da posição final informada pelo jogador
    int colunaFinalPalavra,          // Coluna da posição final
    int tentativas                   // Número de tentativas feitas até agora
) {
    // Percorre todas as palavras da lista
    for (int i = 0; i < 5; i++) {
        // Verifica se a posição informada corresponde à posição de alguma palavra (início e fim)
        // Também aceita se o jogador informar o fim como início e o início como fim
        if ((palavras[i].inicio[0] == linhaInicialPalavra && palavras[i].inicio[1] == colunaInicialPalavra &&
             palavras[i].fim[0] == linhaFinalPalavra && palavras[i].fim[1] == colunaFinalPalavra) ||
            (palavras[i].inicio[0] == linhaFinalPalavra && palavras[i].inicio[1] == colunaFinalPalavra &&
             palavras[i].fim[0] == linhaInicialPalavra && palavras[i].fim[1] == colunaInicialPalavra)) {
            
            int tamanhoPalavra = strlen(palavras[i].palavra); // Calcula o tamanho da palavra
            char caractere = (tentativas + 1) + '0';  // Converte a tentativa em um caractere numérico

            // Substitui as letras por esse número, de acordo com a direção da palavra
            if (palavras[i].inicio[0] == palavras[i].fim[0]) {
                // Direção horizontal
                int linha = palavras[i].inicio[0];
                int colunaInicio = palavras[i].inicio[1];
                for (int j = 0; j < tamanhoPalavra; j++) {
                    matrizPalavras[linha][colunaInicio + j] = caractere;
                }
            } else if (palavras[i].inicio[1] == palavras[i].fim[1]) {
                // Direção vertical
                int coluna = palavras[i].inicio[1];
                int linhaInicio = palavras[i].inicio[0];
                for (int j = 0; j < tamanhoPalavra; j++) {
                    matrizPalavras[linhaInicio + j][coluna] = caractere;
                }
            } else {
                // Direção diagonal (de cima-esquerda para baixo-direita)
                int linhaInicio = palavras[i].inicio[0];
                int colunaInicio = palavras[i].inicio[1];
                for (int j = 0; j < tamanhoPalavra; j++) {
                    matrizPalavras[linhaInicio + j][colunaInicio + j] = caractere;
                }
            }

            palavras[i].palavra[0] = '\0'; // "Apaga" a palavra para marcar que já foi encontrada
            return 1; // Palavra encontrada com sucesso
        }
    }

    return 0; // Nenhuma palavra foi encontrada nas posições informadas
}


void iniciarJogo(Palavra *palavras){
    
    // definição das variveis de tamanho da matriz
    int linhasMatriz = 0;
    int colunasMatriz = 0;
    
    //capturar tamanho das linhas e colunas
    linnhasColunasResgatar(&linhasMatriz, &colunasMatriz);
    
    // Aloca dinamicamente um vetor de ponteiros para representar as linhas da matriz
    char** matrizPalavras = malloc(linhasMatriz * sizeof(char*));

    // Para cada linha, aloca um vetor de caracteres que representa as colunas
    for (int i = 0; i < linhasMatriz; i++) {
        matrizPalavras[i] = malloc(colunasMatriz * sizeof(char));
    }

    // Inicializa todos os elementos da matriz com o caractere espaço ' ' (indicando posição vazia)
    for (int i = 0; i < linhasMatriz; i++) {
        for (int j = 0; j < colunasMatriz; j++) {
            matrizPalavras[i][j] = ' ';
        }
    }
    
    //inicializa variavel que inndica quantas palavras foram colocadas na matriz 
    int palavrasNaMatriz = 0;
    
    //só sai do loop quando tiver 5 palavras na matriz
    while(palavrasNaMatriz < 5){
        
        //sorteia posição inicial da linha
        int posicaoLinha = rand() % linhasMatriz;
        //sorteia posição inicial da coluna
        int posicaoColuna = rand() % colunasMatriz;
        //sorteia direção da plabra dentro da matriz
        int direcao = rand() % 3;
        
        if (posicaoCabe(palavras[palavrasNaMatriz].palavra,posicaoLinha, posicaoColuna, direcao, linhasMatriz, colunasMatriz) &&
            posicaoNaoPreenchida(matrizPalavras,palavras[palavrasNaMatriz].palavra, posicaoLinha, posicaoColuna, direcao, linhasMatriz, colunasMatriz)) {
                //inseri plavra na matriz
                inserirPalavraMatriz(matrizPalavras, &palavras[palavrasNaMatriz], posicaoLinha, posicaoColuna, direcao);      
                palavrasNaMatriz++;
            }
    }
    
    //preenche o resto das posições da matriz com letras aleatorias
    letrasAleatoriasPreencher(matrizPalavras,linhasMatriz, colunasMatriz);

    //limpa terminal
    system("cls");
    printf("\nJOGO INICIADO!!!");
    
    //função responsavel por inicar a jogabilidade
    jogar(matrizPalavras,linhasMatriz,colunasMatriz,palavras);
    
}

//função responsavel por inicar a jogabilidade
void jogar(char** matrizPalavras, int linhasMatriz, int colunasMatriz, Palavra* palavras) {
    
    //inicializa varivel responsavel por guardar o número de palavras encontradas
    int palavraEncontra = 1;
    //inicializa varivel responsavel por guardar o número de tentativas
    int tentativas = 0; 
    
    while(palavraEncontra < 6){

    printf("\ntentaiva %d\n",tentativas+1);
        
        //função responsavel por impremir matriz
        imprimirMatriz(matrizPalavras, linhasMatriz, colunasMatriz);
        
        //imprime palavras que ainda não foram encontradas
        printf("\nPalavras Restantes: ");
        int primeira = 1;
        for (int i = 0; i < 5; i++) {
            if (palavras[i].palavra[0] != '\0') {
                if (!primeira) {
                    printf(", ");
        }
            printf("%s", palavras[i].palavra);
            primeira = 0;
            }
        }
       
        // Inicializa as variáveis que armazenam as coordenadas da posição inicial e final da palavra que o jogador encontrou
        int linhaInicialPalavra = 0;
        int colunaInicialPalavra = 0;
        int linhaFinalPalavra = 0;
        int colunaFinalPalavra = 0;

        int lidos = 0;

        // Loop para ler a posição inicial da palavra encontrada pelo jogador
        do {
            printf("\nDigite a posição inicial da palavra encontrada (x y): ");
            lidos = scanf("%d %d", &linhaInicialPalavra, &colunaInicialPalavra);

        while(getchar() != '\n'); // Limpa o buffer do teclado para evitar problemas com entradas inválidas

        // Verifica se foram lidos exatamente dois inteiros
        if (lidos != 2) {
            printf("Entrada inválida! Digite dois números inteiros separados por espaço.\n");
            continue;
        }

        // Verifica se os valores estão dentro dos limites da matriz
        if (linhaInicialPalavra < 0 || linhaInicialPalavra >= linhasMatriz ||
            colunaInicialPalavra < 0 || colunaInicialPalavra >= colunasMatriz) {
            printf("Entrada inválida! Fora dos limites da matriz.\n");
            continue;
        }

        // Se tudo estiver certo, sai do loop
        break;

    } while (1);

    lidos = 0;

    // Loop para ler a posição final da palavra encontrada
        do {
            printf("\nDigite a posição final da palavra encontrada (x y): ");
            lidos = scanf("%d %d", &linhaFinalPalavra, &colunaFinalPalavra);

        while(getchar() != '\n'); // Limpa o buffer do teclado

        // Verifica se foram lidos exatamente dois inteiros
        if (lidos != 2) {
            printf("Entrada inválida! Digite dois números inteiros separados por espaço.\n");
            continue;
        }

        // Verifica se os valores estão dentro dos limites da matriz
        if (linhaFinalPalavra < 0 || linhaFinalPalavra >= linhasMatriz ||
            colunaFinalPalavra < 0 || colunaFinalPalavra >= colunasMatriz) {
            printf("Entrada inválida! Fora dos limites da matriz.\n");
            continue;
        }

        // Se tudo estiver certo, sai do loop
        break;

    } while (1);
  
        //limpa terminal
        system("cls");

        //verifica se a palavra esta na matriz
        if (verificarPalavraEncontrada(
            matrizPalavras,
            palavras,
            linhaInicialPalavra,
            colunaInicialPalavra,
            linhaFinalPalavra,
            colunaFinalPalavra,
            tentativas)) {
    
            tentativas++;
            palavraEncontra++;
            printf("\nEncontrou uma palavra!\n");

        } else {
            printf("\nNão encontrou uma palavra, tente novamente!\n");
        }
    }

    //limpa terminal
    system("cls");
    printf("PARABÉNS, VOCÊ GANHOU!!!\n");
    printf("tentaivas jogadas: %d",tentativas);

    int escolha;

    printf("\n|===CAÇA PALAVRAS===|\n");
    printf("1 - Novo Jogo\n");
    printf("2 - Menu Inicial\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção : \n");
    scanf("%d",&escolha);

    if(escolha == 1){
        // inicia o jogo de novo
        Palavra *palavrasNovas = get_palavras(5,0);
        iniciarJogo(palavrasNovas);
    }else if(escolha == 2){
        // volta ao menu inicial
        return;
    }else{
        // finaliza programa
        exit(0);;
    }
}