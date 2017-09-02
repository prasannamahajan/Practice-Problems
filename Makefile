all : dictionary
dictionary : main.c
	cc -g main.c -o dictionary
run : dictionary
	./dictionary < input

