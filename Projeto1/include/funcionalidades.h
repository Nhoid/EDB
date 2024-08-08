#ifndef FUNCIONALIDADES_H
#define FUNCIONALIDADES_H

#include "../include/structstring.h"
#include "../include/linkedlist.h"
#include "../include/cardapio.h"
#include "../include/queue.h"

void exibirMenu();

string* anotarPedido (char pedidoChar[], LinkedList* cardapio); // funcao processar pedidos do usuario

void adicionarPedido(LinkedList* pedidos, Cardapio* cardapio); // funcao que recebe os pedidos do usuario

void removerPedido(LinkedList* pedidos); // funcao de remocao de prato de um pedido

void esperarCozinha(Queue* emProcessamento); // faz com que a cozinha libere um pedido e a fila ande

void processarPedido(LinkedList* pedidos, Queue* emProcessamento); // envia o pedido mais antigo para a fila de processamento

void listarPedidosPendentes(LinkedList* pedidos); // printa todos os pedidos da lista

void listarPedidosEmProcessamento(Queue* emProcessamento); // printa todos os pedidos em processamento




#endif // FUNCIONALIDADES_H