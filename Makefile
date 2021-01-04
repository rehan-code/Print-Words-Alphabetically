all: alphabetical_printing

alphabetical_printing: alphabetical_printing.o
	gcc -ansi -Wall -o alphabetical_printing alphabetical_printing.o

alphabetical_printing.o: alphabetical_printing.c
	gcc -ansi -Wall -c alphabetical_printing.c

clean:
	rm *.o alphabetical_printing
