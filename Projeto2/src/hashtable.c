#include "../include/hashtable.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// includes personalizados
#include "../include/concurso.h"
#include "../include/linkedlist.h"
#include "../include/data.h"


HashTable* hashBuilder(int size){
    HashTable* hashTable = (HashTable*) malloc(sizeof(HashTable));

    hashTable->size=0;

    hashTable->capacity = size;
    hashTable->entries = (HashEntry*) malloc(sizeof(HashEntry) * size);

    for (int i = 0; i < size; i++){
        hashTable->entries[i].list = builderList();
    }

    return hashTable;
}

int hash(unsigned int key, unsigned int size){
    return key % size;
}

void addElement(HashTable* hashT, Concurso* concurso) {
    int indice = hash(concurso->numero, hashT->capacity);

    addNodeAtFirst(hashT->entries[indice].list, nodeListBuilder(concurso));

    hashT->size++;
}

Concurso* search(HashTable* hashT, unsigned int key) {

    if (hashT->size == 0){
        printf("Nao tem nenhum concurso registrado.\n");
        return NULL;
    }

    int indice = hash(key, hashT->capacity);

    NodeList* node = searchById(hashT->entries[indice].list, key);

    if (node == NULL) return NULL;

    return node->element;
}

void removeFromHash(HashTable* hashT, unsigned int key) {

    if (hashT->size == 0) {
        printf("Nao tem nenhum concurso cadastrado.\n");
    }

    int indice = hash(key, hashT->capacity);

    NodeList* node = searchById(hashT->entries[indice].list, key);

    if (node == NULL) {
        printf("Concurso nao encontrado");
        return;
    }

    removeNode(hashT->entries[indice].list, node);
}

void clearHashTable(HashTable* hash) {
    for (int i = 0; i < hash->capacity; i++){
        clearLinkedList(hash->entries[i].list);
    }

    free(hash->entries);
}

void printHashTable(HashTable* hash) {
    for (int i = 0; i < hash->capacity; i++){
        printList(hash->entries[i].list);
    }
}