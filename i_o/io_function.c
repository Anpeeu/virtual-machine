/*  P1G94 854723 873888    */
#include "io_function.h"

/*
    Definizione delle istruzioni traducibili (forma1,;forma2;forma_numerica)
*/
#define NUM_ISTRUCTION 16
#define NUM_TEXTS 3

const char *istr[NUM_ISTRUCTION][NUM_TEXTS]= { 
    {"HALT" , "halt" , "0"},
    {"DISPLAY" ,"display" ,"1"},
    {"PRINT_STACK" ,"print_stack" ,"2"},
    {"PUSH" ,"push" ,"10"},
    {"POP" ,"pop" ,"11"},
    {"MOV" ,"mov" ,"12"},
    {"CALL" ,"call" ,"20"},
    {"RET" ,"ret" ,"21"},
    {"JMP" ,"jmp" ,"22"},
    {"JZ" ,"jz" ,"23"},
    {"JPOS" ,"jpos" ,"24"},
    {"JNEG" ,"jneg" ,"25"},
    {"ADD" ,"add" ,"30"},
    {"SUB" ,"sub" ,"31"},
    {"MUL" ,"mul" ,"32"},
    {"DIV" ,"div" ,"33"}
};
/*
    Funzioni di supporto 
*/

void arraycleaner(char *arr,int dim){
    int i;
    for(i=0;i<dim;i++)
        arr[i]='\0';
}


/*controllo se ho solo numeri*/
int just_num(char *s){
    if (((*s) >= '0' && (*s)<= '9')||  (*s) == '-')
    {
        s++;
        while ( (*s) >= '0' && (*s)<= '9' ){
            s++;
        }
    }
    return !(*s);
}

/*rimuove da una parola il ;*/
void remove_semicolon(char *s){
    int j = 0;
    while (s[j] != '\0')
    {
        if ((s)[j] == ';')
        {
            (s)[j] = '\0';
        }
        j++;
    }
}
/*sostituisco l'istruzione con il suo corrispettivo codice macchina*/
void test(char **res,char **s,const char ** array,int *cambiato,int *err)
{
    if (!(*cambiato) && (!strcmp((*s),array[0]) || !strcmp((*s),array[1])))
    {
        *res = (char *)malloc(strlen(array[2])+1);
        if (res != NULL)
        {
            strcpy(*res,array[2]);
            free(*s);
            *s = *res;
            *cambiato = 1;
        }
        else
        {
            *err = MALLOC_FAILURE_ASSEMBLY_TO_MAC;
        }
        
    }
}

/*funzione di supporto che miserve a sostituire la stringa con la sua traduzione in codice macchina*/
void sostituisci(char **s,int *err)
{
    char *res;
    int cambiato = 0;
    int i;
    for ( i = 0; i < NUM_ISTRUCTION; i++)
    {
        test(&res,s,istr[i],&cambiato,err);
    }
    if (cambiato == 0)
    {
        if ((*s)[strlen(*s)-1] == ',')
        {
            (*s)[strlen(*s)-1] = '\0';
        }
        if ((*s)[strlen(*s)-1] == ',')
        {
            (*s)[strlen(*s)-1] = '\0';
        }
        if ((((*s)[0] == 'r' || (*s)[0] == 'R') ) && just_num((*s+1)))
        {
            res = (char *)malloc(strlen(*s));
            if (res != NULL)
            {   
                strcpy(res,(*s+1));
                free(*s);
                *s = res;
                cambiato = 1;
            }
            else
            {
                *err = MALLOC_FAILURE_ASSEMBLY_TO_MAC;
            }
        }
        remove_semicolon(*s);
    }
}


/*---------------------------------------------------------------------------------------*/
/*
    Funzioni principali
*/



pcoda readfile(const char *filename,int *err){
    /*struttura da ritornare*/
    pcoda result;
    FILE *input;
    /*buffer della getline*/
    char *buffer;
    size_t buffsize = 1;
    int stringread;
    /*variabili utili*/
    int i;
    char *prova;
    int comment;

    
    input = fopen(filename,"r");
    if(!input)
    {
        *err = CANT_OPEN_FILE;
        print_err(CANT_OPEN_FILE,-1,NULL);
    }
    else 
    {
        int riga = 1;
        result = getempty();
        buffer=(char*)malloc(sizeof(char)*buffsize);
        if (result == NULL || buffer == NULL)
        {
            *err = MALLOC_FAILURE_READ_FILE;
        }
        else
        {
            while((stringread=getline(&buffer,&buffsize,input))!=EOF){
                comment = 0;
                i = 0;
                prova = (char*) malloc(stringread+1);
                if (prova == NULL)
                {
                    *err = MALLOC_FAILURE_READ_FILE;
                }
                else
                {
                    while(i<stringread && !comment){
                        remove_semicolon(buffer);    
                        for (;*(buffer+i)==' ' || *(buffer+i) == '\n' || *(buffer+i) == '\t' || *(buffer+i) == '\r' ; i++){}
                        if(*(buffer+i)==';' || *(buffer+i)=='\0')
                        {
                            comment = 1;
                        }
                        else
                        {
                            sscanf((buffer+i),"%s",prova);
                            append(result,prova,riga);
                            i+=strlen(prova);
                        }
                        arraycleaner(prova,stringread);
                    }
                    free(prova);
                }
                riga++;
            }
        }
        if (isempty(result))
        {
            *err = EMPTY_FILE;
            print_err(EMPTY_FILE,-1,NULL);
            clear(&result);
        }
        else if ( result->head->word[0] >= '0' && result->head->word[0] <= '9')
        {
           result->tipo = machinecode;
        }
        else
        {
            result->tipo = assembly;
        }
        fclose(input);
        free(buffer);

        return result;
    }
    return NULL;
}


