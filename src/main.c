#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// includes personalizados
#include "../include/structstring.h"
#include "../include/linkedlist.h"
#include "../include/cardapio.h"
#include "../include/queue.h"

#include "../include/funcionalidades.h" // funcoes de menu


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
                adicionarPedido(pedidos, cardapio); // anota pedidos
                break;
            case 2:
                removerPedido(pedidos); // remove algum prato do pedido
                break;
            case 3:
                processarPedido(pedidos, emProcessamento); // envia o pedido mais antigo para a fila de processamento
                break;
            case 4:
                esperarCozinha(emProcessamento); // espera a cozinha liberar o primeiro prato da fila
                break;    
            case 5:
                listarPedidosPendentes(pedidos); // printa todos os pedidos
                break;
            case 6:
                listarPedidosEmProcessamento(emProcessamento); // printa a todos os pedidos na fila de processamento
                break;
        }

    }


    return 0;
}