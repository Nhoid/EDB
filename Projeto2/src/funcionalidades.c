#include "../include/funcionalidades.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

// include personalizados
#include "../include/hashtable.h"
#include "../include/concurso.h"
#include "../include/linkedlist.h"
#include "../include/data.h"

bool isCSV(const char* filename) {
    // verifica se o arquivo tem pelo menos 4 caracteres e se a extensao e ".csv"
    size_t len = strlen(filename);
    return len >= 4 && strcmp(&filename[len - 4], ".csv") == 0;
}

void exibirMenu(){
    // exibe o menu principal com as opcoes disponiveis
    printf("============================================\n");
    printf("              MENU DE CONCURSOS            \n");
    printf("============================================\n");
    printf("1. Inserir Concurso\n");
    printf("2. Buscar Concurso\n");
    printf("3. Remover Concurso\n");
    printf("4. Visualizar Todos os Concursos\n");
    printf("5. Carregar arquivo\n");
    printf("6. Mostrar Estatisticas\n");
    printf("0. Sair\n");
    printf("============================================\n");
    printf("Digite a opcao desejada: ");
}

void exibirMenuEstatisticas(){
    // exibe o menu de estatisticas com as opcoes disponiveis
    printf("============================================\n");
    printf("            MENU DE ESTATISTICAS            \n");
    printf("============================================\n");
    printf("1. 10 numeros mais sorteados\n");
    printf("2. 10 numeros menos sorteados\n");
    printf("3. Quantidade de repeticao de um numero\n");
    printf("4. Sorteios realizado em determinado ano\n");
    printf("0. Sair\n");
    printf("============================================\n");
    printf("Digite a opcao desejada: ");
}

void inserirConcurso(HashTable* hash, Estatisticas* estatisticas) {
    // declara variaveis para armazenar os dados do novo concurso
    char data[11];
    unsigned int numero;
    int bolas[6];

    // solicita os dados do concurso ao usuario
    printf("Para inserir um novo concurso precisamos de alguns dados dele.\n");
    printf("Digite o numero do concurso: ");
    scanf("%d", &numero);
    getchar(); // limpa o buffer de entrada
    
    printf("Seguindo a formatacao, coloque a data (dd-mm-yyyy): ");
    scanf("%10s", data);
    getchar(); // limpa o buffer de entrada
    
    printf("Em sequencia, coloque as bolas sorteadas:\n");
    for (int i = 0; i < 6; i++){
        printf("Bola %d: ", i + 1);
        scanf("%d", &bolas[i]);
        getchar(); // limpa o buffer de entrada
    }
    
    // adiciona o concurso na hash table
    addElement(hash, concursoBuilder(numero, data, bolas));

    // atualiza as estatisticas com as bolas sorteadas
    contarBolas(bolas, estatisticas);

    // confirma que o concurso foi adicionado
    printf("Concurso adicionado com sucesso.\n");
}


void buscarConcurso(HashTable* hash) {
    // solicita o numero do concurso que o usuario deseja buscar
    unsigned int key;

    printf("Digite o numero do concurso que voce quer buscar: ");
    scanf("%d", &key);

    // busca o concurso na hash table usando a chave fornecida
    Concurso* concurso = search(hash, key);

    // verifica se o concurso foi encontrado
    if (concurso == NULL) {
        printf("Concurso nao encontrado.\n");
        return;
    }

    // imprime os detalhes do concurso encontrado
    printConcurso(concurso);
    printf("\n");
}

void removerConcurso(HashTable* hash, Estatisticas* estatisticas) {
    // solicita o numero do concurso que o usuario deseja remover
    unsigned int key;

    printf("Digite o numero do concurso que voce quer remover: ");
    scanf("%d", &key);

    // busca o concurso na hash table usando a chave fornecida
    Concurso* concurso = search(hash, key);

    // se o concurso foi encontrado, atualiza as estatisticas antes de removê-lo
    if (concurso != NULL) diminuirEstatisticas(concurso->bolas, estatisticas);

    // remove o concurso da hash table
    removeFromHash(hash, key);
}

void printConcursos(HashTable* hash) {
    // imprime todos os concursos armazenados na hash table
    printHashTable(hash);
}

int contarlinhas(char* fileName) {
    // abre o arquivo para leitura
    FILE *file = fopen(fileName, "r");

    // verifica se o arquivo foi aberto corretamente
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return -1;
    }

    // inicializa a contagem de linhas
    int lines = 0;
    char ch;

    // percorre o arquivo caractere por caractere contando as linhas
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }

    // fecha o arquivo
    fclose(file);

    // retorna o numero de linhas contadas
    return lines;
}


