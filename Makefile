#Compilador
COMPILER=gcc


###############################################################################################################################
#Nombre del ejecutable y archivos para compilar el programa
OUTPUT_FILE=BotonesyTijeras
FILES=buttonsAndScissorsFront.c buttonsAndScissorsBack.c main.c getnum2.c rand.c
###############################################################################################################################


###############################################################################################################################
#Nombre del ejecutable y archivos para compilar los testings
#OUTPUT_FILE=Testing
#FILES=CuTest.c AllTests.c FrontTestSuite.c BackTestSuite.c buttonsAndScissorsFront.c buttonsAndScissorsBack.c getnum2.c rand.c
###############################################################################################################################

all:
	$(COMPILER) -o $(OUTPUT_FILE) $(FILES) -Wall -pedantic -std=c99 -lm
clean:
	rm $(OUTPUT_FILE)
