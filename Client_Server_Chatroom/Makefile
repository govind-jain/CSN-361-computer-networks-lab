cc = gcc
allowances = -Wall -g3 -fsanitize=address

compile:
	$(cc) $(allowances) -pthread server.c -o server
	$(cc) $(allowances) -pthread client.c -o client