/*  P1G94 854723 873888    */
#include "coda.h"

int isempty(pcoda pc){
    return (pc->head == NULL);
}
pcoda getempty(){
    pcoda ret;

    ret = (pcoda) malloc(sizeof(coda));
    if (ret != NULL)
    {
        ret->head = NULL;
        ret->tail = NULL;
        ret->tipo = not_def;
    }
    return ret;    
}

int append(pcoda pc, char *s,int riga){
    int incremento = 1;
    int err = 0;
    pword w = (pword) malloc(sizeof(word));  
    if (w == NULL)
    {
        err = MALLOC_FAILURE_CODA;
    }
    else
    {
        w->row = riga;
        w->next=NULL;
        w->word = (char *)malloc(strlen(s)+1);
        if (w->word == NULL)
        {
            err = MALLOC_FAILURE_CODA;
        }
        else
        {
            strcpy(w->word,s);
            if ( w->word[strlen(s)-1] == ':'){
                incremento = 0;
            }
            if (pc->tail == NULL)
            {
                pc->head = w;
                pc->tail = w;
                pc->lengt = incremento;
            }
            else
            {
                pc->tail->next = w;
                pc->tail = w;
                pc->lengt += incremento;
            }
        }
    }
    return err;
}


char *extract(pcoda pc,int *riga){
    char *s = "";
    if(!isempty(pc))
    {
        pword temp;
        temp = pc->head;
        s = temp->word;
        *riga = temp->row;
        pc->head = pc->head->next;
        free(temp);
    }
    return s;
}

int ispresent(pcoda pc, char *s)
{
    int res = 0;
    int exit= 0;
    pword temp = pc ->head;
    while (!exit && temp)
    {
        if (!strcmp(s,temp->word)){
            exit=1;
        }
           
        res = res + 1 ;
        temp = temp->next;
    }    
    return (exit)? res: -1;

}

int get_row(pcoda pc,char *s)
{
    int res = -1;
    int exit= 0;
    pword temp = pc ->head;
    while (!exit && temp)
    {
        if (!strcmp(s,temp->word)){
            res = temp->row;
            exit=1;
        }
        temp = temp->next;
    }
    return res;
}


void clear(pcoda *pc){
    pword temp = (*pc)->head;
    pword tmp_next;
    while (temp)
    {
        tmp_next = temp->next;
        free(temp->word);
        free(temp);
        temp = tmp_next;
    }
    free(*pc);
    *pc = NULL;
}

int movetotop(pcoda pc,char *s1,char *s2)
{
    int err = 0;
    pword prima = NULL;
    pword main_cell;
    if (pc->head)
    {
        main_cell = (pc->head);
        while (main_cell != NULL && strcmp(main_cell->word,s1) && strcmp(main_cell->word,s2)  )
        {
            prima = main_cell;
            main_cell = main_cell ->next;
        }
        if (main_cell == NULL)
        {
            return MAIN_NOT_FOUND;
        }
        else if (prima != NULL)
        {
            /*
                Il main non è all inzio
                quindi devo scorrere la coda per trovare la cella che punta al main e la cella che punta alla funzione dopo
            */
            pword temp = main_cell->next;
            pword thead;
            while ( temp != NULL && temp->word[strlen(temp->word)-1] != ':'  )
            {
                main_cell = temp;
                temp = temp -> next;
            }
            if (temp == NULL)
            {
                pc -> tail = prima;
            }
            thead = pc->head;
            pc->head = prima->next;
            prima ->next = main_cell ->next;
            main_cell -> next = thead;            
        }
    }
    
    return err;
}

void stampa(pcoda pc){
    pword temp = pc->head;
    while (temp)
    {
        printf("%s\n",temp->word);
        temp = temp->next;
    }
}
