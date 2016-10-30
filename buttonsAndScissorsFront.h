#ifndef _buttonsAndScissorsFront_h
#define _buttonsAndScissorsFront_h

typedef struct 
{
	char** tab;
	int dim;
}tablero;
/*Recibe un una structura con un tablero y su dimension(ingresada por el usuario)
**lee en el archivo correspondiente a la dimension todos los tableros y de ellos elije uno aleatoriamente
**carga em ;a estructura recibida el tablero elegido
**Devuelve 0 si no ocurrieron errores, 1 si no hay archivos con esa dimension y 2 si hay un error de formato en el archivo.
*/
int GenerarTablero(tablero*);
/*Recibe una dimension y devuelve el nombre tiene el archivo correspondiente a esa dimension
**el nombre del archivo generado sigue los criterios especificados "dimensionxdimension" donde dimension es la variable recibida.
*/
char * GenerarNombre(int);
/*Lee de entrada estandard la opcion del menu principal elegida por el usuario*/
int LeerOpcion(void);
/*Imprime por salida estandard el tablero de juego*/
void imprimir(tablero);
#endif