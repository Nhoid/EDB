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

#include "../include/funcionalidades.h"

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
            case 5:
                clearHashTable(hash);
                hash = carregarArquivo(hash);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;

}