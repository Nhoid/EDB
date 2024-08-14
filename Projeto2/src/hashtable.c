#include "../include/hashtable.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// includes personalizados
#include "../include/concurso.h"
#include "../include/linkedlist.h"
#include "../include/data.h"


HashTable* hashBuilder(int size){
    // aloca e inicializa uma nova tabela hash
    HashTable* hashTable = (HashTable*) malloc(sizeof(HashTable));

    hashTable->size = 0; // inicializa o tamanho da tabela como 0

    hashTable->capacity = size; // define a capacidade da tabela hash
    hashTable->entries = (HashEntry*) malloc(sizeof(HashEntry) * size); // aloca memoria para as entradas

    // inicializa as listas vinculadas para cada entrada da tabela hash
    for (int i = 0; i < size; i++){
        hashTable->entries[i].list = builderList();
    }

    return hashTable;
}

int hash(unsigned int key, unsigned int size){
    // calcula o indice na tabela hash usando a funcao de hash
    return key % size;
}

void addElement(HashTable* hashT, Concurso* concurso) {

    if (concurso == NULL) return; // verifica se o concurso e nulo

    // calcula o indice da tabela hash onde o concurso deve ser adicionado
    int indice = hash(concurso->numero, hashT->capacity);

    // adiciona o concurso na lista vinculada correspondente ao indice
    addNodeAtFirst(hashT->entries[indice].list, nodeListBuilder(concurso));

    hashT->size++; // incrementa o tamanho da tabela hash
}

Concurso* search(HashTable* hashT, unsigned int key) {

    if (hashT->size == 0){
        // exibe mensagem se a tabela estiver vazia
        printf("Nao tem nenhum concurso registrado.\n");
        return NULL;
    }

    // calcula o indice da tabela hash para a chave fornecida
    int indice = hash(key, hashT->capacity);

    // procura o concurso na lista vinculada correspondente
    NodeList* node = searchById(hashT->entries[indice].list, key);

    if (node == NULL) return NULL; // retorna NULL se o concurso nao for encontrado

    return node->element; // retorna o concurso encontrado
}


void removeFromHash(HashTable* hashT, unsigned int key) {

    if (hashT->size == 0) {
        // exibe mensagem se a tabela estiver vazia
        printf("Nao tem nenhum concurso cadastrado.\n");
    }

    // calcula o indice da tabela hash onde a chave está
    int indice = hash(key, hashT->capacity);

    // procura o concurso na lista vinculada correspondente
    NodeList* node = searchById(hashT->entries[indice].list, key);

    if (node == NULL) {
        // exibe mensagem se o concurso não for encontrado
        printf("Concurso nao encontrado");
        return;
    }

    // remove o nodo da lista vinculada
    removeNode(hashT->entries[indice].list, node);
}

void clearHashTable(HashTable* hash) {
    // limpa todas as listas vinculadas na tabela hash
    for (unsigned int i = 0; i < hash->capacity; i++){
        clearLinkedList(hash->entries[i].list);
    }

    // libera a memoria alocada para as entradas da tabela hash
    free(hash->entries);
}

void printHashTable(HashTable* hash) {
    // imprime o conteudo de todas as listas vinculadas na tabela hash
    for (unsigned int i = 0; i < hash->capacity; i++){
        printList(hash->entries[i].list);
    }
}
