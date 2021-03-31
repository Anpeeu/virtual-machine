/*  P1G94 854723 873888    */
#include "./cpu/cpu.h"
#include "./i_o/coda.h"
#include "./i_o/io_function.h"
#include "./err.h"

/* 
    Questa funzione sever a capire, a seconda dei parametri passati tramite riga di comando, cosa dovra fare il programma
        1 - stampa su schermo le istruzioni macchina (in formato assembly)
        2 - esegui il codice macchina o l'assembly contenuto nel passato in input
        3 - scrivi su file il codice macchina corrispondente all'assembly letto dal file in input 
        UNKNOWN_PARAMETER(404) il parametro in input non è stato riconosciuto
*/
int print_or_exe(const char *input){
    if(!strcmp(input,"stampa"))
    {
        return 1;
    }
    else if (!strcmp(input,"esegui"))
    {
        return 2;
    }
    else if (!strcmp(input,"assembla"))
    {
        return 3;
    }
    else
    {
        return UNKOWN_PARAMETER;
    }
}

int main(int argc,const char *argv[]){

    pcoda file;
    int err = 0;
    /* variabili legate all'array di istruzioni */
    int *arr = NULL;
    int dim;
    int inizio;

    if (argc == 3 || argc == 4)
    {
        int op = 0;
        op = print_or_exe(argv[1]);
        if (((op == 1 || op == 2) && argc == 3 ) || ( op == 3 && argc == 4)) 
        {
            file = readfile(argv[2],&err);
            if(!err)
                file = assembly_to_machinecode(file,op,&err);
            if(!err)
                arr = get_instruction_array(file,&dim,&inizio,&err);
            if (!err)
            {
                if(op == 1)
                {
                    machinecode_print(arr,dim,&err);
                    if(err)
                        print_err(err,-1,NULL);
                }
                if(op == 2)
                    err = execute(arr,(unsigned int)dim,inizio);
                if (op == 3)
                    err = print_ass_to_cvm(arr,dim,argv[3]);
            }
            if (arr)
                free(arr);
        }
        else
        {
            print_err(UNKOWN_PARAMETER,-1,NULL);
        }
        
    }
    else 
    {
        print_err(WRONG_NUMBER_PARAMETER,-1,NULL);
    }
    return 0;
}
