#include "../include/data.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Data dataBuilder(char data[]) {
    Data builder;

    char* token;

    token = strtok(data, "-");

    strncpy(builder.day, token, 2);
    builder.day[2] = '\0';

    token = strtok(NULL, "-");

    strncpy(builder.month, token, 2);
    builder.month[2] = '\0';

    token = strtok(NULL, "-");

    strncpy(builder.year, token, 4);
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