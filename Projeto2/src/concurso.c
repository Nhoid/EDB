#include "../include/concurso.h"

#include <stdio.h>
#include <stdlib.h>

#include "../include/data.h"

Concurso* concursoBuilder(unsigned int numero, char data[], int bolas[]) {
    Concurso* concurso = (Concurso*) malloc(sizeof(Concurso));

    concurso->numero = numero;

    concurso->data = dataBuilder(data);

    for (int i = 0; i < 6; i++){
        concurso->bolas[i] = bolas[i];
    }
    
    return concurso;
}

void printConcurso(Concurso* concurso) {

    if (concurso == NULL) return;


    printf("Concurso: %d", concurso->numero);
    printf("\tData: ");
    printf("%s-", concurso->data.day);
    printf("%s-",  concurso->data.month);
    printf("%s",  concurso->data.year);
    printf("\tBolas: ");
    for (int i = 0; i < 6; i++) {
        printf("%d", concurso->bolas[i]);
        if (i != 5) printf("-");
    }
}