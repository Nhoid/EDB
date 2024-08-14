#include "../include/data.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Data dataBuilder(char* data) {
    Data builder;

    // sscanf para extrair o dia, mes e ano
    sscanf(data, "%2[^-]-%2[^-]-%4s", builder.day, builder.month, builder.year);

    // Assegura que o buffers terminam com '\0'
    builder.day[2] = '\0';
    builder.month[2] = '\0';
    builder.year[4] = '\0';
    
    return builder;
}


bool sameDay(Data data1, Data data2){
    // compara se os dias de duas datas sao iguais
    return strcmp(data1.day, data2.day) == 0;
}

bool sameMonth(Data data1, Data data2) {
    // compara se os meses de duas datas sao iguais
    return strcmp(data1.month, data2.month) == 0;
}

bool sameYear(Data data1, Data data2) {
    // compara se os anos de duas datas sao iguais
    return strcmp(data1.year, data2.year) == 0;
}

bool sameData(Data data1, Data data2) {
    // verifica se as datas sao iguais comparando dia, mes e ano
    return sameDay(data1, data2) && sameMonth(data1, data2) && sameYear(data1, data2);
}