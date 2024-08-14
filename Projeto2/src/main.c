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
        // Define o tamanho da tabela hash baseado no argumento
        size = atoi(args[2]);
    }

    if (strcmp(args[1], "-f") == 0) {
        // Define o tamanho da tabela hash baseado no número de linhas do arquivo + 1
        size = contarlinhas(args[2]) + 1;
        file = true;
    }

    Estatisticas* bolas = getBolas(); // responsavel por guardar estatisticas

    HashTable* hash; // tabela hash

    if (file) 
        hash = iniciarArquivo(args[2], bolas); // le arquivo e inicializa a tabela hash
    else 
        hash = hashBuilder(size); // se nao for passado nenhum arquivo como parametro, cria uma tabela hash vazia

    int opcao;

    do {
        exibirMenu(); // exibe o menu principal
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
            case 0:
                break; // encerra o loop e o programa
            case 1:
                inserirConcurso(hash, bolas); // insere um novo concurso na tabela hash
                break;
            case 2:
                buscarConcurso(hash); // busca e exibe um concurso na tabela hash
                break;
            case 3:
                removerConcurso(hash, bolas); // remove um concurso da tabela hash
                break;
            case 4:
                printConcursos(hash); // imprime todos os concursos na tabela hash
                break;
            case 5:
                clearHashTable(hash); // limpa a tabela hash
                limparEstatisticas(bolas); // zera as estatisticas
                hash = carregarArquivo(bolas); // carrega novos dados da tabela hash a partir de um arquivo
                break;
            case 6:
                apresentarEstatisticas(hash, bolas); // exibe estatisticas dos concursos
                break;
            default:
                printf("Opção inválida. Tente novamente.\n"); // opção não reconhecida
                break;
        }
    } while (opcao != 0); // continua o loop até que a opção 0 seja selecionada

    return 0; // termina o programa
}
