#ifndef DATA_H
#define DATA_H

#include <stdbool.h>

typedef struct {
    char day[3];
    char month[3];
    char year[5];
} Data;

Data dataBuilder(char data[]);

bool sameData(Data data1, Data data2); // compara se eh a msm data
bool sameDay(Data data1, Data data2); // compara se eh o mesmo dia
bool sameMonth(Data data1, Data data2); // comapra se eh o mesmo mes
bool sameYear(Data data1, Data data2); // compara se eh o mesmo ano

#endif // DATA_H