#include "cria_arquivo.h"
#include "palavra.h"

char **textos = NULL;
int num_textos= 0;

// Verifica se a palavra já existe no array
int palavra_existe(const char *palavra){
    for (int i = 0; i < num_textos; i++){
        if(strcmp(textos[i],palavra) ==0){
            return 1;
        }
    }
    return 0;
}

// Insere nova palavra no array, validando tamanho e existência
void inserir_palavra (int is_print, const char *nova_palavra){
    if (nova_palavra == NULL){
        log_to_file("log_programa.log", LOG_ERROR, "Palavra nao passada na funcao\n");
        print_erro(is_print,"A palavra não foi informada...\n");
        return;
    }
    if (strlen(nova_palavra) <5 ||  strlen(nova_palavra) >20 ){
        log_to_file("log_programa.log", LOG_ERROR, "Palavra fora do range de 5 a 20 caracteres\n");
        print_erro(is_print,"A palavra %s esta fora do range de 5 a 20 caracteres\n",nova_palavra);
        return;
    }
    if (palavra_existe(nova_palavra) == 1){
        print_aviso(is_print,"Palavra '%s' ja existe na lista de palavras...\n",nova_palavra);
        return;
    }
    char **temporario = (char**)realloc(textos,(num_textos+1) * sizeof(char*));
    if(temporario == NULL){
        log_to_file("log_programa.log", LOG_ERROR, "erro ao realocar memoria para o array de palavras\n");
        print_erro(is_print,"Houve um erro tente inserir novemente a palavra: %s\n",nova_palavra);
        return;
    }
    textos = temporario;
    textos[num_textos] = (char*) malloc(strlen(nova_palavra)+1);
    if (textos[num_textos] == NULL){
        log_to_file("log_programa.log", LOG_ERROR, "erro ao alocar memoria para a nova palavra\n");
        print_erro(is_print,"Houve um erro tente inserir novemente a palavra: %s\n",nova_palavra);
        return;
    }
    strcpy(textos[num_textos],nova_palavra);
    num_textos++;
    log_to_file("log_programa.log", LOG_INFO, "Palavra '%s' adicionada com sucesso.\n",nova_palavra);
    print_sucesso(is_print,"Palavra '%s' adicionada com sucesso.\n",nova_palavra);
}

// Remove uma palavra do array, reorganiza memória
void remover_palavra(int is_print,const char *palavra_a_remover){
    int indice_remover = -1;
    for (int i = 0; i < num_textos; i++){
        if (strcmp(textos[i],palavra_a_remover) == 0){
            indice_remover = i;
            break;
        }
    }
    if (indice_remover == -1){
        log_to_file("log_programa.log", LOG_ERROR, "A palavra '%s' nao foi encontrada no array de palavras\n",palavra_a_remover);
        print_aviso(is_print,"A palavra '%s' nao foi encontrada na lista de palavras\n",palavra_a_remover);
        return;
    }
    free(textos[indice_remover]);
    for (int i = indice_remover; i < num_textos -1; i++){
        textos[i] = textos[i+1];
    }
    num_textos--;
    if (num_textos<=0){
        num_textos = 0;
        free(textos);
        textos = NULL;
        log_to_file("log_programa.log", LOG_INFO, "Removido a palavra '%s' e o array de palavras esta vazio\n",palavra_a_remover);
        print_sucesso(is_print,"Removido a palavra '%s' e a lista de palavras esta vazia\n",palavra_a_remover);
    }else{
        char **temporario = (char**) realloc(textos, num_textos * sizeof(char*));
        if (temporario == NULL){
            log_to_file("log_programa.log", LOG_ERROR, "erro ao alocar memoria apos a remocao, porem sem aplicar no array original\n");
            print_erro(is_print,"Houve um erro ao tente remover a palavra: %s\n",palavra_a_remover);
            return;
        }
        textos = temporario;
        log_to_file("log_programa.log", LOG_INFO, "Removido a palavra '%s' do array de palavras\n",palavra_a_remover);
        print_sucesso(is_print,"Palavra '%s' removida com sucesso!\n",palavra_a_remover);
    }
}

// Libera toda a memória do array e limpa array de palavras
void libera_array(int is_print){
    for (int i = 0; i < num_textos; i++){
        free(textos[i]);
    }
    free(textos);
    textos= NULL;
    num_textos = 0;
    log_to_file("log_programa.log", LOG_INFO, "Array de palavras liberado na memoria\n");
    print_sucesso(is_print,"Lista de palavras foi limpa");
}

