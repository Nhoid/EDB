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
    size_t len = strlen(filename);
    return len >= 4 && strcmp(&filename[len - 4], ".csv") == 0;
}

void exibirMenu(){
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
    printf("Digite a opção desejada: ");
}

void exibirMenuEstatisticas(){
    printf("============================================\n");
    printf("            MENU DE ESTATISTICAS            \n");
    printf("============================================\n");
    printf("1. 10 numeros mais sorteados\n");
    printf("2. 10 numeros menos sorteados\n");
    printf("3. Quantidade de repeticao de um numero\n");
    printf("4. Sorteios realizado em determinado ano\n");
    printf("0. Sair\n");
    printf("============================================\n");
    printf("Digite a opção desejada: ");
}

void inserirConcurso(HashTable* hash, Estatisticas* estatisticas) {
    char data[11];
    unsigned int numero;
    int bolas[6];

    printf("Para inserir um novo concurso precisamos de alguns dados dele.\n");
    printf("Digite o numero do concurso: ");
    scanf("%d", &numero);
    getchar();
    printf("Seguindo a formatacao, coloque a data (dd-mm-yyyy): ");
    scanf("%10s", data);
    getchar();
    printf("Em sequencia, coloque as bolas sorteadas:\n");
    for (int i = 0; i < 6; i++){
        printf("Bola %d: ", i + 1);
        scanf("%d", &bolas[i]);
        getchar();
    }
    
    addElement(hash, concursoBuilder(numero, data, bolas));

    contarBolas(bolas, estatisticas);

    printf("Concurso adicionado com sucesso.\n");
}

void buscarConcurso(HashTable* hash) {

    unsigned int key;

    printf("Digite o numero do concurso que voce quer buscar: ");
    scanf("%d", &key);

    Concurso* concurso = search(hash, key);

    if (concurso == NULL) {
        printf("Concurso nao encontrado.\n");
        return;
    }

    printConcurso(concurso);
    printf("\n");
}

void removerConcurso(HashTable* hash, Estatisticas* estatisticas) {

    unsigned int key;

    printf("Digite o numero do concurso que voce quer remover: ");
    scanf("%d", &key);

    Concurso* concurso = search(hash, key);

    if (concurso != NULL) diminuirEstatisticas(concurso->bolas, estatisticas);

    removeFromHash(hash, key);
}

void printConcursos(HashTable* hash) {
    printHashTable(hash);
}

int contarlinhas(char* fileName) {

    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return -1;
    }

    int lines = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }

    fclose(file);

    return lines;

}

Concurso* processarString(char* string, bool csv) {
    unsigned int key;
    char data[11];
    int bolas[6];

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

    data[11] = '\0';

    return concursoBuilder(key, data, bolas);
}

void lerArquivo(HashTable* hash, char* filename, Estatisticas* estatisticas) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    bool csv = isCSV(filename);

    bool cabecalho = true;

    char *line = (char *)malloc(MAX_LINE_LENGTH);

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {

        if (!cabecalho){

            line[strcspn(line, "\n")] = 0;

            Concurso* concurso = processarString(line, csv);

            contarBolas(concurso->bolas, estatisticas);

            addElement(hash, concurso);

        } else {
            cabecalho = false;
        }
    }

    free(line);
    fclose(file);
}

HashTable* carregarArquivo(Estatisticas* estatisticas) {

    char* filename = (char*) calloc(100, sizeof(char));

    printf("Qual o nome do arquivo que voce quer carregar (diretorio/arquivo)? ");
    scanf("%98[^\n]", filename);

    filename[99] = '\0';

    printf("%s\n", filename);

    int tamanho = contarlinhas(filename);

    HashTable* hash = hashBuilder(tamanho);

    lerArquivo(hash, filename, estatisticas);

    return hash;

}

HashTable* iniciarArquivo(char* filename, Estatisticas* estatisticas){

    int tamanho = contarlinhas(filename);

    HashTable* hash = hashBuilder(tamanho);

    lerArquivo(hash, filename, estatisticas);

    return hash;
}

void contarBolas(int bolas[], Estatisticas* estatisticas) {
    for (int i = 0; i < 6; i++) {
        estatisticas[bolas[i]-1].repeticao++;
    }
}

void diminuirEstatisticas(int bolas[], Estatisticas* estatisticas) {
    for (int i = 0; i < 6; i++) {
        estatisticas[bolas[i]-1].repeticao--;
    }
}

Estatisticas* getBolas() {
    Estatisticas* bolas = (Estatisticas*) malloc(60 * sizeof(Estatisticas));

    for(int i = 0; i < 60; i++){
        bolas[i].bola = i+1;
        bolas[i].repeticao = 0;
    }

    return bolas;
}

void limparEstatisticas(Estatisticas* estatisticas) {
    for (int i = 0; i < 60; i++)
        estatisticas[i].repeticao = 0;
}

void topMaisSorteados(Estatisticas* estatisticas) {
    printf("Numeros mais sorteados:\n");
    for(int i = 59; i >= 50; i--){
        printf("%d - bola %d: %d\n", 60-i ,estatisticas[i].bola, estatisticas[i].repeticao);
    }
}

void topMenosSorteados (Estatisticas* estatisticas) {
    printf("\nNumeros menos sorteados:\n");
    for(int i = 9; i >= 0; i--){
        printf("%d - bola %d: %d\n", 60-i ,estatisticas[i].bola, estatisticas[i].repeticao);
    }
}

void quantidadeRepeticao(Estatisticas* estatisticas) {
    int bola = -1;
    printf("Qual numero voce quer ver? ");
    scanf("%d", &bola);
    getchar();

    if (bola > 60 || bola < 1){
        printf("Numero invalido.\n");
        return;
    }

    printf("bola %d: %d\n",bola, estatisticas[bola-1].repeticao);
}

void sorteiosPorAno(HashTable* hash){
    char ano[5];
    printf("Qual ano voce quer ver os concursos? ");
    scanf("%4s", ano);
    getchar();

    ano[4] = '\0';

    char completo[11];
    sprintf(completo, "01-01-%s", ano);

    completo[10] = '\0';

    Data data = dataBuilder(completo);

    for(unsigned int i = 0; i < hash->capacity; i++){

        LinkedList* list = hash->entries[i].list;

        if (list == NULL || list->size == 0) continue;

        NodeList* pointer = list->header;

        while (pointer != NULL && pointer->element != NULL) {

            if (sameYear(pointer->element->data, data)) {
                printConcurso(pointer->element);
                printf("\n");
            }

            pointer = pointer->next;
        }

    }
}

void apresentarEstatisticas(HashTable* hash, Estatisticas* original){

    // debug
    // for (int i = 0; i < 60; i++) {
    //     printf("%d - bola %d: %d\n", i ,original[i].bola, original[i].repeticao);
    // }

    Estatisticas estatisticas[60];

    memcpy(estatisticas, original, 60 * sizeof(Estatisticas));

    insertionSort(estatisticas);

    int opcao;

    do {
        exibirMenuEstatisticas();
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 0:
                break;
            case 1:
                topMaisSorteados(estatisticas);
                break;
            case 2:
                topMenosSorteados(estatisticas);
                break;
            case 3:
                quantidadeRepeticao(original);
                break;
            case 4:
                sorteiosPorAno(hash);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}

void insertionSort(Estatisticas* arr) {
    for (int i = 1; i < 60; i++) {
        Estatisticas key = arr[i];
        int j = i - 1;

        // Move os elementos de arr[0..i-1] que são maiores que key.repeticao
        // para uma posição à frente da sua posição atual
        while (j >= 0 && arr[j].repeticao > key.repeticao) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}