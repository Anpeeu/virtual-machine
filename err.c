/*  P1G94 854723 873888    */
#include "err.h"

void print_err(int err,int row,char *word){
    char *s;
    switch (err)
    {
    case STACK_FULL:
        s = "STACK_FULL";
        break;
    case STACK_EMPTY:
        s = "STACK_EMPTY";
        break;
    case JUMP_NOT_VALID:
        s = "JUMP_NOT_VALID";
        break;    
    case OVERFLOW_DETECTED:
        s = "OVERFLOW_DETECTED";
        break;    
    case DIV_ZERO:
        s = "DIV_ZERO";
        break;    
    case REGISTRER_UNKNOWN:
        s = "REGISTRER_UNKNOWN";  
        break;
    case INSTRUCTION_NOT_RECOGNIZED:
        s = "INSTRUCTION_NOT_RECOGNIZED";
        break;    
    case UNKOWN_WORD:
        s = "UNKOWN_WORD";
        break;  
    case ARR_SIZE_INCORRECT:
        s = "ARR_SIZE_INCORRECT";
        break;  
    case CANT_OPEN_FILE:
        s = "CANT_OPEN_FILE";
        break;  
    case EMPTY_FILE:
        s = "EMPTY_FILE";
        break;
    case MAIN_NOT_FOUND:
        s = "MAIN_NOT_FOUND";
        break;
    case UNKNOWN_FORMAT:
        s = "UNKNOWN_FORMAT";
        break;
    case UNKOWN_PARAMETER:
        s = "UNKOWN_PARAMETER";
        break;
    case WRONG_NUMBER_PARAMETER:
        s = "WRONG_NUMBER_PARAMETER";
        break;
    case CANNOT_SAVE_CVM:
        s = "CANNOT_SAVE_CVM";
        break;
    case MALLOC_FAILURE:
        s = "MALLOC_FAILURE";
        break;
    default:
        s = "ERRORE SCONOSCIUTO";
        printf("Codice %d",err);
        break;
    }
    printf(" Errore codice %d - %s \n",err,s);
    if (row>=0 && word != NULL)
    {
        printf(" Trovato in riga %d - %s\n",row,word);
    }
}