// Mostra todas as palavras do array
void mostrar_palavras(){
    log_to_file("log_programa.log", LOG_INFO, "\n--- Palavras Atuais no Array (%d) ---\n", num_textos);
    if (num_textos == 0) {
        log_to_file("log_programa.log", LOG_ERROR, "Array vazio.\n");
        return;
    }
    for (int i = 0; i < num_textos; i++) {
        log_to_file("log_programa.log", LOG_INFO, "%d: %s\n", i + 1, textos[i]);
        printf("%s", textos[i]);
        if (i < num_textos -2){
            printf(", ");
        }else if(i == (num_textos - 2)){
            printf(" e ");
        }else if(i == (num_textos -1)){
            printf(".");
        }
        if (i % 10 == 0 && i != 0){
            printf("\n");
        }
        
    }
    log_to_file("log_programa.log", LOG_INFO, "---------------------------------------\n");
}

// Inicializa o dicionário: recria ou carrega de arquivo binário
void inicializar_dicionario(int valida_para_recriar) {
    if (valida_para_recriar == 1){
        libera_array(0);
        const char *palavras_iniciais[] = {
            "abacaxi","ameixa","amora","araca","banana","cacau","caqui","cereja",
            "damasco","goiaba","laranja","limao","lichia",
            "manga","melao","mamao","morango","pessego","pitanga","sapoti",
            "abobora","agriao","alface","aspargo","batata","cebola","cenoura","chuchu",
            "couve","ervilha","feijao","inhame","milho","pepino","quiabo",
            "maniva","repolho","rucula","salsao","tomate","acelga","broto","vagem","trevo",
            "apito","aviao","balao","balde","banco","barco","bolsa","botao",
            "caixa","caneca","caneta","carro","carta","cesto","chave","colher",
            "espada","espelho","forno","garfo",
            "globo","guarda","haste","janela","jarra",
            "abelha","cabra","cisne","cobra","coelho","coruja","formiga","galinha",
            "ganso","jabuti","macaco","morcego","ovelha","panda","papagaio",
            "pomba","pinguim","porco","pulga","texugo","tigre","touro","zebra","alpaca","burro","camelo",
            "branco","cobre","dourado","marrom","preto","verde","amarelo",
            "cinza","prata","creme","violeta","indigo","ciano","magenta","carmim","lilas",
            "bronze","salmao","palha","siena","trigo","vinho","azulejo",
            "andar","beber","cantar","correr","dormir","falar","olhar","pular","comer",
            "abrir","ajudar","apoiar","banhar","chamar","criar","dancar","ensinar",
            "entrar","estudar","fazer","fechar","ganhar","gostar","gritar","jogar","limpar","morar"
        };
    
        int total_palavras_iniciais = sizeof(palavras_iniciais) / sizeof(palavras_iniciais[0]);
        log_to_file("log_programa.log", LOG_INFO, "Inicializando array com %d palavras...\n", total_palavras_iniciais);
    
        for (int i = 0; i < total_palavras_iniciais; i++) {
            inserir_palavra(0,palavras_iniciais[i]);
        }
        log_to_file("log_programa.log", LOG_INFO, "Array inicializado.\n");
        cria_arquivo();
    } else {
        if (valida_arquivo_criado() == 1){
            log_to_file("log_programa.log", LOG_INFO, "Carregando arquivo de dados\n");
            libera_array(0);
            char **carrega_array = retorna_dados_arquivo();
            if (carrega_array != NULL){
                int num_lido = num_textos;
                num_textos = 0;
                for (int i = 0; i < num_lido; i++){
                    inserir_palavra(0,carrega_array[i]);
                }
                for (int i = 0; i < num_lido; i++){
                    if (carrega_array[i] != NULL) free(carrega_array[i]);
                }
                free(carrega_array);
                log_to_file("log_programa.log", LOG_INFO, "Inicializando array com %d palavras...\n", num_lido);
                log_to_file("log_programa.log", LOG_INFO, "Array inicializado com arquivo.\n");
            } else {
                log_to_file("log_programa.log", LOG_ERROR, "Falha ao carregar dados do arquivo.\n");
                inicializar_dicionario(1);
            }
        } else {
            log_to_file("log_programa.log", LOG_ERROR, "Arquivo nao encontrado. Inicializa com palavras padrao.\n");
            inicializar_dicionario(1);
        }
    }
}