Concurso* processarString(char* string, bool csv) {
    // declara variaveis para armazenar os dados do concurso
    unsigned int key;
    char data[11];
    int bolas[6];

    // verifica o formato do arquivo, csv ou tsv, supondo que serao utilizados apenas esse tipo
    if (csv) {
        if (sscanf(string, "%u,%10[^,],%d,%d,%d,%d,%d,%d", &key, data, &bolas[0], &bolas[1], &bolas[2], &bolas[3], &bolas[4], &bolas[5]) != 8) {
            fprintf(stderr, "erro ao ler linha.\n");
            return NULL;
        }
    } else {
        if (sscanf(string, "%u\t%10s\t%d\t%d\t%d\t%d\t%d\t%d", &key, data, &bolas[0], &bolas[1], &bolas[2], &bolas[3], &bolas[4], &bolas[5]) != 8) {
            fprintf(stderr, "erro ao ler linha.\n");
            return NULL;
        }
    }

    // garante que a string da data esta corretamente terminada
    data[11] = '\0';

    // retorna um ponteiro para o novo concurso criado
    return concursoBuilder(key, data, bolas);
}

void lerArquivo(HashTable* hash, char* filename, Estatisticas* estatisticas) {
    // abre o arquivo para leitura
    FILE *file = fopen(filename, "r");

    // verifica se o arquivo foi aberto corretamente
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    // verifica se o arquivo e csv
    bool csv = isCSV(filename);

    // indica se o cabecalho ja foi processado
    bool cabecalho = true;

    // aloca memoria para a leitura das linhas do arquivo
    char *line = (char *)malloc(MAX_LINE_LENGTH);

    // le cada linha do arquivo
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {

        if (!cabecalho) {
            // remove o caractere de nova linha
            line[strcspn(line, "\n")] = 0;

            // processa a linha e cria um objeto Concurso
            Concurso* concurso = processarString(line, csv);

            // atualiza as estatisticas com as bolas sorteadas
            contarBolas(concurso->bolas, estatisticas);

            // adiciona o concurso na hash table
            addElement(hash, concurso);

        } else {
            // ignora o cabecalho
            cabecalho = false;
        }
    }

    // libera a memoria alocada para a leitura de linhas e fecha o arquivo
    free(line);
    fclose(file);
}

HashTable* carregarArquivo(Estatisticas* estatisticas) {
    // aloca memoria para o nome do arquivo
    char* filename = (char*) calloc(100, sizeof(char));

    // solicita o nome do arquivo ao usuario
    printf("Qual o nome do arquivo que voce quer carregar (diretorio/arquivo)? ");
    scanf("%98[^\n]", filename);

    // garante que a string do filename esta corretamente terminada
    filename[99] = '\0';

    printf("%s\n", filename);

    // conta o numero de linhas no arquivo
    int tamanho = contarlinhas(filename);

    // cria uma nova hash table com base no tamanho do arquivo
    HashTable* hash = hashBuilder(tamanho);

    // carrega os dados do arquivo para a hash table
    lerArquivo(hash, filename, estatisticas);

    return hash;
}


HashTable* iniciarArquivo(char* filename, Estatisticas* estatisticas) {
    // conta o numero de linhas no arquivo
    int tamanho = contarlinhas(filename);

    // cria uma nova hash table com base no tamanho do arquivo
    HashTable* hash = hashBuilder(tamanho);

    // carrega os dados do arquivo para a hash table
    lerArquivo(hash, filename, estatisticas);

    return hash;
}

void contarBolas(int bolas[], Estatisticas* estatisticas) {
    // incrementa o contador de repeticoes para cada bola sorteada
    for (int i = 0; i < 6; i++) {
        estatisticas[bolas[i]-1].repeticao++;
    }
}

void diminuirEstatisticas(int bolas[], Estatisticas* estatisticas) {
    // decrementa o contador de repeticoes para cada bola sorteada
    for (int i = 0; i < 6; i++) {
        estatisticas[bolas[i]-1].repeticao--;
    }
}

Estatisticas* getBolas() {
    // aloca memoria para armazenar as estatisticas de 60 bolas
    Estatisticas* bolas = (Estatisticas*) malloc(60 * sizeof(Estatisticas));

    // inicializa as estatisticas de cada bola com o numero e repeticao zero
    for(int i = 0; i < 60; i++){
        bolas[i].bola = i+1;
        bolas[i].repeticao = 0;
    }

    return bolas;
}

