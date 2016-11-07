#ifndef _buttonsAndScissorsFront_h
#define _buttonsAndScissorsFront_h

/*Imprime el menu con las opciones y devuelve la opcion elegida*/
int Menu(void);


/*Imprime el menu con las opciones posibles*/
void ImprimirMenu(void);


/*Lee de entrada estandard la opcion del menu principal elegida por el usuario*/
int LeerOpcion(void);


/*Recibe una dimension y devuelve el nombre tiene el archivo correspondiente a esa dimension
**el nombre del archivo generado sigue los criterios especificados "dimensionxdimension" donde dimension es la variable recibida.
*/
char * GenerarNombre(int);


/*Recibe un una structura con un tablero y su dimension(ingresada por el usuario)
**lee en el archivo correspondiente a la dimension todos los tableros y de ellos elije uno aleatoriamente
**carga em ;a estructura recibida el tablero elegido
**Devuelve 0 si no ocurrieron errores, 1 si no hay archivos con esa dimension y 2 si hay un error de formato en el archivo.
*/
int GenerarTablero(tablero*);


/*Imprime por salida estandard el tablero de juego*/
void imprimir(tablero);


/*Recibe el valor del error que se produjo y imprime el mensaje correspondiente al error.*/
void imprimirErrorTablero(int error);


/*Recibe la direccion de memoria del puntero al que quiero asignarle memoria y la cantidad de bytes que quiero asignarle*/
void validarMemoria(void **punt,unsigned int bytes);


/*Recibe la direccion de memoria de la estructura juego donde estan los datos necesarios del juego, el tablero y su dimension y el modo de juego
**y actua en concordancia con el modo de juego(dos jugadores o jugagador y pc),
**imprime los puntos,el tablero,a quien le corresponde el turno y quien es el ganador de la partida.
*/
void jugar(tJuego*);

#endif