// Sorteia N palavras aleatórias sem repetição
char **retorna_lista (int numero_lista_nova){
    if (numero_lista_nova <=0 || numero_lista_nova > num_textos){
        log_to_file("log_programa.log", LOG_ERROR, "O numero de sorteio deve ser entre 1 e %d\n", num_textos);
        return  NULL;
    }

    if (num_textos == 0){
        log_to_file("log_programa.log", LOG_ERROR, "Nenhuma palavra disponivel para sorteio.\n");
        return NULL;
    }
    
    int *lista_indice = (int *)malloc(numero_lista_nova * sizeof(int));
    if (lista_indice == NULL){
        log_to_file("log_programa.log", LOG_ERROR, "erro ao alocar memoria\n");
        return  NULL;
    }
    
    char **textos_aleatorios = (char**)malloc(numero_lista_nova * sizeof(char *));
    if (textos_aleatorios == NULL){
        log_to_file("log_programa.log", LOG_ERROR, "erro ao alocar memoria\n");
        free(lista_indice);
        return  NULL;
    }
    
    int contador = 0;
    // mostrar_palavras();
    while (contador <numero_lista_nova){
        int numero_aletorio = rand() % num_textos;
        int escolhido = 0;
        for (int i = 0; i < contador; i++){
            if (lista_indice[i] == numero_aletorio){
                escolhido = 1;
                break;
            }
        }
        if (!escolhido){
            lista_indice[contador] = numero_aletorio;
            textos_aleatorios[contador] = (char*)malloc(strlen(textos[numero_aletorio])+1);
            if (textos_aleatorios[contador] == NULL){
                log_to_file("log_programa.log", LOG_ERROR, "erro ao alocar memoria\n");
                for (int i = 0; i < contador; i++){
                    free(textos_aleatorios[i]);
                }
                free(textos_aleatorios);
                free(lista_indice);
                return  NULL;
            }
            strcpy(textos_aleatorios[contador],textos[numero_aletorio]);
            contador++;
        }
    }
    free(lista_indice);
    return textos_aleatorios;
}

// Converte lista de strings em structs Palavra
Palavra *converte_array_para_palavra(char **lista_textos, int total_palavras){
    if(lista_textos == NULL || total_palavras <=0){
        log_to_file("log_programa.log",  LOG_ERROR,"Erro: lista de textos invalida ou numero de palavras <=0 \n");
        return NULL;
    }
    Palavra *lista_palavras = (Palavra*) malloc(total_palavras * sizeof(Palavra));
    if (lista_palavras == NULL){
        log_to_file("log_programa.log", LOG_ERROR, "erro ao alocar memoria\n");
        return NULL;
    }
    for (int i = 0; i < total_palavras; i++){
        if (lista_textos[i] == NULL){
            log_to_file("log_programa.log", LOG_ERROR, "erro ao selcionar palavra\n");
            for (int j = 0; j < i; j++){
                free(lista_textos[j]);
            }
            free(lista_textos);
            return NULL;
        }
        strncpy(lista_palavras[i].palavra,lista_textos[i], sizeof(lista_palavras[i].palavra)-1);
        lista_palavras[i].palavra[sizeof(lista_palavras[i].palavra) -1] = '\0';
        lista_palavras[i].inicio[0] = 0;
        lista_palavras[i].fim[0] = 0;
        lista_palavras[i].inicio[1] = 0;
        lista_palavras[i].fim[1] = 0;
        
    }
    return lista_palavras;
} 

