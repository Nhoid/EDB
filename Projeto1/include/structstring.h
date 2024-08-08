#ifndef STRUCTSTRING_H
#define STRUCTSTRING_H

#include <stddef.h>

typedef struct {
    char* text;
    unsigned long length;
}string; // Estrutura de texto

string* stringBuilder(char* text); // constroi e retorna uma string

string* stringEmpty(); // constroi uma string sem texto

void eraseString(string* string1); // apagar string da memoria

void removeFirstChars(string* string1, size_t size);

void removeSubString(string* string1, const string* subString); // procura uma substring dentro de uma string e remove ela

void concat(string* string1, const string* string2); // funcao de concatenacao personalizada

#endif // STRUCTSTRING_H