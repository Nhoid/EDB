#ifndef CARDAPIO_H
#define CARDAPIO_H

#include "../include/linkedlist.h"

typedef struct Cardapio {
    LinkedList* lista;
    char* nome; // Nome para identificar o tipo de lista (por exemplo, "Entradas", "Principais", "Sobremesas")
} Cardapio;

LinkedList* entradas(); // funcao que gera os pratos de entrada

LinkedList* principais(); // funcao que gera os pratos de entrada

LinkedList* sobremesas(); // funcao que gera os pratos de entrada

void espacamento(int espaco); // funcao auxiliar para formatacao do cardapio

Cardapio* cardapio_builder(); // funcao que retorna o cardapio

void mostrarCardapio(Cardapio* cardapio); // funcao que mostra o cardapio

#endif // CARDAPIO_H