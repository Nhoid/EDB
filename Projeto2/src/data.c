#include "../include/data.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Data dataBuilder(char* data) {
    Data builder;

    // Usamos sscanf para extrair o dia, mês e ano da string `data`
    sscanf(data, "%2[^-]-%2[^-]-%4s", builder.day, builder.month, builder.year);

    // Assegura que o buffers terminam com '\0'
    builder.day[2] = '\0';
    builder.month[2] = '\0';
    builder.year[4] = '\0';
    
    return builder;
}


bool sameDay(Data data1, Data data2){
    return strcmp(data1.day, data2.day) == 0;
}
bool sameMonth(Data data1, Data data2) {
    return strcmp(data1.month, data2.month) == 0;
}
bool sameYear(Data data1, Data data2) {
    return strcmp(data1.year, data2.year) == 0;
}

bool sameData(Data data1, Data data2) {
    return sameDay(data1, data2) && sameMonth(data1, data2) && sameYear(data1, data2);
}