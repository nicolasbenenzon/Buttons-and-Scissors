#include <stdio.h>
#include "getnum.h"
#include "rand.h"
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

#define BORRA_BUFFER while(getchar()!= '\n');
#define DEBUG
//#define DIM 5

typedef char * TipoLinea;
typedef TipoLinea * TipoTablero;
typedef struct
{
	int fila;
	int columna;
}tCoordenada;

int _DIM;

int JugadaValida(tablero * t, movimiento * mov, int * error);
int ExistePosicion(tCoordenada coordenada, int dim);
int EstaVacio(TipoTablero tablero, tCoordenada coordenada);
int DireccionCorte(movimiento * mov);
int HayOtrasVariedades(TipoTablero tablero, movimiento * mov);
int EfectuarCorte(TipoTablero tablero, movimiento * mov);
void CalcularDeltasFilCol(movimiento * mov);
void ReportarErrorPosicion(tCoordenada coordenada);
void ReportarErrorEspacioVacio(tCoordenada coordenada);
void ReportarErrorLineaRecta();
void ReportarErrorVariedades();
void ElegirDim();
void Jugar();
void Jugar2P();
void Menu();
void ImprimirMenu();
void Salir();
void LeerComando();
int Existe(char * archivo);
int Guardar(tJuego * juego);
int CargarArchivo(char * nombreArchivo, tJuego * juego);

int
main(void)
{
	randomize();
	
	int opcion = menu();
	switch(opcion)
	{
		case 1: case 2:
				ElegirDim();
				Jugar(opcion,t);
				break;
		case 3:
				Jugar(opcion,t);
				break;
		case 4:
				printf("Hasta luego, regrese cuando quiera.\n");

	}
	return 0;
	/*randomize();
	Menu();
	TipoTablero tablero;
	tablero = malloc(DIM * sizeof(*tablero));
	int i, j;
	for(i = 0; i < DIM; i++)
	{
		tablero[i] = malloc(DIM);
		for(j = 0; j < DIM; j++)
		{
			tablero[i][j] = randInt(0, 4) + 'A';
			printf("%c ", tablero[i][j]);
		}
		putchar('\n');
	}
	//tCoordenada origen = {0, 0};
	//tCoordenada destino = {2,0};
	//int cortes = JugadaValida(tablero, origen, destino, DIM);
	#ifdef DEBUG
		tablero[0][0] = '0'; tablero[0][1] = 'A'; tablero[0][2] = '0'; tablero[0][3] = '0'; tablero[0][4] = '0';
		tablero[1][0] = '0'; tablero[1][1] = '0'; tablero[1][2] = '0'; tablero[1][3] = 'B'; tablero[1][4] = 'D';
		tablero[2][0] = '0'; tablero[2][1] = '0'; tablero[2][2] = 'B'; tablero[2][3] = '0'; tablero[2][4] = '0';
		tablero[3][0] = '0'; tablero[3][1] = 'C'; tablero[3][2] = 'D'; tablero[3][3] = 'C'; tablero[3][4] = 'A';
		tablero[4][4] = 'B'; tablero[4][1] = '0'; tablero[4][2] = '0'; tablero[4][3] = '0'; tablero[4][4] = '0';
		tCoordenada origen = {3,2};
		tCoordenada destino = {1,4};
		int existe = JugadaValida(tablero, origen, destino, DIM);
		printf("%d\n", existe);
		for(i = 0; i < DIM; i++)
		{
			for(j = 0; j < DIM; j++)
			{
				printf("%c ", tablero[i][j]);
			}
			putchar('\n');
		}
		
	
	#endif
	for(i = 0; i < DIM; i++)
	{
		free(tablero[i]);
	}
	free(tablero);
	return 0;*/
}

