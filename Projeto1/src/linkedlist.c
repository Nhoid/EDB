#include "../include/linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

#include "../include/structstring.h"
#include <string.h>


// CONSTROI UM NODE
NodeList* buildNodeList(char* string){
    // COMEÇA ALOCANDO NOVA MEMORIA
    NodeList* node = (NodeList*) malloc(sizeof(NodeList));

    if (!node) {
        printf("Erro ao alocar memoria para Node\n");
        return NULL;
    }

    // COPIA OS DADOS DA STRING PASSADA
    node->element.text = strdup(string);
    node->element.length = strlen(string);

    //DEFINE OS SEGUINTES E OS ANTERIORES COMO NULL
    node->next = NULL;
    node->prev = NULL;

    //RETORNA O NODE CRIADO
    return node;
}

// APAGA UM NODE
void eraseNodeList(NodeList* node){

    // COMEÇA APAGANDO SUAS REFERENCIAS DE PROXIMO E ANTERIOR
    node->next = NULL;
    node->prev = NULL;

    // APAGA A STRING
    eraseString(&node->element);

    // APAGA O NODE
    free(node);
}

bool validNode(LinkedList* linkedList, NodeList* node){
    return node == linkedList->tail || node == linkedList->header || node == NULL;
}

bool isListEmpty(const LinkedList* linkedList) {
    return linkedList->size == 0;
}

// CONSTRUTOR DE LINKEDLIST

LinkedList* builderList(){

    // COMEÇA ALOCANDO O ESPAÇO DE UMA LINKEDLIST
    LinkedList* linkedList =(LinkedList*) malloc(sizeof(LinkedList));

    // CONSTROI HEADER(SENTINELA)
    linkedList->header = buildNodeList("__HEADER__");
    // CONSTROI A TAIL(SENTINELA)
    linkedList->tail = buildNodeList("__TAIL__");


    // DEFINE O ANTERIOR AO TAIL COMO SENDO O HEADER, JA QUE ESTÁ VAZIA
    linkedList->tail->prev = linkedList->header;
    // DEFINE O ANTERIOR AO HEADER COMO SENDO A TAIL, JA QUE ESTÁ VAZIA
    linkedList->header->next = linkedList->tail;

    // DEFINE O TAMANHO COMO 0
    linkedList->size = 0;

    if (!(linkedList && linkedList->header && linkedList->tail)) {
        printf("Erro ao alocar memoria para lista\n");
        return NULL;
    }
    //RETORNA A LINKEDLIST
    return linkedList;
}

void addNodeAfter(LinkedList* linkedList, NodeList* fromlist, NodeList* newNode){

    //DEBUG
//    printf("fromList == linkedList->tail: %s\n", fromList == linkedList->tail ? "true" : "false");
//    printf("newNode == linkedList->tail: %s\n", newNode == linkedList->tail ? "true" : "false");
//    printf("newNode == linkedList->header: %s\n", newNode == linkedList->header ? "true" : "false");

    // VERIFICAÇÕES PARA EVITAR ERRO
    // VERIFICA SE TAO QUERENDO ADICIONAR DPS DO TAIL, NAO PODE
    // VERIFICA SE EH UM NODE VALIDO CHAMADNO A FUNCAO
    if( fromlist == linkedList->tail || validNode(linkedList, newNode)) {
        printf("Node para ser adiciona eh invalido\n");
        return;
    }


    // PEGA O SEGUINTE DA LISTA
    NodeList* nodeNext = fromlist->next;

    // DEFINE O PROXIMO DO NOVO NODE COMO SENDO O SEGUINTE DO NODE ANTERIOR
    newNode->next = nodeNext;
    // DEFINE O ANTERIOR COMO SENDO O NODE PASSADO
    newNode->prev = fromlist;

    // FAZ OS NODES DA LISTA APONTAR PARA O NOVO NODE
    fromlist->next = newNode;
    nodeNext->prev = newNode;

    // AUMENTA O TAMANHO DA LISTA
    linkedList->size++;
}

// REMOVER UM ELEMENTO SEM APAGAR ELE DA MEMORIA
void removeNodeWithOutDelete(LinkedList* linkedList, NodeList* node){

    // VERIFICAÇÕES PARA EVITAR ERRO
    if( validNode(linkedList, node) || isListEmpty(linkedList) ) {
        printf("Node Invalido ou a lista esta vazia \n");
        return;
    };

    // PEGA O NODE SEGUINTE E ANTERIOR DO QUE ESTÁ PARA SER REMOVIDO
    NodeList* prev = node->prev;
    NodeList* next = node->next;

    // FAZ OS NODES SEGUINTE E ANTERIOR APONTAREM UM PARA O OUTRO
    prev->next = next;
    next->prev = prev;

    node->prev = NULL;
    node->next = NULL;

    // DIMINUI O TAMANHO DA LISTA
    linkedList->size--;
}

