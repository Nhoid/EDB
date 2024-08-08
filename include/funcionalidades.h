#ifndef FUNCIONALIDADES_H
#define FUNCIONALIDADES_H

void exibirMenu();

string* anotarPedido (char pedidoChar[], LinkedList* cardapio); // funcao processar pedidos do usuario

void adicionarPedido(LinkedList* pedidos, Cardapio* cardapio); // funcao que recebe os pedidos do usuario

void removerPedido(LinkedList* pedidos); // funcao de remocao de prato de um pedido

void processarPedido(LinkedList* pedidos, Queue* emProcessamento); // envia o pedido mais antigo para a fila de processamento

void listarPedidosPendentes(LinkedList* pedidos); // printa todos os pedidos da lista

void listarPedidosEmProcessamento(Queue* emProcessamento); // printa todos os pedidos em processamento




#endif // FUNCIONALIDADES_H