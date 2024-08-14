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

    int size = 50; // tamanho padrao

    bool file = false; // verifica se foi passado arquivo como argumento

    // processamento de entrada
    if (strcmp(args[1], "-s") == 0) {
        size = atoi(args[2]);
    }

    if (strcmp(args[1], "-f") == 0) {
        size = contarlinhas(args[2]) + 1;
        file = true;
    }

    Estatisticas* bolas = getBolas(); // responsavel por guardar estatisticas

    HashTable* hash; // tabela hash

    if (file) hash = iniciarArquivo(args[2], bolas); // le arquivo
    else hash = hashBuilder(size); // se nao for passado nenhum arquivo como parametro

    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 0:
                break;
            case 1:
                inserirConcurso(hash, bolas);
                break;
            case 2:
                buscarConcurso(hash);
                break;
            case 3:
                removerConcurso(hash, bolas);
                break;
            case 4:
                printConcursos(hash);
                break;
            case 5:
                clearHashTable(hash);
                limparEstatisticas(bolas);
                hash = carregarArquivo(bolas);
                break;
            case 6:
                apresentarEstatisticas(hash, bolas);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;

}