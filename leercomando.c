#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LONG 256
#define MAX_NAME 48

#define LIMPIA_BUFFER() while(getchar() != '\n')

typedef char ** TipoTablero;
typedef struct 
{
	TipoTablero tab;
	int dim;
}tablero;

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
void LeerComando(tablero * t);

int main(void)
{
	tablero t;
	LeerComando(&t);


}
/*int ExistePosicion(tCoordenada coordenada, int dim);
int EstaVacio(TipoTablero tablero, tCoordenada coordenada);
int DireccionCorte(movimiento * mov);
int HayOtrasVariedades(TipoTablero tablero, movimiento * mov);
int EfectuarCorte(TipoTablero tablero, movimiento * mov);
void CalcularDeltasFilCol(movimiento * mov);
void ReportarErrorPosicion(tCoordenada coordenada);
void ReportarErrorEspacioVacio(tCoordenada coordenada);
void ReportarErrorLineaRecta();
void ReportarErrorVariedades();*/

void LeerComando(tablero * t){
	movimiento mov;
	char cmd[MAX_LONG];
	char name[MAX_NAME] = {0};
	int done = 0;
	int F1, C1, F2, C2;
	char aux, c;
	do
	{
		printf("Ingrese un comando: ");
		fgets(cmd, MAX_LONG, stdin);
		if(strcmp(cmd, "quit\n") == 0)
		{
			char c1;
			printf("¿Está seguro que quiere salir (Y/N)? ");
			fgets(cmd, MAX_LONG, stdin);
			//scanf("%c%c", &c1, &aux);
			if(strcmp(cmd, "Y\n") == 0)
			{
				printf("¿Desea guardar la partida antes de salir (Y/N)? ");
				fgets(cmd, MAX_LONG, stdin);
				if(strcmp(cmd, "Y\n") == 0)
				{
					
						printf("Ingrese el nombre del archivo: ");
						fgets(name, MAX_NAME, stdin);
						//scanf("%s%c", name, &aux);
						if(strlen(name) > 0 && name[0] != '\n') 
						{
								//Guardar(name);
								printf("El archivo se guardo exitosamente.\nHasta luego\n");
								done = 1;
								//Salir();
							
						}
						else printf("Debe ingresar un nombre válido de archivo.\n");
					
				}
				else if(strcmp(cmd, "N\n") == 0)
				{
					//Salir();
					printf("back to menu\n");
					done = 1;
				}
				else
					printf("Comando invalido.\n");
			}
			else if(strcmp(cmd, "N\n") != 0)
			{
				printf("Comando invalido.\n");
			}
		}
		else
		{
			if(sscanf(cmd, "save %s%c", name, &aux) == 2 && aux == '\n')
			{
				if(strlen(name) > 0) 
				{
					//Guardar(name);
					printf("El archivo se guardo exitosamente.\n");
				}
				else printf("Debe ingresar un nombre válido de archivo.\n");
			}
			else if(sscanf(cmd, "[%d,%d][%d,%d]%c", &F1, &C1, &F2, &C2, &aux) == 5 && aux == '\n')
			{
				int error;
				int direccionCorte = -1;
				mov.inicio.fila = F1;
				mov.inicio.columna = C1;
				mov.final.fila = F2;
				mov.final.columna = C2;
				printf("F1=%d\tC1=%d\nF2=%d\tC2=%d\n",F1,C1,F2,C2);
				done = 1;
			}
			else printf("Comando inválido.\n");
		}
	}
	while(done == 0);
//jugadavalida
}
