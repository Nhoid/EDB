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
    if (len < 4) return false;

    char extension[5];  // 4 characters + 1 for the null terminator
    strncpy(extension, &filename[len - 4], 4);
    extension[4] = '\0';  // Ensure null termination

    printf("%s\n", extension);

    return strcmp(extension, ".csv") == 0;
}

bool isTSV(const char* filename) {
    size_t len = strlen(filename);
    if (len < 4) return false;

    char extension[5];
    strncpy(extension, &filename[len - 4], 4);
    extension[4] = '\0';

    printf("%s\n", extension);

    return strcmp(extension, ".tsv") == 0;
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

Concurso* processarString(char* string, char delimitador) {
    unsigned int key;
    char* data;
    int bolas[6];

    char* token;
    
    token = strtok(string, delimitador);

    key = atoi(token);

    token = strtok(NULL, delimitador);
    
    data = strdup(token);

    token = strtok(NULL, delimitador);

    for (int i = 0; i < 6; i++){
        bolas[i] = atoi(token);
        token = strtok(NULL, delimitador);
    }
    
    return concursoBuilder(key, data, bolas);
}

void lerArquivo(HashTable* hash, char* filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    char delimitador;

    if (isCSV(filename)) delimitador = ",";
    else if (isTSV(filename)) delimitador = " ";
    else {
        printf("Tipo de arquivo nao suportado\n");
        return;
    }

    printf("%c\n", delimitador);

    bool cabecalho = true;

    char *line = (char *)malloc(MAX_LINE_LENGTH);

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {

        if (!cabecalho){

            line[strcspn(line, "\n")] = 0;

            addElement(hash, processarString(line, delimitador));

        } else {
            cabecalho = false;
        }
    }

    free(line);
    fclose(file);
}

HashTable* carregarArquivo() {

    char* filename;

    printf("Qual o nome do arquivo que voce quer carregar (diretorio/arquivo)? ");
    scanf("%99s", filename);

    int tamanho = contarlinhas(filename);

    HashTable* hash = hashBuilder(tamanho);

    lerArquivo(hash, filename);

    return hash;

}