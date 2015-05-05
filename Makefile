blind: blind.c	Makefile
	gcc -O3 -Wall -std=c99 blind.c -o $@ -lssl -lcrypto