void limparEstatisticas(Estatisticas* estatisticas) {
    // reseta o contador de repeticoes para todas as bolas
    for (int i = 0; i < 60; i++)
        estatisticas[i].repeticao = 0;
}

void topMaisSorteados(Estatisticas* estatisticas) {
    // exibe os 10 numeros mais sorteados
    printf("Numeros mais sorteados:\n");
    for(int i = 59; i >= 50; i--){
        printf("%d - bola %d: %d\n", 60-i ,estatisticas[i].bola, estatisticas[i].repeticao);
    }
}

void topMenosSorteados (Estatisticas* estatisticas) {
    // exibe os 10 numeros menos sorteados
    printf("\nNumeros menos sorteados:\n");
    for(int i = 9; i >= 0; i--){
        printf("%d - bola %d: %d\n", 60-i ,estatisticas[i].bola, estatisticas[i].repeticao);
    }
}

void quantidadeRepeticao(Estatisticas* estatisticas) {
    int bola = -1;

    // solicita ao usuario para digitar o numero da bola que deseja consultar
    printf("Qual numero voce quer ver? ");
    scanf("%d", &bola);
    getchar();

    // verifica se o numero da bola esta dentro do intervalo valido
    if (bola > 60 || bola < 1) {
        printf("Numero invalido.\n");
        return;
    }

    // exibe a quantidade de vezes que a bola foi sorteada
    printf("bola %d: %d\n", bola, estatisticas[bola-1].repeticao);
}

void sorteiosPorAno(HashTable* hash) {
    char ano[5];

    // solicita ao usuario o ano desejado para visualizar os concursos
    printf("Qual ano voce quer ver os concursos? ");
    scanf("%4s", ano);
    getchar();

    ano[4] = '\0';

    char completo[11];
    sprintf(completo, "01-01-%s", ano);

    completo[10] = '\0';

    // cria uma data representando o inicio do ano solicitado
    Data data = dataBuilder(completo);

    // percorre a hash table para encontrar e exibir concursos do ano solicitado
    for(unsigned int i = 0; i < hash->capacity; i++) {

        LinkedList* list = hash->entries[i].list;

        // ignora listas vazias
        if (list == NULL || list->size == 0) continue;

        NodeList* pointer = list->header;

        // percorre a lista vinculada ao bucket atual
        while (pointer != NULL && pointer->element != NULL) {

            // verifica se o concurso pertence ao ano solicitado
            if (sameYear(pointer->element->data, data)) {
                printConcurso(pointer->element);
                printf("\n");
            }

            pointer = pointer->next;
        }
    }
}

void apresentarEstatisticas(HashTable* hash, Estatisticas* original) {

    // debug
    // descomente para visualizar as estatisticas antes da ordenacao
    // for (int i = 0; i < 60; i++) {
    //     printf("%d - bola %d: %d\n", i ,original[i].bola, original[i].repeticao);
    // }

    // cria uma copia das estatisticas originais para ordenar
    Estatisticas estatisticas[60];
    memcpy(estatisticas, original, 60 * sizeof(Estatisticas));

    // ordena as estatisticas pelo numero de repeticoes usando insertion sort
    insertionSort(estatisticas);

    int opcao;

    // menu para apresentar estatisticas
    do {
        exibirMenuEstatisticas();
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 0:
                // sai do menu de estatisticas
                break;
            case 1:
                // exibe os 10 numeros mais sorteados
                topMaisSorteados(estatisticas);
                break;
            case 2:
                // exibe os 10 numeros menos sorteados
                topMenosSorteados(estatisticas);
                break;
            case 3:
                // exibe a quantidade de repeticoes de um numero especifico
                quantidadeRepeticao(original);
                break;
            case 4:
                // exibe os concursos realizados em um ano especifico
                sorteiosPorAno(hash);
                break;
            default:
                // mensagem de erro para opcao invalida
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}

void insertionSort(Estatisticas* arr) {
    // ordena o array de Estatisticas em ordem crescente de repeticao
    for (int i = 1; i < 60; i++) {
        Estatisticas key = arr[i];
        int j = i - 1;

        // move os elementos maiores que key.repeticao para a direita
        while (j >= 0 && arr[j].repeticao > key.repeticao) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
