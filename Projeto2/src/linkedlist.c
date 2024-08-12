#include "../include/linkedlist.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../include/concurso.h"

NodeList* nodeListBuilder(Concurso* concurso){
    NodeList* node = (NodeList*) malloc(sizeof(NodeList));

    node->element = concurso;

    node->next = NULL;

    return node;
}

LinkedList* builderList() {
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));

    list->header = (NodeList*) malloc(sizeof(NodeList));
    list->tail = (NodeList*) malloc(sizeof(NodeList));

    list->header->element = NULL;
    list->tail->element = NULL;

    list->tail->next = NULL;
    list->header->next = list->tail;

    list->size = 0;

    return list;
}

void eraseNodeList(NodeList* node) {
    free(node->element);
    free(node->next);
}

void removeNode(LinkedList* list, NodeList* node) {

    if (node == NULL || list == NULL) return;

    NodeList* pointer = list->header;

    if (pointer == node) {
        removeAtFirst(list);
        return;
    }

    while ( pointer->next != node  && pointer->next != NULL){
        pointer = pointer->next;
    }

    if ( pointer->next == NULL ) {
        printf("Concurso nao encontrado.\n");
        return;
    }

    if (list->tail == node) list->tail = pointer;
    else pointer->next = node->next;

    node->next = NULL;

    list->size--;

    eraseNodeList(node);
}

void addNodeAfter(LinkedList* list, NodeList* fromlist, NodeList* newNode) {

    if (list->size == 0){
        addNodeAtFirst(list, newNode);
        return;
    }

    newNode->next = fromlist->next;

    fromlist->next = newNode;

    list->size++;
}

void addNodeAtFirst(LinkedList* list, NodeList* node) {

    node->next = list->header;

    list->header = node;

    list->size++;
}

void addNodeAtLast(LinkedList* list, NodeList* node) {
    addNodeAfter(list, list->tail, node);
}

void removeAtLast(LinkedList* list) {
    removeNode(list, list->tail);
}

void removeAtFirst(LinkedList* list) {
    NodeList* node = list->header;

    list->header = node->next;

    list->size--;

    node->next = NULL;

    eraseNodeList(node);
}

NodeList* searchById(const LinkedList* list, unsigned int concurso) {

    if (list->size == 0) return NULL;

    NodeList* pointer = list->header;

    while(pointer->element->numero != concurso && pointer != NULL){
        pointer = pointer->next;
    }
    
    return pointer->element->numero == concurso ? pointer : NULL;
}

bool isListEmpty(LinkedList* list){
    return list->size == 0;
}

int printList(const LinkedList* list) {

    NodeList* pointer = list->header;

    while (pointer != NULL && pointer->element != NULL) {
        printConcurso(pointer->element);
        printf("\n");
        pointer = pointer->next;
    }
}

void clearLinkedList(LinkedList* list) {
    
    while (!isListEmpty(list)){
        removeAtFirst(list);
    }
    free(list);
}