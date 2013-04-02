
all: serial paralel optim 


serial: serial.c
	gcc serial.c -o serial

optim: optimnew.c
	gcc optimnew.c -o optim

paralel: paralel.c
	gcc -fopenmp paralel.c -o paralel

clean:
	rm -rf paralel serial
