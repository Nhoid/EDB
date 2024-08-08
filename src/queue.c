#include "../include/queue.h"

#include "../include/structstring.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

NodeQueue* buildNodeQueue(const char* string){
    //COMEÇA ALOCANDO NOVA MEMORIA
    NodeQueue* node = (NodeQueue*) malloc(sizeof(NodeQueue));

    //COPIA OS DADOS DA STRING PASSADA
    node->element.text = strdup(string);
    node->element.length = strlen(string);

    //DEFINE OS SEGUINTES E OS ANTERIORES COMO NULL
    node->next = NULL;

    //RETORNA O NODE CRIADO
    return node;
}


//APAGA UM NODE
void eraseNodeQueue(NodeQueue* node){
    //COMEÇA APAGANDO SUAS REFERENCIAS DE PROXIMO E ANTERIOR
    node->next = NULL;

    //APAGA A STRING
    eraseString(&node->element);

    //APAGA O NODE
    free(node);
}

//Retorna uma Fila
Queue* builderQueue(){
    //Aloca espaço inicial
    Queue* queue = (Queue*) malloc(sizeof(Queue));

    queue->first = NULL;
    queue->last = NULL;

    //Define o tamanho como 0
    queue->size = 0;

    return queue;
}

//retorna o tamanho da fila
int size(const Queue* queue){
    return queue->size;
}

//Verifica se tem algum elemento na fila
bool isQueueEmpty(const Queue* queue){
    return size(queue) == 0;
}

//Adiciona elemento na fila
void enqueue(Queue* queue, NodeQueue* node){
    //Verifica se tem algum elemento
    if(isQueueEmpty(queue)){
        //Se não tiver ele atribui o primeiro e ultimo
        queue->first = queue->last = node;
    }else{
        //se tiver, ele o elemento para o fim de fila
        queue->last->next = node;
        queue->last = node;
    }
    //aumenta o tamanho da fila
    queue->size++;
}

//Retorna, mas não apaga, o primeiro elemento 
NodeQueue* front(const Queue* queue){
    return queue->first;;
}

//Remove e retorna o primeiro elemento
NodeQueue* dequeue(Queue* queue){

    if(isQueueEmpty(queue)) return NULL;

    //Pega referencia do primeiro
    NodeQueue* node = queue->first;
   
    //Pega a referencia do segundo
    queue->first = queue->first->next;

    node->next = NULL;

    //diminui o tamanho da fila
    queue->size--;

    return node;
}

//Apaga uma queue da memoria
void deleteQueue(Queue* queue){
    //Delete todos os elementos, caso tenha
    while(!isQueueEmpty(queue)){
        eraseNodeQueue( dequeue(queue) );
    }

    free(queue);
}

// funcao que printa uma fila
int printQueue(const Queue* queue) {

    if(isQueueEmpty(queue)) return 0; // verifica se tem elementos

    NodeQueue* pointer = front(queue); // ponteiro para percorrer a fila

    int indice = 1;

    while (pointer != NULL){ // itera sobre a lista
        printf("%d - %s\n", indice, pointer->element.text);
        indice++;
        pointer = pointer->next;
    }

    return indice;
}