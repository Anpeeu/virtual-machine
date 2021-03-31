#  P1G94 854723 873888 
objects = main.o err.o cpu.o istr.o coda.o io_function.o
eseguibile = VM
cflags = -g3 -fsanitize=address -fsanitize=undefined -std=gnu89 -pedantic-errors -Wall -Wextra 
libs = -lm

$(eseguibile) : $(objects)
	gcc $(cflags) -o $(eseguibile) $(objects) $(libs)

main.o : main.c 
	gcc $(cflags) -c main.c $(libs)

err.o : err.c
	gcc $(cflags) -c err.c $(libs)
	
cpu.o :  ./cpu/cpu.c
	gcc $(cflags) -c ./cpu/cpu.c $(libs)

istr.o : ./cpu/istr.c
	gcc $(cflags) -c ./cpu/istr.c $(libs)

coda.o : ./i_o/coda.c
	gcc $(cflags) -c ./i_o/coda.c $(libs)

io_function.o : ./i_o/io_function.c
	gcc $(cflags) -c ./i_o/io_function.c $(libs)


#Funzioni di utilità 
clean:
	rm $(eseguibile)  $(objects)

