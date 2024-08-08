#include "../include/funcionalidades.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/structstring.h"
#include "../include/linkedlist.h"
#include "../include/cardapio.h"
#include "../include/queue.h"


// menu de opcoes
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

// processa pedidos
string* anotarPedido (char pedidoChar[], LinkedList* cardapio){
    // variaveis auxiliares
    int numberoPedido = -1;
    char* token;
    char* endptr;

    string* pedido = stringEmpty(); // variavel que vai guardar os nomes dos pedidos

    token = strtok(pedidoChar, ","); // pega numero do pedido

    while (token != NULL) {

        numberoPedido = strtol(token, &endptr, 10);

        if (numberoPedido == 0) break; // cliente nao quer pedir nada

        if (numberoPedido > 5 || numberoPedido < 1){ // verifica se eh um pedido valido

            printf("Numero de pedido %d eh invalido, sera ignorado.\n", numberoPedido);

        }else {

            NodeList* node = searchByIndex(cardapio, numberoPedido-1); // busca nome do pedido no cardapio

            concat(pedido, &node->element); // adiciona pedido 

        }
        token = strtok(NULL, ",");
    }


    return pedido; // retorna
}

// funcao que recebe os pedidos do usuario
void adicionarPedido(LinkedList* pedidos, Cardapio* cardapio) {

    char* pedido = (char*) malloc(sizeof(char) * 30); // variavel para pegar entrada do usuario

    string* pedidoCompleto = stringEmpty(); // variavel que vai guardar todos os pedidos, entrada, principal e sobremesas

    printf("Escolha os pratos de entrada\n");
    printf("Se voce quiser pedir mais de um, separe os numeros por ','. Se nao quiser digite 0): ");
    scanf("%29s", pedido);
    getchar(); // pegar entrada fantasma
    // chama a funcao anotar pedido que retorna uma string* e ja concatena com pedido completo
    concat(pedidoCompleto, anotarPedido(pedido, cardapio[0].lista)); 
    printf("Escolha os pratos principais\n");
    printf("Se voce quiser pedir mais de um, separe os numeros por ','. Se nao quiser digite 0): ");
    scanf("%29s", pedido);
    getchar(); // pegar entrada fantasma
    // chama a funcao anotar pedido que retorna uma string* e ja concatena com pedido completo
    concat(pedidoCompleto, anotarPedido(pedido, cardapio[1].lista));
    printf("Escolha as sobremesas\n");
    printf("Se voce quiser pedir mais de um, separe os numeros por ','. Se nao quiser digite 0): ");
    scanf("%29s", pedido);
    getchar(); // pegar entrada fantasma
    // chama a funcao anotar pedido que retorna uma string* e ja concatena com pedido completo
    concat(pedidoCompleto, anotarPedido(pedido, cardapio[2].lista));

    addNodeAtLast(pedidos, buildNodeList(pedidoCompleto->text) ); // adiciona pedido completo na lsita

    // limpar memoria
    free(pedido); 
    eraseString(pedidoCompleto);
}

// funcao de remocao de prato de um pedido
void removerPedido(LinkedList* pedidos) {

    char prato[100] = ""; // variavel que ira pegar o prato a ser removido
    int indice = 0;  // variavel que ira pegar indice do pedido a ser modificado

    printf("PEDIDOS:\n");
    printList(pedidos);
    printf("\n");

    printf("Escreva o numero do pedido que voce quer remover um prato e o prato que vc quer remover.\n");
    printf("Digite '0' no numero do pedido para cancelar a remocao do pedido.\n");
    printf("Numero do pedido: ");

    scanf("%d", &indice); // pega o indice
    getchar();

    if (indice == 0) return; // cliente mudou de ideia

    printf("Nome do prato: "); 
    scanf("%99[^\n]", prato); // pega o nome do prato
    getchar();

    if (prato == "") return; // nao escolheu nenhum prato

    string* newString = stringBuilder(prato);

    NodeList* node = searchByIndex(pedidos, indice-1); // busca o pedido a ser modificado

    removeSubString(&node->element, newString); // modifica pedido

    if (node->element.length == 0) removeNode(pedidos, node); // caso tenha removido o ultimo prato do pedido, ele remove o pedido da lista

    eraseString(newString); // limpa memoria
}

// envia o pedido mais antigo para a fila de processamento
void processarPedido(LinkedList* pedidos, Queue* emProcessamento) {
    if(isListEmpty(pedidos)) { // verifica se tem algum pedido
        printf("Nao tem nenhum pedido para ser processado.\n");
        return;
    }

    // adiciona pedido na fila de processamento
    enqueue(emProcessamento, buildNodeQueue( getFirst(pedidos)->element.text )); // passa o pedido para emProcessamento

    removeAtFirst(pedidos); // remove pedido da lista de pedidos

    printf("Pedido %s em processamento...\n", front(emProcessamento)->element.text );
}

void listarPedidosPendentes(LinkedList* pedidos) {
    if ( printList(pedidos) == 0 ){ // chama a funcao de printar, se ela retornar 0 eh pq nao tinha nenhum pedido
        printf("Nenhum pedido pendente.\n");
    }
}

void listarPedidosEmProcessamento(Queue* emProcessamento) {
    if ( printQueue(emProcessamento) == 0 ) { // chama a funcao de printar, se ela retornar 0 eh pq nao tinha nenhum pedido
        printf("Nenhum pedido pendente.\n");
    };
}