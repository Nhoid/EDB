#include "../include/structstring.h"


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

// construtor de string
string* stringBuilder(char* text){

    if (text == NULL) return stringEmpty();

    string* algumacoisa = (string*) malloc(sizeof(string));

    algumacoisa->text = strdup(text);
    algumacoisa->length = strlen(text);

    return algumacoisa;
}

string* stringEmpty(){
    string* algumacoisa = (string*) malloc(sizeof(string));

    algumacoisa->text = NULL;
    algumacoisa->length = 0;

    return algumacoisa;
}

// deleta uma string
void eraseString(string* string1){

    // verifica se tem alguma coisa na string
    if(string1->text != NULL) {
        free(string1-> text);
        return;
    }

    // define a string como null
    string1->text = NULL;

    free(string1->text);
}


// funcao personalizada de concatenacao para concatenar e adicionar ", " entre as strings que serao os pedidos
void concat(string* string1, const string* string2){

    if (string2->text == NULL) return; // vai concatenar oq? o vento?

    if (string1->text == NULL) { // verifica se string1 contem algum conteudo
        string1->text = strdup(string2->text); // se nao tiver, ele simplesmente copia o conteudo da string2 para a string1
        string1->length = string2->length;
    } else {
        size_t newSize = string1->length + string2->length + 3; // calcula novo tamanho para incluir ", " e o caracter nulo "\0"

        char* newString = (char*) realloc(string1->text, newSize);

        if (newString) { // verifica se a memoria foi realocada de maneira correta
            strcat(newString, ", ");
            strcat(newString, string2->text);
            string1->text = newString; // troca de referência de ponteiro
            string1->length += string2->length + 2; // atualiza o comprimento para incluir ", "
        } else {
            printf("Erro ao realocar memória.\n");
        }
    }
}

void removeFirstChars(string* string1, size_t size) {
    if (size > string1->length) {
        printf("Número de caracteres a remover é maior que o comprimento da string.\n");
        return;
    }

    // Calcula o tamanho restante da string apos a remocao dos primeiros n caracteres
    size_t remainingLength = string1->length - size;
    
    // Move o bloco de memoria para "remover" os primeiros n caracteres
    memmove(string1->text, string1->text + size, remainingLength);

    // Atualiza o comprimento da string original
    string1->length -= size;

    // Adiciona um caractere nulo ao final da nova string para garantir terminacao correta
    string1->text[string1->length] = '\0';
}


void removeSubString(string* string1, const string* subString) {

    char* pointer = strstr(string1->text, subString->text);

    bool fim = false;

    if (pointer == NULL) {
        printf("Prato nao encontrado.\n");
        return;
    }

    if (pointer == string1) {
        removeFirstChars(string1, subString->length);
        return;
    }

    if ( (pointer + subString->length) != (string1->text + string1->length) ) {
        string* divisor = stringBuilder("");
        concat(subString, divisor);
    } else {
        pointer -= 2;
    }

    // Calcula o tamanho restante da string apos a remocao do subString
    size_t remainingLength = string1->length - (pointer - string1->text + subString->length);
    
    // pointer = destino para o bloco de memoria
    // pointer + subString->length = de onde o bloco de memoria ira Sair
    // tamanho do bloco de memoria
    memmove(pointer, pointer + subString->length, remainingLength);

    // Atualiza o comprimento da string original
    string1->length -= subString->length;

    // Adiciona um caractere nulo ao final da nova string para garantir terminacao correta
    string1->text[string1->length] = '\0';
}