#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "buttonsAndScissorsFront.h"
#define LIMPIABUFFER() while(getchar()!='\n')
//enum errorLeerTablero {NOEXISTE=1,FORMATO};
tablero t={NULL,5};
/* lee tableros de un archivo elije uno aleatoriamente y lo carga en el tablero del juego*/
int GenerarTablero(tablero* t)
{
	FILE* arch=NULL;
	char * nombre=GenerarNombre(t->dim);
	arch=fopen(nombre,"r");
	if(arch==NULL)
		return 1;
	else
	{
		int cant=0,i=0,j,k,salir=0,c,elegido;
		t->tab=malloc(sizeof(char*)*(t->dim));
		for(j=0;j<t->dim;j++)
		{	
			(t->tab)[j]=malloc(sizeof(char)*(t->dim));
		}
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

			for(j=0;j<t->dim&&(!salir);j++)
			{
				for(k=0;k<t->dim&&(!salir);k++)
				{
					c=fgetc(arch);
					if((isalpha(c)&&isupper(c))||c==' ')
					{
						if(i==elegido)
							(t->tab)[j][k]=c;
						
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
			for(j=0;j<t->dim;j++)
				free((t->tab)[j]);
			free(t->tab);
			//free(t);
		}

		return salir;
	}
	
}

void imprimirErrorTablero(int error)
{
	switch(error)
	{
		case 1:
						printf("El archivo solicitado no existe.\n");
						break;
		case 2: 
						printf("Error de Formato..\n");
						break;
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
	/*if(opcion==3)
		cargar();*/
	return opcion;
}
int main()
{
	srand(time(NULL));
	printf("%d\n",LeerOpcion());
	int error;
	if((error=GenerarTablero(&t))==0)
		imprimir(t);
	else
		imprimirErrorTablero(error);
	return 0;
}