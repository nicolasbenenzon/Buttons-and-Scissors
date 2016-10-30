#ifndef _buttonsAndScissorsBack_h
#define _buttonsAndScissorsBack_h

typedef struct 
{
	char** tab;
	int dim;
}tablero;
/*Recibe el tablero de Juego y la direccion de donde se almacena el puntaje
**elije aleatoriamente una estrategia(movimiento con minima cantidad de botones o con maxima cantidad de botones)
**y de acuerdo a la estrategia ya sea en el maximo o el minimo de todos los que tengan esa cantidad de botones elije uno aleatoriamente
*/
void JugarAi(tablero*,int *);
/*Recibe el tablero una fila y una columns y un incremento para la fila y para la columna
**recorre el tablero a partir de la fila y columna recibida sumandole los incrementos
**devuelve cuantos botones del mismo tipo al que esta en la fila y columna recibida hay en la direccion dada por los incrementos*/
int buscdir(tablero,int,int,int,int,int);
#endif