void LeerComando()
{
	tCoordenada origen;
	tCoordenada destino;
	char cmd[5];
	char name[48];
	int done = 0;
	int F1, C1, F2, C2;
	char aux;
	do
	{
		printf("Ingrese el comando: ");
		if(scanf("%s %s", cmd, name) == 2)
		{
			if(strcmp(cmd, "save") == 0)
			{
				if(strlen(name) > 0)
				{
					Guardar(name);
					done = 1;
				}
				else printf("Debe ingresar un nombre válido de archivo.\n");
			}
			else printf("Comando inválido.\n");
		}
		else if(scanf("%s", cmd) == 1)
		{
			if(strcmp(cmd, "quit") == 0) 
			{
				char c;
				printf("¿Está seguro que quiere salir (Y/N)? ");
				scanf("%c", &c);
				if(c == 'Y')
				{
					printf("¿Desea guardar la partida antes de salir (Y/N)? ");
					scanf("%c", &c);
					if(c == 'Y')
					{
						printf("Ingrese el nombre del archivo: ");
						scanf("%s", name);
						if(strlen(name) > 0) 
						{
							Guardar(name);
							Salir();
						}
						else printf("Debe ingresar un nombre válido de archivo.\n");
					}
					else Salir();
				}
				else done = 1;
			}
			else printf("Comando inválido.\n");
		}
		else if(scanf("[%d,%d][%d,%d]%c", &F1, &C1, &F2, &C2, &aux) == 5)
		{
			if(aux != '\n') printf("Por favor, respete el formato indicado.\n");
			else
			{
				int error;
				int direccionCorte = -1;
				origen.fila = F1;
				origen.columna = C1;
				destino.fila = F2;
				destino.columna = C2;
				if((direccionCorte = jugadaValida(Tablero, origen, destino, _DIM, &error)) != -1) 
				{
					efectuarCorte(Tablero, origen, destino, direccionCorte);
					done = 1;
				}
				else
				{
					switch(error)
					{
						case 1: ReportarErrorPosicion(origen);
							break;
						case 2: ReportarErrorPosicion(destino);
							break;
						case 3: ReportarErrorEspacioVacio(destino);
							break;
						case 4: ReportarErrorEspacioVacio(origen);
							break;
						case 5: ReportarErrorLineaRecta();
							break;
						case 6: ReportarErrorVariedades();
							break;
					}
				}
				
			}
		}
		else printf("Comando inválido.\n");
	}
	while(done == 0);
}

int Menu(){
    ImprimirMenu();
    return LeerOpcion();    
}

void ImprimirMenu(){
    printf("MENÚ DEL JUEGO:\n");
    printf("1. Juego de dos jugadores\n");
    printf("2. Juego contra computadora\n");
    printf("3. Recuperar un juego grabado\n");
    printf("4. Terminar\n");
}
/*tablero es una estructura definida en front.h*/
void Jugar(int opcion,tablero t){
	int jugador1=1,jugador2=2,puntosjug1=0,puntosjug2=0,turno=rand()%2,termino;
	do
	{
		printf("Turno Jugador %d\n",(turno==0)?jugador1:jugador2);
		imprimir(t);
		if(turno==1&&opcion==2)
			JugarAI(t,&puntosjug2);
		else if(turno==1)
			Jugar2P(t,&puntosjug2);
		else
			Jugar2P(t,&puntosjug1);
		turno=(turno+1)%2;
		if(termino=esGanador(t))
			printf("El ganador es el jugador %d!!!\n",(turno==0)?jugador1:jugador2);
	}while(!termino);
}
	
/*tablero es un struct en front.c*/
void Jugar2P(tablero t,int* puntos,int jugador){
	LeerComando(puntos);
	
}

void ElegirDim()
{
	ElegirDimr();
	if(GenerarTablero(_DIM))
		//imprimir_Error
	
	/*cargo struct o parametros
	*/
}
void ElegirDimr(){
	/*do _DIM = getint("Ingrese la dimensión del tablero (Mínima: 5 (5x5), Máxima: 30 (30x30)): ");
	while(_DIM < 5 || _DIM > 30);*/
	printf("Ingrese la dimensión del tablero (Mínima: 5 (5x5), Máxima: 30 (30x30)): "); // MÉTODO RECURSIVO
	scanf("%d", &_DIM);
	if(_DIM < 5 || _DIM > 30) ElegirDimr();
}

void Salir(){
	exit();	
}

int Existe(char *archivo)
{
	struct stat buffer;
	return (stat(archivo, &buffer) == 0);
}