// Salva o array em arquivo binário
int cria_arquivo(){
    FILE *arquivo = NULL;
    if (textos == NULL || num_textos <=0){
        log_to_file("log_programa.log", LOG_ERROR, "Erro: lista de textos invalida ou numero de palavras <=0 \n");
        print_aviso(1,"lista de palavras invalida ou numero de palavras <=0 \n");
        return -1;
    }
    
    arquivo = fopen("palavras.bin","wb"); 
    if (arquivo == NULL){
        log_to_file("log_programa.log", LOG_ERROR, "erro ao criar aquivo\n");
        print_erro(1,"erro ao criar aquivo\n");
        return -1;
    }

    if (fwrite(&num_textos,sizeof(int),1,arquivo) != 1){
        log_to_file("log_programa.log", LOG_ERROR, "erro ao escrever numero de plavras no arquivo\n");
        print_erro(1,"erro ao escrever numero de plavras no arquivo\n");
        fclose(arquivo);
        remove("palavras.bin");
        return -1;
    }

    for (int i = 0; i < num_textos; i++){
        int tamanho_palavra = strlen(textos[i]);
        if (fwrite(&tamanho_palavra,sizeof(int),1,arquivo) != 1){
            log_to_file("log_programa.log", LOG_ERROR, "Erro ao escrever o comprimento da palavra '%s' no arquivo.\n", textos[i]);
            print_erro(1,"Erro ao escrever o comprimento da palavra '%s' no arquivo.\n", textos[i]);
            fclose(arquivo);
            remove("palavras.bin");
            return -1;
        }
        if (fwrite(textos[i],sizeof(char),tamanho_palavra,arquivo) != (size_t)tamanho_palavra){
            log_to_file("log_programa.log", LOG_ERROR, "Erro ao escrever a palavra '%s' no arquivo.\n", textos[i]);
            print_erro(1,"Erro ao escrever a palavra '%s' no arquivo.\n", textos[i]);
            fclose(arquivo);
            remove("palavras.bin");
            return -1;
        }
    }
    
    fclose(arquivo);
    log_to_file("log_programa.log", LOG_INFO, "Dados criados com sucesso no arquivo.\n");
    print_sucesso(1,"Dados criados com sucesso no arquivo.\n");
    return 0;
}

// Carrega palavras do arquivo binário para memória
char **retorna_dados_arquivo(){
    FILE *arquivo = NULL;
    char **lista_palavras = NULL;
    int num_texto_temp = 0;
    arquivo = fopen("palavras.bin","rb"); 
    if (arquivo == NULL){
        log_to_file("log_programa.log", LOG_ERROR, "erro ao abrir para leitura o aquivo\n");
        return NULL;
    }
    if (fread(&num_texto_temp,sizeof(int),1,arquivo)!= 1){
        log_to_file("log_programa.log", LOG_ERROR, "erro ao ler numero de plavras no arquivo\n");
        fclose(arquivo);
        return NULL;
    }
    if (num_texto_temp <= 0){
        log_to_file("log_programa.log", LOG_ERROR, "Arquivo vazio ou com numero invalido de palavras (%d).\n", num_texto_temp);
        fclose(arquivo);
        return NULL;
    }
    
    lista_palavras = (char**) malloc(num_texto_temp * sizeof(char*));
    if (lista_palavras == NULL){
        log_to_file("log_programa.log", LOG_ERROR, "erro ao alocar memoria para lista de ponteiros\n");
        fclose(arquivo);
        return NULL;
    }
    for (int i = 0; i < num_texto_temp; i++){
        int tamanho_palavra;
        if (fread(&tamanho_palavra,sizeof(int),1,arquivo) != 1){
            log_to_file("log_programa.log", LOG_ERROR, "erro ao ler tamanho da palavra %d\n",i);
            for (int j = 0; j < i; j++){
                free(lista_palavras[j]);
            }
            fclose(arquivo);
            return NULL;
        }
        lista_palavras[i] = (char*)malloc(tamanho_palavra +1);
        if (lista_palavras[i] == NULL){
            log_to_file("log_programa.log", LOG_ERROR, "erro ao ler palavra %d\n",i);
            for (int j = 0; j < i; j++){
                free(lista_palavras[j]);
            }
            free(lista_palavras);
            fclose(arquivo);
            return NULL;
        }
        if (fread(lista_palavras[i], sizeof(char), tamanho_palavra, arquivo) != tamanho_palavra) {
            log_to_file("log_programa.log", LOG_ERROR, "erro ao ler a palavra %d\n", i);
            free(lista_palavras[i]);
            for (int j = 0; j < i; j++) { free(lista_palavras[j]); }
            free(lista_palavras);
            fclose(arquivo);
            return NULL;
        }
        lista_palavras[i][tamanho_palavra]= '\0';
        
    }
    fclose(arquivo);
    num_textos = num_texto_temp;
    
    log_to_file("log_programa.log", LOG_INFO, "Dados lidos com sucesso do arquivo\n");
    return lista_palavras;
}

// Verifica se arquivo binário existe
int valida_arquivo_criado(){
    FILE *arquivo = NULL;
    arquivo = fopen("palavras.bin","rb");
    if (arquivo == NULL){
        log_to_file("log_programa.log", LOG_ERROR, "erro ao abrir para leitura o aquivo\n");
        return 0;
    }
    fclose(arquivo);
    return 1;
}

