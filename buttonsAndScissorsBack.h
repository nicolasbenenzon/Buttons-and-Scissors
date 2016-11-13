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
	int puntosJug1;
	int puntosJug2;
}tJuego;


/* Recibe un puntero a la struct tablero, otro a la struct movimiento y otro a la variable error.
** Evalúa unos cuantos aspectos del movimiento. En caso de ser válido devuelve en su nombre la dirección del corte, y en caso
** contrario devuelve -1, y deja en la variable error un número identificador del error encontrado en ese movimiento para que
** LeerComando se encargue de imprimir el error correspondiente al valor de la variable error.
*/
int JugadaValida(tablero * t, movimiento * mov, int * error);

// Recibe una coordenada y la dimensión del tablero, y devuelve TRUE si esa posición existe, y FALSE en caso contrario. 
int ExistePosicion(tCoordenada coordenada, int dim);

//Recibe el tablero y una coordenada, y devuelve TRUE si esa posición está vacía, y FALSE en caso contrario.
int EstaVacio(TipoTablero tablero, tCoordenada coordenada);

/* Recibe el tablero y un puntero a la struct movimiento, donde se guarda el movimiento que quiere hacer el usuario.
** Devuelve 1 si hay algún botón de otro color en el camino desde el primero al último botón del corte ingresado,
** y 0 en caso contrario.
*/
int HayOtrasVariedades(TipoTablero tablero, movimiento * mov);

/* Recibe un puntero a la struct movimiento y guarda según la dirección cómo varía en cada paso el movimiento en cuanto a filas
** y columnas.
*/
void CalcularDeltasFilCol(movimiento * mov);

/* Recibe un puntero a la struct movimiento y devuelve en su nombre el ángulo que forma la dirección del corte (0 si es hacia el este, 
** 45 si es hacia el noreste, 90 si es hacia el norte, etc.). En caso de que el corte no forme una línea recta retorna -1.
*/
int DireccionCorte(movimiento * mov);

/* Recibe el tablero y un puntero a la struct movimiento, efectúa el corte eliminando los botones, y retorna la cantidad
** de botones cortados en esa jugada.
*/
int EfectuarCorte(TipoTablero tabler, movimiento * mov);


/*Recibe el tablero de Juego y la direccion de donde se almacena el puntaje
**elige aleatoriamente una estrategia(movimiento con minima cantidad de botones o con maxima cantidad de botones)
**y de acuerdo a la estrategia ya sea en el maximo o el minimo de todos los que tengan esa cantidad de botones elige uno aleatoriamente
*/
int jugarAi(tablero* t,int *puntos);


/*Recibe el tablero una fila y una columna y un incremento para la fila y para la columna y la direccion a la variable botones
**recorre el tablero a partir de la fila y columna recibida sumandole los incrementos
**devuelve en su nombre la cantidad de espacios que recorrio 
**modifica a botones colocando cuantos botones del mismo tipo al que esta en la fila y columna recibida hay en la direccion dada por los incrementos
*/
int buscdir(tablero t,int modo,int fila,int columna,int incfil,int inccol,int *botones);


/*Recibe el tablero y devuelve en su nombre 1 si no hay mas jugadas posibles para el jugador siguiente y 0 en caso contrario*/
int hayGanador(tablero t);



/*Recibe la direccion de memoria del puntero al que quiero asignarle memoria y la cantidad de bytes que quiero asignarle*/
int validarMemoria(void **punt,unsigned int bytes);

/*Recibe un puntero a la estructura juego y libera la memoria que se reservo para el tablero 
**ya sea en CargarTablero como en GenerarTablero
*/
void liberarTablero(tablero * t);

#endif