// REMOVE UM NODE
void removeNode(LinkedList* linkedList, NodeList* node){

    // FAZ CHAMADA DE OUTRA FUNCAO
    removeNodeWithOutDelete(linkedList, node);

    // APAGA O NODE
    eraseNodeList(node);
}

// ADICIONA UM NODE NA PRIMEIRA POSIÇÃO DA LISTA USANDO O HEADER COMO REFERÊNCIA
void addNodeAtFirst(LinkedList* linkedlist, NodeList* node){
    addNodeAfter(linkedlist, linkedlist->header, node);
}

// ADICIONA O ELEMENTO NA ULTIMA POSIÇÃO DA LISTA USANDO O ANTERIOR A TAIL COMO REFERÊNCIA
void addNodeAtLast(LinkedList* linkedlist,NodeList* node){
    addNodeAfter(linkedlist, linkedlist->tail->prev, node);
}

// REMOVE UM NODE NA PRIMEIRA POSIÇÃO DA LISTA USANDO O HEADER COMO REFERÊNCIA
void removeAtFirst(LinkedList* linkedList){
    removeNode(linkedList, getFirst(linkedList));
}

// REMOVE O ELEMENTO NA ULTIMA POSIÇÃO DA LISTA USANDO O ANTERIOR A TAIL COMO REFERÊNCIA
void removeAtLast(LinkedList* linkedList){
    removeNode(linkedList, getLast(linkedList));
}

// PROCURA UM ELEMENTO COM BASE NO TEXTO FORNECIDO
NodeList* searchByData(const LinkedList* linkedlist, const char* string){
    // COMEÇA DO PRIMEIRO ELEMENTO
    NodeList* pointer = linkedlist->header->next;
    // ENQUANTO O TEXTO DO ELEMENTO NÃO FOR IGUAL AO PASSADO E AINDA HOUVER ELEMENTOS VALIDOS NA LISTA
    while(strcmp(pointer->element.text, string) != 0 && pointer != linkedlist->tail){

        if (strstr(pointer->element.text, string) != NULL) {
            return pointer;
        }

        // PULA PARA O PROXIMO ELEMENTO
        pointer = pointer->next;

    }

    // SE O ELEMENTO FOR IGUAL AO TEXTO PASSADO PARA PESQUISA ELE RETORNA, SE NÃO ELE RETORNA NULL
    return strcmp(pointer->element.text, string) == 0 ? pointer : NULL;
}

// PROCURA POR INDICE
NodeList* searchByIndex(const LinkedList* linkedlist, int index){

    // VERIFICA SE O INDEX É VALIDO
    if (index < 0 || index >= linkedlist->size) {
        printf("Index de pesquisa invalido\n");
        return NULL;
    }

    // FAZ UMA VERIFICAÇÃO RAPIDA PARA VER SE O INDEX PROCURADO NÃO SE REFERE DIRETAMENTE AO PRIMEIRO OU AO ULTIMO
    if (index == 0) return getFirst(linkedlist);
    else if (index == linkedlist->size - 1) return getLast(linkedlist);

    NodeList* pointer = getFirst(linkedlist);

    while (index > 0){
        pointer = pointer->next;
        index--;
    }


    return pointer;
}

// PEGA O PRIMEIRO ELEMENTO, CASO A LISTA ESTEJA VAZIA ELE RETORNA O HEADER
NodeList* getFirst(const LinkedList* linkedList){
    return linkedList->size == 0 ? NULL : linkedList->header->next;
}

// PEGA O ULTIMO ELEMENTO, CASO A LISTA ESTEJA VAZIA ELE RETORNA A TAIL
NodeList* getLast(const LinkedList* linkedList){
    return linkedList->size == 0 ? NULL : linkedList->tail->prev;
}

// LIMPA UMA LISTA DA MEMORIA
void clearLinkedList(LinkedList* linkedList){
    while(linkedList->size > 0) removeAtLast(linkedList); // VAI REMOVENDO NODE POR NODE
    eraseNodeList(linkedList->header); // REMOVE O HEADER
    eraseNodeList(linkedList->tail); // REMOVE A TAIL
    free(linkedList); // REMOVE A LISTA
}

// printa uma lista inteira
int printList(const LinkedList* linkedlist) {

    if (isListEmpty(linkedlist)) return 0; // verifica se tem elementos a serem printados

    NodeList* pointer = getFirst(linkedlist); // ponteiro para percorrer a lista

    int indice = 1;

    while ( pointer != linkedlist->tail ) { // itera sobre todos elementos da lista
        printf("%d - %s\n", indice ,pointer->element.text);
        indice++;
        pointer = pointer->next;
    }

    return indice;
}