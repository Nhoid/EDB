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

void exibirMenu(){
    printf("============================================\n");
    printf("              MENU DE CONCURSOS            \n");
    printf("============================================\n");
    printf("1. Inserir Concurso\n");
    printf("2. Buscar Concurso\n");
    printf("3. Remover Concurso\n");
    printf("4. Visualizar Todos os Concursos\n");
    printf("============================================\n");
    printf("Digite a opção desejada: ");
}

void inserirConcurso(HashTable* hash) {
    char data[11];
    unsigned int numero;
    int bolas[6];

    printf("Para inserir um novo concurso precisamos de alguns dados dele.\n");
    printf("Digite o numero do concurso: ");
    scanf("%d", &numero);
    printf("Seguindo a formatacao, coloque a data (dd-mm-yyyy): ");
    scanf("%10s", data);
    printf("Em sequencia, coloque as bolas sorteadas:\n");
    for (int i = 0; i < 6; i++){
        printf("Bola %d: ", i + 1);
        scanf("%d", &bolas[i]);
    }
    
    addElement(hash, concursoBuilder(numero, data, bolas));

    printf("Concurso adicionado com sucesso.\n");
}

void buscarConcurso(HashTable* hash) {

    unsigned int key;

    printf("Digite o numero do concurso que voce quer buscar: ");
    scanf("%d", &key);

    Concurso* concurso = search(hash, key);

    printConcurso(concurso);
    printf("\n");
}

void removerConcurso(HashTable* hash) {

    unsigned int key;

    printf("Digite o numero do concurso que voce quer remover: ");
    scanf("%d", &key);

    removeFromHash(hash, key);
}

void printConcursos(HashTable* hash) {
    printHashTable(hash);
}

int contarlinhas(char* fileName) {

    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
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

Concurso* processarString(char* string) {
    unsigned int key;
    char* data;
    int bolas[6];

    char* token;
    
    token = strtok(string, ",");

    key = atoi(token);

    token = strtok(NULL, ",");
    
    data = strdup(token);

    token = strtok(NULL, ",");

    for (int i = 0; i < 6; i++){
        bolas[i] = atoi(token);
        token = strtok(NULL, ",");
    }
    
    return concursoBuilder(key, data, bolas);
}

void lerArquivo(HashTable* hash, char* filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    bool cabecalho = true;

    char *line = (char *)malloc(MAX_LINE_LENGTH);

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {

        if (!cabecalho){

            line[strcspn(line, "\n")] = 0;

            addElement(hash, processarString(line));

        } else {
            cabecalho = false;
        }
    }

    free(line);
    fclose(file);
}

int main(int argv, char* args[]) {

    int size = 50;
    bool file = false;

    if (strcmp(args[1], "-s") == 0) {
        size = atoi(args[2]);
    }

    if (strcmp(args[1], "-f") == 0) {
        size = contarlinhas(args[2]) + 1;
        file = true;

    }

    HashTable* hash = hashBuilder(size);

    if (file) lerArquivo(hash, args[2]);

    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirConcurso(hash);
                break;
            case 2:
                buscarConcurso(hash);
                break;
            case 3:
                removerConcurso(hash);
                break;
            case 4:
                printConcursos(hash);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;

}