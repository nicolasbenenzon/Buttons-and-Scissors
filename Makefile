COMPILER=gcc
OUTPUT_FILE=prueba
FILES= ejercicio1.c getnum2.c rand.c

all:
	$(COMPILER) -o $(OUTPUT_FILE) $(FILES) -Wall -pedantic -std=c99 -lm
clean:
	rm $(OUTPUT_FILE)