int JugadaValida(tablero * t, movimiento * mov, int * error)
{
	mov -> direccion = -1;
	//int botonesCortados = 0;
	
	//Verifico que exista la posición de origen, en caso negativo reporta el error y retorna 0
	if(ExistePosicion(mov -> inicio, t -> dim))
	{
		//En caso de existir la posición de origen, ahora verifico si existe la posición de destino, en caso negativo reporta el error y retorna 0
		if(ExistePosicion(mov -> final, t -> dim))
		{
			//Ahora verifico que tanto en el origen como en el destino haya algún botón, en caso negativo reporta el error y retorna 0
			if(!EstaVacio(t -> tab, mov -> inicio) && !EstaVacio(t -> tab, mov -> final))
			{
				//Luego verifico si el corte determinado por el origen y el destino forma efectivamente una línea recta
				if((mov -> direccion = DireccionCorte(mov)) != -1)
				{
					//Finalmente, se valida que no haya otras variedades de botones en esa dirección
					if(! HayOtrasVariedades(t -> tab, mov))
					{
						//En caso de haber cumplido con todos los requisitos, se efectúa el corte y guarda la cantidad de botones cortados
						//botonesCortados = EfectuarCorte(tablero, origen, destino, direccion);
						return mov -> direccion;
					}
					else
					{
						*error = 6;//ReportarErrorVariedades(); //Como hay más de una variedad de botones en esa dirección, reporta el error
					}
				}
				else
				{
					*error = 5;//ReportarErrorLineaRecta(); //Como el origen y destino no forman una línea recta, reporta el error
				}
			}
			else
			{
				//Si alguno de las 2 coordenadas es un espacio vacio entonces ve cuál es y reporta el error
				if(EstaVacio(t -> tab, mov -> inicio)) *error = 3;//ReportarErrorEspacioVacio(origen);
				else *error = 4;//ReportarErrorEspacioVacio(destino);
			}
		}
		else
		{
			//ReportarErrorPosicion(destino); //Como no existe la posición de destino, reporta el error
			*error = 2;
		}
	}
	else
	{
		//ReportarErrorPosicion(origen); //Como no existe la posición de origen, reporta el error
		*error = 1;
	}
	
	return -1;
}

int ExistePosicion(tCoordenada coordenada, int dim)
{
	return (coordenada.fila >= 0 && coordenada.fila < dim && coordenada.columna >= 0 && coordenada.columna < dim);
}

int EstaVacio(TipoTablero tablero, tCoordenada coordenada)
{
	return (tablero[coordenada.fila][coordenada.columna] == '0');
}

int DireccionCorte(movimiento * mov)
{
	if((mov -> inicio).fila == (mov -> final).fila) //Si ambos están en la misma fila
	{
		if((mov -> inicio).columna < (mov -> final).columna) //Si el final está a la derecha del inicio
			return 0;
		else 
			if((mov -> inicio).columna > (mov -> final).columna) //Si el final está a la izquierda del inicio
				return 180;
	}
	else if((mov -> inicio).columna == (mov -> final).columna) //Si están en la misma columna
	{
		if((mov -> inicio).fila < (mov -> final).fila) //Si el final está por debajo del inicio
			return 270;
		return 90; //El destino está por encima del origen
	}
	//Si no se cumplieron las condiciones anteriores, ahora se fija por las diagonales
	else if(abs((mov -> inicio).fila - (mov -> final).fila) == abs((mov -> inicio).columna - (mov -> final).columna))
	{
		//Si se forma una línea recta en diagonal, entonces retorna la respectiva dirección
		if((mov -> inicio).fila > (mov -> final).fila)
		{
			if((mov -> inicio).columna < (mov -> final).columna)
				return 45;
			return 135;
		}
		if((mov -> inicio).columna < (mov -> final).columna)
			return 315;
		return 225;
	}
	return -1; //En caso de no haber cumplido ninguna condición, significa que no forma una línea recta y retorna -1
}

int HayOtrasVariedades(TipoTablero tablero, movimiento * mov)
{
	int fil, col, hayBotonDistinto = 0;
	char botonOrigen = tablero[(mov -> inicio).fila][(mov -> inicio).columna]; //Guardo el botón que está en inicio
	char botonDestino = tablero[(mov -> final).fila][(mov -> final).columna]; //Guardo el botón que está en final
	
	//Primero verifico que en inicio y final haya el mismo botón, porque si son distintos, no tiene sentido recorrer todo el camino, ya se sabe que las variedades son distintas
	if(botonOrigen == botonDestino)
	{
		//Calculo el sentido en que hago el recorrido(se guarda en deltaFil y deltaCol), y recorro
		CalcularDeltasFilCol(mov);
		for(fil = (mov -> inicio).fila + mov -> deltaFil, col = (mov -> inicio).columna + mov -> deltaCol; fil != (mov -> final).fila && col != (mov -> final).columna && !hayBotonDistinto; fil += mov -> deltaFil, col += mov -> deltaCol)
		{
			if(tablero[fil][col] != botonOrigen && tablero[fil][col] != '0')
				hayBotonDistinto = 1;
		}
		return hayBotonDistinto;
	}
	else 
		return 1; //Si el destino y el origen tienen distintos botones, retorno 1
}

