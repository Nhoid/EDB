#include "../include/cardapio.h"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/linkedlist.h"
#include "../include/structstring.h"

// cria a lista de entradas
LinkedList* entradas(){

    LinkedList* entrada = builderList();

    addNodeAtFirst(entrada, buildNodeList("Sopa de Cebola"));
    addNodeAtLast(entrada, buildNodeList("Salada Caesar"));
    addNodeAtLast(entrada, buildNodeList("Bruschetta"));
    addNodeAtLast(entrada, buildNodeList("Carpaccio de Carne"));
    addNodeAtLast(entrada, buildNodeList("Camarao ao Alho"));

    return entrada;
}
// cria a lista dos principais
LinkedList* principais() {

    LinkedList* principais = builderList();

    addNodeAtFirst(principais, buildNodeList("Lasanha a Bolonhesa"));
    addNodeAtLast(principais, buildNodeList("File Mignon com Fritas"));
    addNodeAtLast(principais, buildNodeList("Frango Grelhado com Legumes"));
    addNodeAtLast(principais, buildNodeList("Bacalhau a Gomes de Sa"));
    addNodeAtLast(principais, buildNodeList("Risoto de Cogumelos"));

    return principais;
}
// cria a lista das sobremesas
LinkedList* sobremesas() {
    LinkedList* sobremesa = builderList();

    addNodeAtFirst(sobremesa, buildNodeList("Tiramisu"));
    addNodeAtLast(sobremesa, buildNodeList("Cheesecake de Frutas Vermelhas"));
    addNodeAtLast(sobremesa, buildNodeList("Mousse de Chocolate"));
    addNodeAtLast(sobremesa, buildNodeList("Pudim de Leite"));
    addNodeAtLast(sobremesa, buildNodeList("Sorvete de Baunilha com Calda de Morango"));

    return sobremesa;
}

// cria cardapio
Cardapio* cardapio_builder() {

    Cardapio* cardapio = (Cardapio*)malloc(3 * sizeof(Cardapio)); // aloca tamanho suficiente

    if (!cardapio) { // verifica se a alocacao foi bem sucessida
        printf("Erro ao criar cardapio\n");
        return NULL;
    }

    // Inicializar o array de Cardapio
    cardapio[0].lista = entradas();
    cardapio[0].nome = strdup("ENTRADA");
    cardapio[1].lista = principais();
    cardapio[1].nome = strdup("PRINCIPAIS");
    cardapio[2].lista = sobremesas();
    cardapio[2].nome = strdup("SOBREMESAS");

    return cardapio;
}

int max(int a, int b) { // funcao auxiliar
    return a > b ? a : b;
}

void espacamento(int espaco){ // funcao auxiliar
    while (espaco > 0) {
        printf(" ");
        espaco--;
    }  
}

void mostrarCardapio(Cardapio* cardapio) {

    // pega listas de pratos
    LinkedList* entradas = cardapio[0].lista;
    LinkedList* principais = cardapio[1].lista;
    LinkedList* sobremesas = cardapio[2].lista;

    // Calcular o numero maximo de itens entre as tres listas, caso tenham modificado o cardapio original
    int i = max(sobremesas->size, max(entradas->size, principais->size));

    int numeroEntrada = 1, numeroPrincipal = 1, numeroSobremesa = 1; // numero do pedido, para adicionar os indices dos pedidos

    // Definir o espaço maximo para cada coluna
    int larguraColuna = 40;

    // Imprimir cabeçalhos
    printf("ENTRADA:");
    espacamento(larguraColuna - 8);
    printf("PRINCIPAL:");
    espacamento(larguraColuna - 10);
    printf("SOBREMESA:\n");

    // Inicializar ponteiros para percorrer as listas
    NodeList* pointerEntradas = getFirst(entradas);
    NodeList* pointerPrincipais = getFirst(principais);
    NodeList* pointerSobremesas = getFirst(sobremesas);

    // Percorrer as listas e imprimir os itens
    while (i > 0) {
        // Verificar e imprimir entrada
        if (pointerEntradas != entradas->tail) {
            printf("%d - %s", numeroEntrada,pointerEntradas->element.text);
            espacamento(larguraColuna - pointerEntradas->element.length - 4);
            pointerEntradas = pointerEntradas->next;
            numeroEntrada++;
        } else {
            espacamento(larguraColuna);
        }

        // Verificar e imprimir principal
        if (pointerPrincipais != principais->tail) {
            printf("%d - %s", numeroPrincipal, pointerPrincipais->element.text);
            espacamento(larguraColuna - pointerPrincipais->element.length - 4);
            pointerPrincipais = pointerPrincipais->next;
            numeroPrincipal++;
        } else {
            espacamento(larguraColuna);
        }

        // Verificar e imprimir sobremesa
        if (pointerSobremesas != sobremesas->tail) {
            printf("%d - %s", numeroSobremesa, pointerSobremesas->element.text);
            espacamento(larguraColuna - pointerSobremesas->element.length - 4);
            pointerSobremesas = pointerSobremesas->next;
            numeroSobremesa++;
        } else {
            espacamento(larguraColuna);
        }

        printf("\n");
        i--;
    }
}