#include "../include/data.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Data dataBuilder(char data[]) {
    Data builder;

    char* token;

    

    token = strtok(data, "-");

    for (int i = 0; i < 2; i++) {
        builder.day[i] = token[i];
    }
    builder.day[3] = '\0';
    token = strtok(NULL, "-");

    

    for (int i = 0; i < 2; i++) {
        builder.month[i] = token[i];
    }
    builder.month[3] = '\0';
    token = strtok(NULL, "-");

    for (int i = 0; i < 4; i++) {
        builder.year[i] = token[i];
    }
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