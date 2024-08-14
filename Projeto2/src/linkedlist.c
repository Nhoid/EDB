#include "../include/linkedlist.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../include/concurso.h"

NodeList* nodeListBuilder(Concurso* concurso){
    // aloca e inicializa um novo nodo para a lista vinculada
    NodeList* node = (NodeList*) malloc(sizeof(NodeList));

    node->element = concurso; // atribui o concurso ao nodo

    node->next = NULL; // inicializa o ponteiro para o próximo nodo como NULL

    return node;
}

LinkedList* builderList() {
    // aloca e inicializa uma nova lista vinculada
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));

    // aloca e inicializa o cabeçalho e o final da lista
    list->header = (NodeList*) malloc(sizeof(NodeList));
    list->tail = (NodeList*) malloc(sizeof(NodeList));

    list->header->element = NULL; // cabeçalho não tem elemento
    list->tail->element = NULL; // final não tem elemento

    list->tail->next = NULL; // o final da lista não aponta para nenhum próximo nodo
    list->header->next = list->tail; // o cabeçalho aponta para o final da lista

    list->size = 0; // inicializa o tamanho da lista como 0

    return list;
}

void eraseNodeList(NodeList* node) {
    // libera a memória alocada para o elemento e o próximo nodo
    free(node->element);
    free(node->next);
}


void removeNode(LinkedList* list, NodeList* node) {

    if (node == NULL || list == NULL) return; // retorna se o nodo ou a lista forem NULL

    NodeList* pointer = list->header;

    // verifica se o nodo a ser removido é o cabeçalho
    if (pointer == node) {
        removeAtFirst(list); // remove o primeiro nodo
        return;
    }

    // procura o nodo anterior ao nodo a ser removido
    while (pointer->next != node && pointer->next != NULL){
        pointer = pointer->next;
    }

    if (pointer->next == NULL) {
        // exibe mensagem se o nodo não for encontrado
        printf("Concurso nao encontrado.\n");
        return;
    }

    // ajusta o ponteiro do nodo anterior para o próximo nodo do nodo a ser removido
    if (list->tail == node) list->tail = pointer;
    else pointer->next = node->next;

    node->next = NULL; // desconecta o nodo removido da lista

    list->size--; // diminui o tamanho da lista

    eraseNodeList(node); // libera a memória do nodo removido
}

void addNodeAfter(LinkedList* list, NodeList* fromlist, NodeList* newNode) {

    if (list->size == 0){
        // se a lista estiver vazia, adiciona o nodo como o primeiro
        addNodeAtFirst(list, newNode);
        return;
    }

    newNode->next = fromlist->next; // ajusta o ponteiro do novo nodo para o próximo do nodo a partir do qual está sendo adicionado

    fromlist->next = newNode; // ajusta o ponteiro do nodo a partir do qual está sendo adicionado para o novo nodo

    list->size++; // aumenta o tamanho da lista
}

void addNodeAtFirst(LinkedList* list, NodeList* node) {

    node->next = list->header; // o próximo do novo nodo é o antigo cabeçalho

    list->header = node; // o cabeçalho da lista é o novo nodo

    list->size++; // aumenta o tamanho da lista
}


void addNodeAtLast(LinkedList* list, NodeList* node) {
    // Adiciona um nodo no final da lista chamando a função que adiciona após um nodo
    addNodeAfter(list, list->tail, node);
}

void removeAtLast(LinkedList* list) {
    // Remove o nodo do final da lista
    removeNode(list, list->tail);
}

void removeAtFirst(LinkedList* list) {
    NodeList* node = list->header; // Salva o nodo do cabeçalho

    list->header = node->next; // Atualiza o cabeçalho para o próximo nodo

    list->size--; // Decrementa o tamanho da lista

    node->next = NULL; // Desconecta o nodo removido

    eraseNodeList(node); // Libera a memória do nodo removido
}

NodeList* searchById(const LinkedList* list, unsigned int concurso) {

    if (list->size == 0) return NULL; // Retorna NULL se a lista estiver vazia

    NodeList* pointer = list->header; // Começa a busca a partir do cabeçalho

    // Procura o nodo com o número do concurso correspondente
    while(pointer->element->numero != concurso && pointer != NULL){
        pointer = pointer->next;
    }
    
    // Retorna o nodo se encontrado, senão retorna NULL
    return pointer->element->numero == concurso ? pointer : NULL;
}

bool isListEmpty(LinkedList* list){
    // Retorna verdadeiro se o tamanho da lista for 0
    return list->size == 0;
}

void printList(const LinkedList* list) {

    NodeList* pointer = list->header; // Começa a impressão a partir do cabeçalho

    // Imprime os elementos da lista
    while (pointer != NULL && pointer->element != NULL) {
        printConcurso(pointer->element); // Imprime o concurso
        printf("\n"); // Adiciona uma linha em branco
        pointer = pointer->next; // Avança para o próximo nodo
    }
}


void clearLinkedList(LinkedList* list) {
    
    // Remove todos os nodos da lista, um por um
    while (!isListEmpty(list)){
        removeAtFirst(list);
    }
    // Libera a memória alocada para a lista após todos os nodos serem removidos
    free(list);
}