// Gerencia fluxo principal para pegar palavras
Palavra *get_palavras(int numero_de_escolhas, int valida_para_recriar) {
    if (numero_de_escolhas <= 0){
        log_to_file("log_programa.log", LOG_ERROR, "numero menor que 0\n");
        return NULL;
    }
    inicializar_dicionario(valida_para_recriar);
    if (numero_de_escolhas > num_textos){
        log_to_file("log_programa.log", LOG_ERROR, "Numero de escolhas (%d) e maior que o numero de palavras disponiveis (%d).\n", numero_de_escolhas, num_textos);
        return NULL;
    }
    char **meus_textos_aleatorios = retorna_lista(numero_de_escolhas);
    // --- 1. Geração e Conversão para Palavras ---
    if (meus_textos_aleatorios == NULL) {
        log_to_file("log_programa.log", LOG_ERROR, "Falha ao obter textos aleatórios. Encerrando programa.\n");
        return NULL;
    }
    
    Palavra *lista_de_palavras_struct = converte_array_para_palavra(meus_textos_aleatorios, numero_de_escolhas);
    if (lista_de_palavras_struct == NULL) {
        log_to_file("log_programa.log", LOG_ERROR, "Falha ao converter para lista de Palavras. Liberando textos aleatórios e encerrando.\n");
        // Libera a memória de meus_textos_aleatorios antes de sair
        for (int i = 0; i < numero_de_escolhas; i++) {
            free(meus_textos_aleatorios[i]);
        }
        free(meus_textos_aleatorios);
        return NULL;
    }

    // --- 4. Imprime as palavras e suas informações lidas do arquivo ---
    log_to_file("log_programa.log", LOG_INFO, "\n--- Lista de Palavras Lidas do Arquivo () ---\n");
    for (int i = 0; i < numero_de_escolhas; i++) {
        log_to_file("log_programa.log",  LOG_INFO,"Palavra %d: %s\n", i + 1, lista_de_palavras_struct[i].palavra);
        log_to_file("log_programa.log",  LOG_INFO,"  Inicio: [%d, %d]\n", lista_de_palavras_struct[i].inicio[0], lista_de_palavras_struct[i].inicio[1]);
        log_to_file("log_programa.log",  LOG_INFO,"  Fim:    [%d, %d]\n", lista_de_palavras_struct[i].fim[0], lista_de_palavras_struct[i].fim[1]);
        log_to_file("log_programa.log",  LOG_INFO,"---\n");
    }
    return lista_de_palavras_struct; // Indica que o programa terminou com sucesso
}

// Atualiza uma palavra existente no array
void atualiza_palavra(int is_print, const char *palavra_anterior, const char *nova_palavra){
    if (nova_palavra == NULL || palavra_anterior == NULL){
        log_to_file("log_programa.log", LOG_ERROR, "Palavras nao passadas na funcao\n");
        print_erro(is_print,"As palavras não foram informadas...\n");
        return;
    }
    if (palavra_existe(nova_palavra) == 1){
        print_aviso(is_print,"Palavra '%s' ja existe na lista de palavras...\n",nova_palavra);
        return;
    }
    int index = -1, tamanho_anterior, tamanho_nova;
    for (int i = 0; i < num_textos; i++){
        if(strcmp(textos[i],palavra_anterior) ==0){
            index = i;
            break;
        }
    }
    if (index == -1){
        print_aviso(is_print,"Palavra '%s' não existe na lista de palavras...\n",palavra_anterior);
        return;
    }
    if (strlen(nova_palavra) < 5 || strlen(nova_palavra) > 20) {
        log_to_file("log_programa.log", LOG_ERROR, "Nova palavra fora do range de 5 a 20 caracteres\n");
        print_erro(is_print,"A nova palavra '%s' está fora do range de 5 a 20 caracteres\n", nova_palavra);
        return;
    }
    char *temp = (char*) realloc(textos[index], strlen(nova_palavra) + 1);
    if (temp == NULL){
        log_to_file("log_programa.log", LOG_ERROR, "Erro ao alocar memória para atualizar a palavra\n");
        print_erro(is_print,"Houve um erro ao atualizar a palavra '%s'\n", nova_palavra);
        return;
    }
    textos[index] = temp;
    strcpy(textos[index], nova_palavra);

    log_to_file("log_programa.log", LOG_INFO, "Palavra '%s' atualizada para '%s'\n", palavra_anterior, nova_palavra);
    print_sucesso(is_print,"Palavra '%s' atualizada para '%s'\n", palavra_anterior, nova_palavra);
}