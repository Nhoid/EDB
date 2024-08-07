#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// includes personalizados
#include "../include/structstring.h"
#include "../include/linkedlist.h"
#include "../include/cardapio.h"
#include "../include/queue.h"


void exibirMenu() {
    printf("+----------------------------------+\n");
    printf("|          MENU PRINCIPAL           |\n");
    printf("+----------------------------------+\n");
    printf("| 1. Adicionar Pedido               |\n");
    printf("| 2. Remover Pedido                 |\n");
    printf("| 3. Processar Pedido               |\n");
    printf("| 4. Listar Pedidos Pendentes       |\n");
    printf("| 5. Listar Pedidos em Processamento|\n");
    printf("| 0. Sair                           |\n");
    printf("+----------------------------------+\n");
}

string* anotarPedido (char pedidoChar[], LinkedList* cardapio){
    int numberoPedido = -1;
    char* token;
    char* endptr;

    string* pedido = stringEmpty();

    token = strtok(pedidoChar, ",");

    while (token != NULL) {

        numberoPedido = strtol(token, &endptr, 10);

        if (numberoPedido == 0) break; // cliente nao quer pedir nada

        if (numberoPedido > 5 || numberoPedido < 1){

            printf("Numero de pedido %d eh invalido, sera ignorado.\n", numberoPedido);

        }else {

            NodeList* node = searchByIndex(cardapio, numberoPedido-1);

            concat(pedido, &node->element);

        }
        token = strtok(NULL, ",");
    }


    return pedido;
}

void adicionarPedido(LinkedList* pedidos, Cardapio* cardapio) {

    char* pedido = (char*) malloc(sizeof(char) * 30);

    string* pedidoCompleto = stringEmpty();

    printf("Escolha os pratos de entrada\n");
    printf("Se voce quiser pedir mais de um, separe os numeros por ','. Se nao quiser digite 0): ");
    scanf("%29s", pedido);
    getchar(); // pegar entrada fantasma
    concat(pedidoCompleto, anotarPedido(pedido, cardapio[0].lista));
    printf("Escolha os pratos principais\n");
    printf("Se voce quiser pedir mais de um, separe os numeros por ','. Se nao quiser digite 0): ");
    scanf("%29s", pedido);
    getchar(); // pegar entrada fantasma
    concat(pedidoCompleto, anotarPedido(pedido, cardapio[1].lista));
    printf("Escolha as sobremesas\n");
    printf("Se voce quiser pedir mais de um, separe os numeros por ','. Se nao quiser digite 0): ");
    scanf("%29s", pedido);
    getchar(); // pegar entrada fantasma
    concat(pedidoCompleto, anotarPedido(pedido, cardapio[2].lista));

    addNodeAtLast(pedidos, buildNodeList(pedidoCompleto->text) );

    // limpar memoria
    free(pedido); 
    eraseString(pedidoCompleto);
}

void removerPedido(LinkedList* pedidos) {

    char prato[100] = "";
    int indice = 0;

    printf("PEDIDOS:\n");
    printList(pedidos);
    printf("\n");

    printf("Escreva o numero do pedido que voce quer remover um prato e o prato que vc quer remover.\n");
    printf("Digite '0' no numero do pedido para cancelar a remocao do pedido.\n");
    printf("Numero do pedido: ");

    scanf("%d", &indice);
    getchar();

    if (indice == 0) return;

    printf("Nome do prato: ");
    scanf("%99[^\n]", prato);
    getchar();

    if (prato == "") return;

    string* newString = stringBuilder(prato);

    NodeList* node = searchByIndex(pedidos, indice-1);

    removeSubString(&node->element, newString);

    printf("%d\n", node->element.length);

    if (node->element.length == 0) removeNode(pedidos, node);

    eraseString(newString);
}

void processarPedido(LinkedList* pedidos, Queue* emProcessamento) {
    if(isListEmpty(pedidos)) {
        printf("Nao tem nenhum pedido para ser processado.\n");
        return;
    }

    enqueue(emProcessamento, buildNodeQueue( getFirst(pedidos)->element.text )); // passa o pedido para emProcessamento

    removeAtFirst(pedidos);

    printf("Pedido %s em processamento...\n", front(emProcessamento)->element.text );
}

void listarPedidosPendentes(LinkedList* pedidos) {
    if ( printList(pedidos) == 0 ){
        printf("Nenhum pedido pendente.\n");
    }
}

void listarPedidosEmProcessamento(Queue* emProcessamento) {
    if ( printQueue(emProcessamento) == 0 ) {
        printf("Nenhum pedido pendente.\n");
    };
}

int main(){

    Cardapio* cardapio = cardapio_builder(); // indice 0 entrada, 1 principais, 2 sobremesa

    LinkedList* pedidos = builderList(); // vai guardar os pedido

    Queue* emProcessamento = builderQueue(); // vai guardar os pedidos em processamento

    int opcao = -1;

    while (opcao != 0){

        exibirMenu(); // menu

        scanf("%d", &opcao);

        getchar();

        switch (opcao) {

            case 0:
                break;
            case 1:
                mostrarCardapio(cardapio);
                adicionarPedido(pedidos, cardapio);
                break;
            case 2:
                removerPedido(pedidos);
                break;
            case 3:
                processarPedido(pedidos, emProcessamento);
                break;
            case 4:
                listarPedidosPendentes(pedidos);
                break;
            case 5:
                listarPedidosEmProcessamento(emProcessamento);
                break;
        }

    }


    return 0;
}