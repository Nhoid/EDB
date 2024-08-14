#ifndef FUNCIONALIDADES_H
#define FUNCIONALIDADES_H

#include <stdbool.h>

#include "hashtable.h"
#include "concurso.h"
#include "linkedlist.h"
#include "data.h"

typedef struct {
    int bola;
    int repeticao;
} Estatisticas;

void exibirMenu(); // menu de escolhas

Estatisticas* getBolas(); // gera estatisticas

void inserirConcurso(HashTable* hash, Estatisticas* estatisticas); // adicionar novos concursos

void contarBolas(int bolas[], Estatisticas* estatisticas); // salva estatisticas

void diminuirEstatisticas(int bolas[], Estatisticas* estatisticas); // diminui estatisticas, em caso de remocao de concurso

void buscarConcurso(HashTable* hash); // busca um concurso

void removerConcurso(HashTable* hash, Estatisticas* estatisticas); // exclui um concurso

void printConcursos(HashTable* hash); // mostra todos os concursos

int contarlinhas(char* fileName); // conta linhas de um arquivo

Concurso* processarString(char* string, bool csv); // processa linha de arquivo

void lerArquivo(HashTable* hash, char* filename, Estatisticas* estatisticas); // le um arquivo

HashTable* iniciarArquivo(char* filename, Estatisticas* estatisticas); // carrega um arquivo no inicio do programa

HashTable* carregarArquivo(Estatisticas* estatisticas); // carrega um arquivo passado

void limparEstatisticas(Estatisticas* estatisticas); // apaga todas as estatisticas

void apresentarEstatisticas(HashTable* hash, Estatisticas* original); // mostra todas as estatisticas

void insertionSort(Estatisticas* arr); // insectionSort

#endif // FUNCIONALIDADES_H