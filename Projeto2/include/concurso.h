#ifndef CONCURSO_H
#define CONCURSO_H

#include "data.h"

typedef struct {

    unsigned int numero;
    Data data;
    int bolas[6];

} Concurso;

Concurso* concursoBuilder(unsigned int numero, char data[], int bolas[]); // retorna um ponteiro de concurso

void printConcurso(Concurso* concurso); // printa um concurso, formatdo e nao quebra linha

#endif // CONCURSO_H