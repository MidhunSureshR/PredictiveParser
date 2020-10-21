#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char* production;
}production_body;

typedef struct{
    ssize_t size;
    production_body* body;
}production_body_list;

typedef struct{
    char left;
    production_body_list *right;
}production;

void copy_string(char* destination,const char* source, ssize_t len){
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

void print_production(production *p){
    printf("%c->", p->left);
    int i;
    for(i=0; i<p->right->size - 1; ++i){
        printf("%s|",p->right->body[i].production);
    }
    printf("%s",p->right->body[i].production);
}

production_body_list* parse_production_body_from_string(const char* start_of_production_body){
    char backup[100];
    copy_string(backup, start_of_production_body, strlen(start_of_production_body));

    production_body_list* p = malloc((sizeof(production_body_list)));
    p->size = num_occurrence(start_of_production_body, '|') + 1;
    p->body = malloc(sizeof(production_body) * p->size);

    for(int i=0; i<p->size; ++i) {
        p->body[i].production = malloc(sizeof(char) * 10);
    }

    char* token;

    token = strtok(backup, "|");
    copy_string(p->body[0].production, token, strlen(token));
    for(int i=1; token && i<p->size; ++i){
        token = strtok(NULL, "|");
        copy_string(p->body[i].production, token, strlen(token));
    }
    return p;
}

production* parse_production_from_string(const char* string){
    // Assume our production has the string form A->bB|cC|d;
    production* p = malloc(sizeof(production));

    // Lets first find our left side non-terminal ( A in our example)
    p -> left = string[0];


    production_body_list* b = parse_production_body_from_string(string+3);
    p -> right = b;
    printf("Parsed: ");
    print_production(p);
  return p;
};

char** get_grammar_from_user(int num_productions){
    char** grammar = malloc(sizeof(int *) * num_productions);
    for(int i=0; i < num_productions; ++i){
        grammar[i] = malloc(sizeof(char) * 100);
        scanf("%s", grammar[i]);
    }
    return grammar;
};

int get_productions_count(){
    int num_productions;
    scanf("%d", &num_productions);
    return num_productions;
}

int main() {
    printf("Predictive Parser\n");
/*    printf("Enter number of productions:");
    const int num_productions = get_productions_count();
    char **grammar = get_grammar_from_user(num_productions);*/
    parse_production_from_string("A->Bb|cD|eF");
    return 0;
}