int EfectuarCorte(TipoTablero tablero, movimiento * mov)
{
	int fil, col;
	int botonesCortados = 2; //Lo inicializo en 2 porque de entrada corto los botones de origen y destino
	
	//Corto los botones de inicio y final
	tablero[(mov -> inicio).fila][(mov -> inicio).columna] = '0';
	tablero[(mov -> final).fila][(mov -> final).columna] = '0';
	
	//Calculo el sentido en que hago el corte, y corto contando la cantidad de botones cortados
	//CalcularDeltasFilCol(direccion, &deltaFil, &deltaCol);
	for(fil = (mov -> inicio).fila + mov -> deltaFil, col = (mov -> inicio).columna + mov -> deltaCol; fil != (mov -> final).fila && col != (mov -> final).columna; fil += mov -> deltaFil, col += mov -> deltaCol)
	{
		//Si hay un botón en esa posición, lo corta e incrementa la variable de botones cortados
		if(tablero[fil][col] != '0')
		{
			tablero[fil][col] = '0';
			botonesCortados++;
		}
	}
	
	return botonesCortados;
}

void CalcularDeltasFilCol(movimiento * mov)
{
	switch(mov -> direccion)
	{
		case 0:
			mov -> deltaFil = 0;
			mov -> deltaCol = 1;
		break;
		
		case 45:
			mov -> deltaFil = -1;
			mov -> deltaCol = 1;
		break;
		
		case 90:
			mov -> deltaFil = -1;
			mov -> deltaCol = 0;
		break;
		
		case 135:
			mov -> deltaFil = -1;
			mov -> deltaCol = -1;
		break;
		
		case 180:
			mov -> deltaFil = 0;
			mov -> deltaCol = -1;
		break;
		
		case 225:
			mov -> deltaFil = 1;
			mov -> deltaCol = -1;
		break;
		
		case 270:
			mov -> deltaFil = 1;
			mov -> deltaCol = 0;
		break;
		
		case 315:
			mov -> deltaFil = 1;
			mov -> deltaCol = 1;
		break;
	}
}

void ReportarErrorPosicion(tCoordenada coordenada)
{
	printf("Error: No existe la posición [%d,%d]\n", coordenada.fila, coordenada.columna);
}

void ReportarErrorEspacioVacio(tCoordenada coordenada)
{
	printf("Error: La posición [%d,%d] no tiene ningún botón\n", coordenada.fila, coordenada.columna);
}

void ReportarErrorLineaRecta()
{
	printf("Error: El corte no forma una línea recta\n");
}

void ReportarErrorVariedades()
{
	printf("Error: El corte no tiene una única variedad de botones\n");
}

int Guardar(tJuego * juego)
{
	int i;
	int dim = juego -> tableroJuego.dim; //Guarda la dirección del tablero en una variable auxiliar
	
	//Crea el archivo con el nombre nombreArch
	FILE * archPartida;
    	archPartida = fopen(juego -> nombreArch, "wb");
	
	//Se fija que no haya habido errores
	if(archPartida == NULL)
        return 0;
	
	//Escribe los datos de la partida en el archivo
    	fwrite(&(juego -> modoJuego), sizeof(juego -> modoJuego), 1, archPartida); //Modo de Juego (2P o Jugador vs. Computadora)
	fwrite(&(juego -> proximoTurno), sizeof(juego -> proximoTurno), 1, archPartida); //De quién es el próximo turno
	fwrite(&dim, sizeof(dim), 1, archPartida); //Dimensión del tablero
	for(i = 0; i < dim; i++)
		fwrite(juego -> tableroJuego.tab[i], dim, 1, archPartida); //Escribe cada fila del tablero en el archivo
	
	
    	//Una vez finalizada la escritura, cierra el archivo
	fclose(archPartida);
	
	return 1;
}

int CargarArchivo(char * nombreArchivo, tJuego * juego)
{
	int i;
	FILE * archPartida;
	int dim = juego -> tableroJuego.dim; //Guarda la dirección del tablero en una variable auxiliar
	
	//Pregunta si existe el archivo, y en ese caso lo abre en modo lectura 
	//(por ser lazy, si no existe el archivo nunca lo abre), y corrobora que no haya errores
	if(!Existe(nombreArchivo) || (archPartida = fopen(nombreArch, "rb")) == NULL)
		return 0;
	
	
	//Lee los datos del archivo y carga las variables
	juego -> nombreArch = nombreArch;
	fread(&(juego -> modoJuego), sizeof(juego -> modoJuego), 1, archPartida);
	fread(&(juego -> proximoTurno), sizeof(juego -> proximoTurno), 1, archPartida);
	fread(&(juego -> tableroJuego.dim), sizeof(dim), 1, archPartida);
	
	juego -> tableroJuego.tab = malloc(dim * sizeof(char*));
	
	for(i = 0; i < dim; i++)
	{	
		juego -> tableroJuego.tab[i] = malloc(dim);
		fread(juego -> tableroJuego.tab[i], dim, 1, archPartida);
	}
	
	//Cierra el archivo
	fclose(archPartida);
	
	return 1;
}
