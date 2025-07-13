out: main.o contact_operations.o file_operations.o
	cc  main.o contact_operations.o file_operations.o -o out

main.o: main.c
	cc -c main.c

contact_operations.o: contact_operations.c
	cc -c contact_operations.c

file_operations.o: file_operations.c
	cc -c file_operations.c

clean:
	rm -f *.o out

