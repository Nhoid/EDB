#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#include "../include/structstring.h"


typedef struct NodeQueue NodeQueue;

typedef struct NodeQueue{

    string element;

    NodeQueue* next;

}NodeQueue; // Elemento da fila

typedef struct{

    NodeQueue* last; // fila

    NodeQueue* first;

    int size;
}Queue;

Queue* builderQueue(); // retorna uma nova queue

NodeQueue* buildNodeQueue(const char* string); // retorna um novo node

void eraseNodeQueue(NodeQueue* node); // Apaga um Node da memoria

void enqueue(Queue* queue ,NodeQueue* node); // adiciona o elemento no fim da queue

NodeQueue* dequeue(Queue* queue); // remove e retorna o primeiro elemento da fila

int size(const Queue* queue); // retorna o tamanho da fila

bool isQueueEmpty(const Queue* queue); // retorna se a fila está vazia ou não

NodeQueue* front(const Queue* queue); // retorna, mas não remove, o primeiro elemento

int printQueue(const Queue* queue); // printa todos elementos da fila

void deleteQueue(Queue* queue); // libera a memoria da queue por completo

#endif // QUEUE_H