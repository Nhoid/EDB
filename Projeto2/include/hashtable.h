#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "concurso.h"
#include "linkedlist.h"

typedef struct {

    LinkedList* list;

} HashEntry;

typedef struct HashTable {

    HashEntry *entries;

    unsigned int size;

    unsigned int capacity;

} HashTable;

HashTable* hashBuilder(int size); // cria uma tabela hash

int hash(unsigned int key, unsigned int size); // funcao hash

void addElement(HashTable* hashT, Concurso* concurso); // adiciona um concurso na tabela hash

Concurso* search(HashTable* hashT, unsigned int key); // procura um concurso com base na chave

void removeFromHash(HashTable* hashT, unsigned int key); // remove um concurso com base na chave

void clearHashTable(HashTable* hash); // limpa memoria de uma hashTable

void printHashTable(HashTable* hash); // printa todos elementos da hashTable

#endif // HASHTABLE_H