pcoda assembly_to_machinecode(pcoda pc,int op,int *err){
    pcoda result;
    /*controllo se la coda è fatta di codice assembly*/
    if ( pc->tipo == assembly)
    {
        /*futuro aggiornamento, copiare le celle invece di eliminarele e ricrearele*/
        char *s;
        int rowtemp=0;
        result = getempty();
        if (result == NULL)
        {
            *err = MALLOC_FAILURE_CODA;
            clear(&pc);
        }
        else
        {
            /*estraggo fino alla fine*/
            while (!isempty(pc))
            {
                s = extract(pc,&rowtemp);
                /*ELABORAZIONE DELLA STRINGA*/
                sostituisci(&s,err);
                /*fine elaborazione*/
                append(result,s,rowtemp);
                /*copiando la stringa devo farne la free*/
                free(s);
            }
            result->tipo = machinecode_label;
            if (op == 3)
            {
                if(movetotop(result,"main:","MAIN:"))
                {
                    *err = MAIN_NOT_FOUND;
                    print_err(MAIN_NOT_FOUND,-1,NULL);
                    clear(&result);
                }
            }
            free(pc);
        }
    }
    else
    {
        result = pc;
    }
    
    return result;
}

/*
    rimuovo tutti i label che trovo nella coda
    il valore di ritorno indica se ho completato il lavoro senza problemi o no
*/
int * get_instruction_array(pcoda pc,int *dim,int *inizio,int * err)
{
    int *res = NULL;
    char *s = NULL;
    
    *dim = *inizio = 0;
    
    if (pc->tipo == machinecode_label)
    {
        /*interi utili alla fine per trovare dove parte il main*/
        int m1,m2;
        /*struttura per salvare i label*/
        pcoda label;
        /*variabile per gestire le righe*/
        int row;
        /*indice array istruzioni*/
        int i = 0;
        /*inizializzo la struttura*/
        label = getempty();
        
        res = (int *)malloc(sizeof(int)*pc->lengt); 
        if (res == NULL)
        {
            *err = MALLOC_FAILURE_INSTR_ARR;
            clear(&pc);
            free(label);
        }
        else
        {
            *dim = pc->lengt;
            while (!isempty(pc))
            {
                /*estraggo il primo elemento*/
                s = extract(pc,&row);
                if (just_num(s) == 0)
                {
                    /*genero la versione con :alla fine*/
                    int dist=0;
                    char *mod_s = (char *) malloc(strlen(s)+2);
                    if (mod_s == NULL)
                    {
                        *err = MALLOC_FAILURE;
                    }
                    else
                    {
                        strcpy(mod_s,s);
                    mod_s[strlen(s)]=':';
                    mod_s[strlen(s)+1]='\0';
                    if (s[strlen(s)-1] == ':')
                    {
                        append(label,s,i);
                    }
                        else
                        {
                            if ((dist=ispresent(label,mod_s)>=0))
                            {

                                res[i] = get_row(label,mod_s);
                            }
                            else if ((dist=ispresent(pc,mod_s))>=0)
                            {
                                
                                res[i] = dist+i;
                            }
                            else
                            {
                                *err = UNKOWN_WORD;
                                print_err(UNKOWN_WORD,row,s);
                            }
                            i++;
                        }
                        free(mod_s);
                    }
                }
                else
                {
                    res[i] = atoi(s);
                    i++;
                }
                free(s);
                s = NULL;
            }
            m1 = get_row(label,"main:");
            m2 = get_row(label,"MAIN:");
            if (m1>=0)
            {
                *inizio = m1;
            }else if (m2>=0)
            {
                *inizio = m2;
            }
            else
            {
                *err = MAIN_NOT_FOUND;
                print_err(MAIN_NOT_FOUND,-1,NULL);
            }
            clear(&label);
            free(pc);
        }
        
        
        
        
    }
    else if (pc->tipo == machinecode)
    {
        int temp;
        int row_temp;
        int i = 0;

        s = extract(pc,&row_temp);
        remove_semicolon(s);
        if(!just_num(s))
        {
            *err = UNKOWN_WORD;
            print_err(UNKOWN_WORD,row_temp,s);
        }
        temp = atoi(s); 
        free(s);

        res = (int*) malloc (sizeof(int)*temp);
        if (res == NULL)
        {
            *err = MALLOC_FAILURE_INSTR_ARR;
        }
        else
        {    
            *dim = temp;
            *inizio = 0; 
            while ( i < *dim && !isempty(pc))
            {

                s = extract(pc,&row_temp);
                remove_semicolon(s);
                if(!just_num(s)){
                    *err = UNKOWN_WORD;
                    print_err(UNKOWN_WORD,row_temp,s);
                }
                res[i] = atoi(s);
                free(s);
                i++;
            }
        }
        if (!isempty(pc))
        {
            *err = ARR_SIZE_INCORRECT;
            print_err(ARR_SIZE_INCORRECT,-1,NULL);
            clear(&pc);
        }
        else
        {
            free(pc);
        }
        
    }
    else
    {
        *err = UNKNOWN_FORMAT;
        print_err(UNKNOWN_FORMAT,-1,NULL);
    }
    if (*err != 0){
        free(res);
        res =  NULL;
    }
        
    return res;
}


