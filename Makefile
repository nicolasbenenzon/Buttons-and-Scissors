#Compilador
COMPILER=gcc


###############################################################################################################################
#Nombre del ejecutable y archivos para compilar el programa
OUTPUT_FILE=juego
FILES=buttonsAndScissorsFront.c buttonsAndScissorsBack.c main.c rand.c
###############################################################################################################################


###############################################################################################################################
#Nombre del ejecutable y archivos para compilar los testings
#OUTPUT_FILE=Testing
#FILES=CuTest.c AllTests.c FrontTestSuite.c BackTestSuite.c buttonsAndScissorsFront.c buttonsAndScissorsBack.c rand.c
#para ejecutar los test debe redireccionarse la entrada con el archivo
###############################################################################################################################

all:
	$(COMPILER) -o $(OUTPUT_FILE) $(FILES) -Wall -pedantic -std=c99 
clean:
	rm $(OUTPUT_FILE)
