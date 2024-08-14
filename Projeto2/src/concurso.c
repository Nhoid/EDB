#include "../include/concurso.h"

#include <stdio.h>
#include <stdlib.h>

#include "../include/data.h"

Concurso* concursoBuilder(unsigned int numero, char data[], int bolas[]) {
    // aloca memoria para um novo objeto Concurso
    Concurso* concurso = (Concurso*) malloc(sizeof(Concurso));

    // define o numero do concurso
    concurso->numero = numero;

    // inicializa a data do concurso usando a funcao dataBuilder
    concurso->data = dataBuilder(data);

    // copia os valores das bolas sorteadas para o concurso
    for (int i = 0; i < 6; i++){
        concurso->bolas[i] = bolas[i];
    }
    
    // retorna o ponteiro para o concurso criado
    return concurso;
}

void printConcurso(Concurso* concurso) {
    // verifica se o ponteiro concurso e nulo, se for, sai da funcao
    if (concurso == NULL) return;

    // imprime o numero do concurso
    printf("Concurso: %d", concurso->numero);
    
    // imprime a data do concurso no formato dia-mes-ano
    printf("\tData: ");
    printf("%s-", concurso->data.day);
    printf("%s-",  concurso->data.month);
    printf("%s",  concurso->data.year);
    
    // imprime as bolas sorteadas no concurso
    printf("\tBolas: ");
    for (int i = 0; i < 6; i++) {
        printf("%d", concurso->bolas[i]);
        // imprime um traço entre as bolas, exceto apos a ultima
        if (i != 5) printf("-");
    }
}