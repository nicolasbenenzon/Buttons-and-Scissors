#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "buttonsAndScissorsBack.h"
#include "buttonsAndScissorsFront.h"
#define LIMPIABUFFER() while(getchar()!='\n')

/* lee tableros de un archivo elije uno aleatoriamente y lo carga en el tablero del juego*/
int GenerarTablero(tablero* t)
{
	FILE* arch=NULL;
	t->tab=NULL;
	char * nombre=GenerarNombre(t->dim);
	arch=fopen(nombre,"r");
	if(arch==NULL)
		return 1;
	else
	{
		int cant=0,i=0,j,k,salir=0,c,elegido;
		char n1;
		while((n1=fgetc(arch))!='\n'&&isdigit(n1))
		{
			cant=cant*10+n1-'0';
		}
		
		if(n1!='\n')
		{
			salir=2;
		}
		elegido=rand()%cant;
		while(!feof(arch)&&(!salir))
		{
			if(i==elegido)
				//t->tab=malloc(sizeof(char*)*(t->dim));
				validarMemoria((void**)(&(t->tab)),sizeof(char*)*(t->dim));
			for(j=0;j<t->dim&&(!salir);j++)
			{
				if(i==elegido)
					//(t->tab)[j]=malloc(sizeof(char)*(t->dim));
					validarMemoria((void**)((t->tab)+j),sizeof(char)*(t->dim));
				for(k=0;k<t->dim&&(!salir);k++)
				{
					c=fgetc(arch);
					if((isalpha(c)&&isupper(c))||c==' ')
					{
						if(i==elegido)
						{
							if(c==' ')
							{
								(t->tab)[j][k]='0';
							}
							else
								(t->tab)[j][k]=c;
						}
						
					}
					else
					{
						salir=2;
					}
				}
				c=fgetc(arch);
				if(!feof(arch)&&(salir=(c!='\n')))
				{
					salir=2;
				}			
			}
			if(!salir)
			{	
				c=fgetc(arch);
				if(!feof(arch)&&(salir=(c!='-')))
				{
					salir=2;
				}
				else
				{
					c=fgetc(arch);
					if(!feof(arch)&&(salir=(c!='\n')))
					{
						salir=2;
					}
				}
			}
			i++;
		}
		if(i<cant)
			salir=2;
		if(salir)
		{
			if(t->tab!=NULL)
			{
				for(j=0;j<t->dim;j++)
					free((t->tab)[j]);
				free(t->tab);
			}
		}

		return salir;
	}
	
}

/*Recibe la direccion de memoria del puntero al que quiero asignarle memoria y la cantidad de bytes que quiero asignarle*/
void validarMemoria(void **punt,unsigned int bytes)
{
	void *aux;
	aux=realloc(*punt,bytes);
	if(aux==NULL)
	{
		printf("Espacio insuficiente.\n");
		exit(0);
	}
	*punt=aux;
}


void imprimirErrorTablero(int error)
{
	switch(error)
	{
		case 1:
						printf("El archivo solicitado no existe.\n");
						break;
		case 2: 
						printf("Error de Formato.\n");
						break;
	}
}	
	
/*Genera el nombre del archivo en el cual buscar los tableros a partir de la dimension ingresada por el usuario*/
char * GenerarNombre(int dimension)
{
	char *nombre=NULL;
	//nombre=malloc(sizeof(*nombre)*6);
	validarMemoria((void**)(&nombre),6);
	if(nombre==NULL)
	{
		printf("No hay memoria suficiente para generar el archivo.\n");
		return nombre;
	}
		sprintf(nombre,"%dx%d",dimension,dimension);
	return nombre;
}
/*Imprime el tablero por salida estandar*/
void imprimir(tablero tabjuego)
{
	int i,j;
	
	
		for(i=0;i<2;i++)
		{
			printf("\t");
			for(j=0;j<tabjuego.dim;j++)
			{
				if(i==0)
				{
					if(j<10)
						printf("%d  ",j);
					else
						printf("%d ",j);
				}
				else
					printf("---");
			}
			printf("\n");
		}
		for(i=0;i<tabjuego.dim;i++)
		{
				if(tabjuego.dim<10)
					printf("%d|\t",i);
				else
				{
					if(i<10)
						printf("%d |\t",i);
					else
						printf("%d|\t",i);
				}
			for(j=0;j<tabjuego.dim;j++)
			{
					if((tabjuego.tab)[i][j]=='0')
						printf("   ");
					else
						printf("%c  ",(tabjuego.tab)[i][j]);
			}
			printf("\n");
		}
		printf("\n\n");
}
/*Lee una opcion del menu principal por entrada estandard*/
int LeerOpcion(void)
{
	int opcion;
	char c;
	do
	{
		c=0;
		printf("Ingrese la opcion: ");
		scanf("%d%c",&opcion,&c);
		if(c!='\n')
		{
			LIMPIABUFFER();
			printf("Debe ingresar solo un numero entero entre 1 y 4 y luego enter.\n");
		}
		else if(opcion>=5||opcion<=0)
		{
			printf("El numero debe ser 1 2 3 o 4.\n");
		}
	}while(c!='\n'||opcion>=5||opcion<=0);
	return opcion;
}


int Menu()
{
    ImprimirMenu();
    return LeerOpcion();
   
}

void ImprimirMenu()
{
    printf("MENÚ DEL JUEGO:\n");
    printf("1. Juego de dos jugadores\n");
    printf("2. Juego contra computadora\n");
    printf("3. Recuperar un juego grabado\n");
    printf("4. Terminar\n");
}

void jugar(tJuego* juego)
{
	int jugador1=1,jugador2=2,puntosjug1=0,puntosjug2=0,termino;
	juego->proximoTurno=rand()%2;
	do
	{
		printf("Botones J1: %d, J2:%d\n\n",puntosjug1,puntosjug2);
		imprimir(juego->tableroJuego);
		printf("Turno jugador %d\n",(juego->proximoTurno==0)?jugador1:jugador2);
		if((termino=hayGanador(juego->tableroJuego)))//por si empieza con tablero vacio
			printf("El ganador es el jugador %d!!!\n",(juego->proximoTurno==0)?jugador1:jugador2);
		else
		{
			if(juego->proximoTurno==1&&juego->modoJuego==1)
				jugarAi(&(juego->tableroJuego),&puntosjug2);
			/*else if(turno==1)
				Jugar2P(t,&puntosjug2);
			else
				Jugar2P(t,&puntosjug1);*/
			//turno=(turno+1)%2;
			if((termino=hayGanador(juego->tableroJuego)))//si no hay mas jugadas posibles o si quedo vacio el tablero
				printf("El ganador es el jugador %d!!!\n",(juego->proximoTurno==0)?jugador1:jugador2);
			else
			juego->proximoTurno=(juego->proximoTurno+1)%2;
		}
	}while(!termino);
}