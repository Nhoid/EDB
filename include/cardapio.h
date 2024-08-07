#ifndef CARDAPIO_H
#define CARDAPIO_H

#include "../include/linkedlist.h"

typedef struct Cardapio {
    LinkedList* lista;
    char* nome; // Nome para identificar o tipo de lista (por exemplo, "Entradas", "Principais", "Sobremesas")
} Cardapio;

LinkedList* entradas();

LinkedList* principais();

LinkedList* sobremesas();

void espacamento(int espaco);

Cardapio* cardapio_builder();

void mostrarCardapio(Cardapio* cardapio);

#endif // CARDAPIO_H