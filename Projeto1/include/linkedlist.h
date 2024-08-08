#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>


#include "../include/structstring.h"

typedef struct NodeList NodeList;

typedef struct NodeList{

    string element;

    NodeList* next;
    NodeList* prev;

}NodeList; // Elemento da Lista

typedef struct{

    NodeList* header; // Sentinela head

    NodeList* tail; // Sentinela tail

    int size; // tamanho da lista

}LinkedList;

LinkedList* builderList(); // Retorna uma LinkedList

NodeList* buildNodeList(char* string); // Recebe um array de char e retorna um Node
void eraseNodeList(NodeList* node); // Apaga um Node da memoria

void removeNode(LinkedList* linkedList, NodeList* node); // Só precisa saber o Node que será apagado, ja que ele irá saber sua propria posição
void addNodeAfter(LinkedList* linkedList, NodeList* fromlist, NodeList* newNode); // Adicionar em uma posição especifica da lista

void addNodeAtFirst(LinkedList* linkedlist, NodeList* node); // Necessita saber a lista onde vai ser adicionado o dado por primeiro
void addNodeAtLast(LinkedList* linkedlist, NodeList* node); // Necessita saber a lista onde vai ser adicionado o dado por ultimo
void removeAtFirst(LinkedList* linkedList); // Remove o primeito elemento de uma lista
void removeAtLast(LinkedList* linkedList); // remove o ultimo elemento da lista

NodeList* searchByData(const LinkedList* linkedlist, const char* string); // Procurar um node pelo conteúdo
NodeList* searchByIndex(const LinkedList* linkedlist, int index); // Procura um node com base no seu index
NodeList* getFirst(const LinkedList* linkedlist); // Pega o primeiro elemento
NodeList* getLast(const LinkedList* linkedlist); // Pega o ultimo elemento

int printList(const LinkedList* linkedlist); // printa a lista

bool isListEmpty(const LinkedList* linkedlist); // verifica se tem algum elemento na lista

void clearLinkedList(LinkedList* linkedList); // Deleta uma lista

#endif // LINKEDLIST_H