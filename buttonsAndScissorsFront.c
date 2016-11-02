#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "buttonsAndScissorsFront.h"
#define LIMPIABUFFER() while(getchar()!='\n')
/*typedef struct 
{
	char** tab;
	int dim;
}tablero;*/
//tablero t={NULL,5};
char ** Tablero=NULL;
int _DIM=5;
/* lee tableros de un archivo elije uno aleatoriamente y lo carga en el tablero del juego*/
int GenerarTablero()
{
	FILE* arch=NULL;
	char * nombre=GenerarNombre(_DIM);
	char ** aux;

			
	arch=fopen(nombre,"r");
	if(arch==NULL)
	{
		printf("El archivo con nombre: %s no existe.\n",nombre);
		return 1;
	}
	else
	{
		int cant=0,i=0,j,k,salir=0,c,elegido;
		Tablero=malloc(sizeof(*Tablero)*_DIM);
		aux=malloc(sizeof(*aux)*_DIM);
		for(j=0;j<_DIM;j++)
		{	
			Tablero[j]=malloc(sizeof(char)*_DIM);
			aux[j]=malloc(sizeof(char)*_DIM);
		}
		char n1;
		while((n1=fgetc(arch))!='\n'&&isdigit(n1))
		{
			cant=cant*10+n1-'0';
		}
		
		if(n1!='\n')
		{
			printf("Error de formato.\n");
			return 2;
		}
		elegido=rand()%cant;
		printf("El elegido es: %d\n\n\n",elegido);
		while(!feof(arch)&&(!salir))
		{

			for(j=0;j<_DIM&&(!salir);j++)
			{
				for(k=0;k<_DIM&&(!salir);k++)
				{
					c=fgetc(arch);
					if((isalpha(c)&&isupper(c))||c==' ')
					{
						if(i==elegido)
							Tablero[j][k]=c;
						else
							aux[j][k]=c;
					}
					else
					{
						salir=2;
						printf("Error de formato.\n");
					}
				}
				c=fgetc(arch);
				if(!feof(arch)&&(salir=(c!='\n')))
				{
					printf("Error de formato.\n");
					salir=2;
				}			
			}
			if(!salir)
			{	
				c=fgetc(arch);
				if(!feof(arch)&&(salir=(c!='-')))
				{
					printf("Error de formato.\n");
					salir=2;
				}
				else
				{
					c=fgetc(arch);
					if(!feof(arch)&&(salir=(c!='\n')))
					{
						printf("Error de formato.\n");
						salir=2;
					}
				}
			}
			if(i==elegido)
			{
				printf("Es el elegido %d.\n",elegido);
				imprimir(Tablero);
			}
			else
			{
				printf("No es el elegido %d.\n",i);
				imprimir(aux);
			}
			i++;
		}
	
		return salir;
	}
}	
/*Genera el nombre del archivo en el cual buscar los tableros a partir de la dimension ingresada por el usuario*/
char * GenerarNombre(int dimension)
{
	char *nombre=NULL;
	nombre=malloc(sizeof(*nombre)*6);
	if(nombre==NULL)
	{
		printf("No hay memoria suficiente para generar el archivo.\n");
		return nombre;
	}
	
		sprintf(nombre,"%dx%d",dimension,dimension);
		printf("nombre del archivo=%s\n",nombre);
	return nombre;
}
/*Imprime el tablero por salida estandar*/
void imprimir(char** t)
{
	int i,j;
	
	
		for(i=0;i<2;i++)
		{
			printf("\t");
			for(j=0;j<_DIM;j++)
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
		for(i=0;i<_DIM;i++)
		{
				if(_DIM<10)
					printf("%d|\t",i);
				else
				{
					if(i<10)
						printf("%d |\t",i);
					else
						printf("%d|\t",i);
				}
			for(j=0;j<_DIM;j++)
			{
					printf("%c  ",t[i][j]);
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
	if(opcion==3)
	{	
		do
		{
			printf("Ingrese el nombre del archivo: ");
			scanf("%s", nombreArchivo);
			archivoCargado = CargarArchivo(nombreArchivo);
		} while(!archivoCargado)
		
	}return opcion;
}
int CargarArchivo(char NombreArch[])
{
	int i;
	FILE * archPartida;
	
	//Pregunta si existe el archivo, y en ese caso lo abre en modo lectura 
	//(por ser lazy, si no existe el archivo nunca lo abre), y corrobora que no haya errores
	if(!Existe(NombreArch) || (archPartida = fopen(NombreArch, "rb")) == NULL)
		return 0;
	
	
	//Lee los datos del archivo y carga las variables
	fread(&ModoJuego, sizeof(ModoJuego), 1, archPartida);
	fread(&ProximoTurno, sizeof(ProximoTurno), 1, archPartida);
	fread(&_DIM, sizeof(_DIM), 1, archPartida);
	
	Tablero = malloc(_DIM * sizeof(char*));
	
	for(i = 0; i < _DIM; i++)
	{	
		Tablero[i] = malloc(_DIM);
		fread(Tablero[i], _DIM, 1, archPartida);
	}
	
	//Cierra el archivo
	fclose(archPartida);
	
	return 1;
}

/*int main()
{
	srand(time(NULL));
	//printf("%d\n",LeerOpcion());
	//if(GenerarTablero()==0)
		//imprimir(t);
	GenerarTablero();
	return 0;
}*/
