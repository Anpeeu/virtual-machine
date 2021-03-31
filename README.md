# virtual-machine
Questo progetto è stato ideato come parte di laboratorio del linguaggio di programmazione C, del medesimo corso a Ca'Foscari 2019. 
Il progetto consisteva nell'eseguire del codice Assembly-like scritto in linguaggio macchina in base 10.
Dalla consegna iniziale si sono volute aggiungere altre funzionalità, descritte in seguito.

## Installazione sistema Unix
Copiare la cartella del progetto nel vostro computer, esempio tramite clone.
- `git clone https://github.com/Anpeeu/virtual-machine.git`

Accedere alla cartella appena creata.
- `cd virtual-machine`
  
Eseguire il comando make per compilare il progetto, necessario aver installato nel sistema il compilatore C gcc.
- `make`
  
Attendere il completamento della compilazione, è possibile rimuovere tutti i file compilati eseguendo il comando 
- `make clean`


## Utilizzo
Il programma permette di effettuare 3 operazioni:
- esecuzione, di codice sia testuale che in codice macchina
- stampa, in formato testuale, non numerico di un programma 
- assemblazione, funzione che permetteva di tradurre del codice Assembly-like scritto in modo testuale, compreso di label, in codice macchina.  
  
La struttura per eseguire/stampare il programma è 
`./VM (esegui, stampa) ./pathfile/nomefile.(cvm, ass)`
Breve esempio di esecuzione del programma 
`./VM esegui ./test_file/while.cvm`

### Esecuzione
Il comando `esegui` permette l'esecuzione del codice salvato nel file inserito nel secondo parametro.
Il codice eseguito non effettuerà nessuna stampa se non è esplitcitamente scritto nel codice.
L'esecuzione avviene sia che il file contenga codice .ass (formato assembly-like) che .cvm (codice macchina)

`./VM esegui ./pathfile/nomefile.(cvm, ass)`

### Stampa
Il comando `stampa` permette la stampa in formato Assembly-like in modo sequenziale a come è scritto, non quindi seguando il flusso del programma, del codice salvato nel file inserito nel secondo parametro.

`./VM stampa ./pathfile/nomefile.(cvm, ass)`

### Assembla
Il comando `assembla` permette la traduzione di un file da Assembly-like a codice macchina. 
Essendo una funzionalità fuori dalla specifica di progetto si è preferito aggiungere la funzionalità per permettere la creazione di test case scritti in linguaggio Assembly-like per poi tradurli in codice macchina e condividerli ad altri gruppi.
Esempio di assemblazione su il file while.ass dalla cartella principale del programma

`./VM assembla test_file/while.ass test_file/while(salva nella cartella dei file di test)`

È possibile assemblare anche un file in codice macchina, questo porterà alla creazione di un file sempre in codice macchina ma privo di commenti.

In caso di file scritto in codice macchina ma privo del numero di righe del programma alla prima riga, quindi contro le specifiche di progetto, se viene inserito il label del main `main:` compre prima riga del file e compilato il file il programma risolverà il problema.

## Formato Assembly-like
Questo formato si basa sulle istruzioni in formato Assembly-like, qui lo schema delle istruzioni supportate.

Istruzione | CM | Descrizione
------------ | ------------- | -------------
HALT | 0 | -
DISPLAY | 1 | -
PRINT_STACK | 2 | -
PUSH | 10 | -
POP | 11 | -
MOV | 12 | -
CALL | 20 | -
RET | 21 | -
JMP | 22 | -
JZ | 23 | -
JPOS | 24 | -
JNEG | 25 | -
ADD | 30 | -
SUB | 31 | -
MUL | 32 | -
DIV | 33 | -

Inoltre, è possibile e necessario, utilizzare un sistema di label al posto delle righe statiche, che rendono la programmazione fastidiosa fissi nelle istruzioni di salto.
In questo caso il codice non verrà eseguito in modo sequenziale dall'alto ma verrà eseguita la prima istruzione dopo il label `main:` che quindi diventa di obbligatoria presenza.

La scrittura dei label deve rispettare la seguente specifica
- Definizione -> `nome_label:` quindi con nome e due punti tutti attaccati.
- Utilizzo -> `JZ exit_while` nell'utilizzo è necessario utilizzare solo il nome, privo di due punti.

## Esempi di programma 
Questi esempi sono salvati nella cartella `./test_file/...`

#### Somma dei primi n-1 numeri
```
main:
    MOV r0, 1
    DISPLAY R0
    MOV r1, 1
    DISPLAY R1
    MOV r2, 0       ;accumulatore 
    DISPLAY R2     
    MOV r3, 11      ;quanti numeri devo stampare partendo da 0
    DISPLAY R3
loop: 
    ;calcolo della condizione e push nello stack
    SUB r1, r3
    JZ exit_while
    ADD r1, r2 
    POP r2
    ADD r1, r0
    POP r1
    JMP loop

exit_while: 
    DISPLAY r2
    HALT
```