void machinecode_print(int *instr_arr,int dim,int *err){
    int i=0;
    
    while(i<dim && !(*err)) {
        
        switch (instr_arr[i]){
            case HALT:
                printf("[%03d]  HALT\n",i);
                i++;
                break;
            case DISPLAY:
                printf("[%03d]  DISPLAY R%d\n",i,instr_arr[i+1]);
                i+=2;
                break;
            case PRINT_STACK:
                printf("[%03d]  PRINT_STACK %d\n",i,instr_arr[i+1]);
                i+=2;
                break;        
            case PUSH:
                printf("[%03d]  PUSH R%d\n",i,instr_arr[i+1]);
                i+=2;
                break;
            case POP:
                printf("[%03d]  POP R%d\n",i,instr_arr[i+1]);
                i+=2;
                break;
            case MOV:
                printf("[%03d]  MOV R%d  %d\n",i,instr_arr[i+1],instr_arr[i+2]);
                i+=3;
                break;
            case CALL:
                printf("[%03d]  CALL %d\n",i,instr_arr[i+1]);
                i+=2;
                break;
            case RET:
                printf("[%03d]  RETURN\n",i);
                i++;
                break;        
            case JMP:
                printf("[%03d]  JMP %d\n",i,instr_arr[i+1]);
                i+=2;
                break;
            case JZ:
                printf("[%03d]  JZ %d\n",i,instr_arr[i+1]);
                i+=2;
                break;
            case JPOS:
                printf("[%03d]  JPOS %d\n",i,instr_arr[i+1]);
                i+=2;
                break;
            case JNEG:
                printf("[%03d]  JNEG %d\n",i,instr_arr[i+1]);
                i+=2;
                break;
            case ADD:
                printf("[%03d]  ADD R%d R%d\n",i,instr_arr[i+1],instr_arr[i+2]);
                i+=3;
                break;
            case SUB:
                printf("[%03d]  SUB R%d R%d\n",i,instr_arr[i+1],instr_arr[i+2]);
                i+=3;
                break;
            case MUL:
                printf("[%03d]  MUL R%d R%d\n",i,instr_arr[i+1],instr_arr[i+2]);
                i+=3;
                break;
            case DIV:
                printf("[%03d]  DIV R%d R%d\n",i,instr_arr[i+1],instr_arr[i+2]);
                i+=3;
                break;
            default: 
                *err=INSTRUCTION_NOT_RECOGNIZED;
                i=dim;
                break;
        }
    }
    return;
}

int print_ass_to_cvm(int *instr_arr,int dim,const char *output){

    int str_l;
    char *str_ext;
    FILE *out;

    str_l=strlen(output);
    /*vedo la dimensione della stringa che gli passo e creo un aray che possa contenere quella +.cvm */
    str_ext=(char*)malloc(sizeof(char)*str_l+5);
    if (str_ext == NULL)
    {
        return MALLOC_FAILURE;
    }
    /*concateno il nome+ il formato in un array di grandezza esatta*/
    strcpy(str_ext,output);
    strcat(str_ext,".cvm");  
    out = fopen(str_ext,"w");
    /*faccio già il free di nome+formato perchè non mi serve più*/
    free(str_ext);


    if(out)
    {
        int i;
        fprintf(out,"%d\n",dim);

            for(i=0;i<dim;i++){
                fprintf(out,"%d\n",instr_arr[i]);
            }

        fclose(out);
        return NO_PROBLEM;
    }
    else 
        fclose(out);
    return CANNOT_SAVE_CVM;/*definire errore impossibile creare file*/
}
