#include "helper.h"
#include <string.h>

void copy_string(char* destination,const char* source){
    strncpy(destination, source, strlen(source));
    destination[strlen(source)] = '\0';
}

int num_occurrence(const char* string, char symbol){
    int num = 0;
    for(int i=0; i<strlen(string); ++i){
        if(string[i] == symbol) ++num;
    }
    return num;
}