COMPILER=gcc
OUTPUT_FILE=BotonesYTijeras
FILES= AllTests.c BackTestSuite.c CuTest.c FrontTestSuite.c buttonsAndScissorsBack.c buttonsAndScissorsFront.c main.c getnum2.c rand.c

all:
	$(COMPILER) -o $(OUTPUT_FILE) $(FILES) -Wall -pedantic -std=c99 -lm
clean:
	rm $(OUTPUT_FILE)
