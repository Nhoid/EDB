#ifndef FUNCIONALIDADES_H
#define FUNCIONALIDADES_H

#include "hashtable.h"
#include "concurso.h"
#include "linkedlist.h"
#include "data.h"

void exibirMenu();

void inserirConcurso(HashTable* hash);

void buscarConcurso(HashTable* hash);

void removerConcurso(HashTable* hash);

void printConcursos(HashTable* hash);

int contarlinhas(char* fileName);

Concurso* processarString(char* string, char delimitador);

void lerArquivo(HashTable* hash, char* filename);

HashTable* carregarArquivo();

#endif // FUNCIONALIDADES_H