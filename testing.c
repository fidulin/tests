//include the basic libs
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define log printf("log\n");

typedef struct {
    char* string;
    int strlen;
    int allocated;
}STR_ALLOC;

void str_append(char symbol,STR_ALLOC *str){
    if(str->allocated == 0){
        str->string = malloc(sizeof(char)*8);
        if(str->string == NULL){
            exit(0);
        }
        str->allocated = 8;
    }

    if(str->allocated <= str->strlen+1){
        char* tmpstr = malloc(sizeof(char)*(2 * str->allocated));
        if(tmpstr == NULL){
            exit(0);
        }

        for(int i=0; i<str->strlen; i++){ //copying string to temporary
            tmpstr[i] = str->string[i];
        }
        free(str->string);
        str->string = tmpstr;
        str->allocated = 2*str->allocated;
    }

    str->string[str->strlen] = symbol;
    str->strlen++;
    str->string[str->strlen] = '\0';
}

char* derivation(char* str_input){
    char* str_output;
    str_output = malloc(sizeof(str_input));
    //lets derive the input
    int i=0;
    enum FSM_state_struct {start, number, variable, operator, end};
    enum FSM_state_struct FSM_state = start;

    STR_ALLOC tmp_str;
    switch(FSM_state){
        case start:
            if(str_input[i] == '\0'){
                str_output[i] = '\0';
                return str_output;
            }
            else if(str_input[i] >= '0' && str_input[i] <= '9'){
                FSM_state = number;
                str_append(str_input[i], &tmp_str);
                i++;
            }
            else if(str_input[i] == 'x'){
                FSM_state = variable;
                i++;
            }
            else if(str_input[i] == '+' || str_input[i] == '-'){
                FSM_state = operator;
                i++;
            }
            else{
                str_output[i] = '\0';
                return str_output;
            }
        case number:
            if(str_input[i] >= '0' && str_input[i] <= '9'){
                str_append(str_input[i], &tmp_str);
                i++;
            }
            else if(str_input[i] == 'x'){
                //TODO:
                FSM_state = variable;
                i++;
            }
            else if(str_input[i] == '+' || str_input[i] == '-'){
                //todo
                FSM_state = operator;
                i++;
            }
            else{
                str_output[i] = '\0';
                return str_output;
            }
    }
    //TODO: implement the derivation
        
    return str_output;
}

int main(void){
    char str_input[10] ="10x^2+5";
    char* str_output;
    str_output = derivation(str_input);
    printf("%s\n", str_output);
}
