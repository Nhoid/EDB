#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>

#include "concurso.h"

typedef struct NodeList NodeList;

typedef struct NodeList{

    Concurso* element;

    NodeList* next;

}NodeList; // Elemento da Lista

typedef struct {

    NodeList* header;

    NodeList* tail;

    int size;

} LinkedList;

LinkedList* builderList(); // Retorna uma LinkedList

NodeList* nodeListBuilder(Concurso* concurso); // cria um no com um concurso

void eraseNodeList(NodeList* node); // Apaga um Node da memoria

void removeNode(LinkedList* list, NodeList* node); // Só precisa saber o Node que será apagado, ja que ele irá saber sua propria posição
void addNodeAfter(LinkedList* list, NodeList* fromlist, NodeList* newNode); // Adicionar em uma posição especifica da list

void addNodeAtFirst(LinkedList* list, NodeList* node); // Necessita saber a lista onde vai ser adicionado o dado por primeiro
void addNodeAtLast(LinkedList* list, NodeList* node); // Necessita saber a lista onde vai ser adicionado o dado por ultimo
void removeAtFirst(LinkedList* list); // Remove o primeito elemento de uma lista
void removeAtLast(LinkedList* list); // remove o ultimo elemento da lista

NodeList* searchById(const LinkedList* list, unsigned int concurso); // Procurar um node pelo conteúdo

int printList(const LinkedList* list); // printa a lista

bool isListEmpty(LinkedList* list); // verifica se tem algum elemento na lista

void clearLinkedList(LinkedList* list); // Deleta uma lista

#endif // LINKEDLIST_H