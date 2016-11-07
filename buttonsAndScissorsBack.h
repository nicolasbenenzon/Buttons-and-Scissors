#ifndef _buttonsAndScissorsBack_h
#define _buttonsAndScissorsBack_h
typedef char ** TipoTablero;
typedef struct 
{
	int fila;
	int columna;
}tCoordenada;

typedef struct
{
	tCoordenada inicio;
	tCoordenada final;
	int direccion;
	int deltaFil;
	int deltaCol;
}movimiento;

typedef struct 
{
	TipoTablero tab;
	int dim;
}tablero;

typedef struct
{
	tablero tableroJuego;
	char * nombreArch;
	int modoJuego;
	int proximoTurno;
}tJuego;

void CalcularDeltasFilCol(movimiento * mov);
int DireccionCorte(movimiento * mov);
int EfectuarCorte(TipoTablero tabler, movimiento * mov);

/*Recibe el tablero de Juego y la direccion de donde se almacena el puntaje
**elije aleatoriamente una estrategia(movimiento con minima cantidad de botones o con maxima cantidad de botones)
**y de acuerdo a la estrategia ya sea en el maximo o el minimo de todos los que tengan esa cantidad de botones elije uno aleatoriamente
*/
void jugarAi(tablero* t,int *puntos);
/*Recibe el tablero una fila y una columns y un incremento para la fila y para la columna y la direccion a la variable botones
**recorre el tablero a partir de la fila y columna recibida sumandole los incrementos
**devuelve en su nombre la cantidad de espacios que recorrio 
**modifica a botones colocando cuantos botones del mismo tipo al que esta en la fila y columna recibida hay en la direccion dada por los incrementos
*/
int buscdir(tablero t,int modo,int fila,int columna,int incfil,int inccol,int *botones);
/*Recibe el tablero y devuelve en su nombre 1 si no hay mas jugadas posibles para el jugador siguiente y 0 en caso contrario*/
int hayGanador(tablero t);

#endif