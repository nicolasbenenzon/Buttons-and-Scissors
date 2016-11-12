#ifndef _buttonsAndScissorsFront_h
#define _buttonsAndScissorsFront_h

/*Fucion que controla el flujo del juego, llama a Menu y recibe la opcion elegida por el usuario 
**y de acuerdo a ella continua con la ejecucion del juego
*/
void botonesyTijeras(void);

/*Imprime el menu con las opciones y devuelve la opcion elegida*/
int Menu(void);


/*Imprime el menu con las opciones posibles*/
void ImprimirMenu(void);


/*Lee de entrada estandard la opcion del menu principal elegida por el usuario*/
int LeerOpcion(void);


void ElegirDim(tablero * t);


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


int LeerComando(tJuego *);


/*Recibe la direccion de memoria de la estructura juego donde estan los datos necesarios del juego, el tablero y su dimension y el modo de juego
**y actua en concordancia con el modo de juego(dos jugadores o jugagador y pc),
**imprime los puntos,el tablero,a quien le corresponde el turno y quien es el ganador de la partida.
*/
void jugar(tJuego* juego);


int jugar2P(tJuego* juego);


int Guardar(tJuego * juego);

/*Lee de entrada estandard el nombre del archivo que el usuario quiere cargar*/
void leerNombre(tJuego* juego);


/*Recibe un puntero a una estructura donde cargara los datos leidos del archivo
**Le pide al usuario el nombre del archivo, se fija si existe y lo abre
**de acuerdo al orden especificado guarda los datos leidos en los campos de la estructura
**devuelve cero si no logra abrir el archivo y uno en caso contrario
*/
int CargarArchivo(tJuego * juego);


int Existe(char *archivo);


/*Recibe un puntero a la estructura juego y libera la memoria que se reservo para el tablero 
**ya sea en CargarTablero como en GenerarTablero
*/
void liberarTablero(tJuego * juego);

#endif