#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>
#include "buttonsAndScissorsBack.h"
#include "buttonsAndScissorsFront.h"
#include "rand.h"
#define LIMPIABUFFER() while(getchar()!='\n')
#define MAX_LONG 256
#define MAX_NAME 48

void botonesyTijeras(void)
{
	tJuego juego;
	int opcion,error;
	do
	{
		opcion=Menu();
		if(opcion==1||opcion==2)
    	{
    		juego.modoJuego=opcion-1;
    		do
    		{
    			juego.proximoTurno=randInt(0,1);
	
    			ElegirDim(&(juego.tableroJuego));
    			if((error=GenerarTablero(&(juego.tableroJuego)))==0)
		  			jugar(&juego);
        		else
					imprimirErrorTablero(error);
			}while(error);
        
    	}
    	else if(opcion==3)
    	{
    		int resp;
    		do
    		{
    			juego.nombreArch=NULL;
				leerNombre(&juego);
				resp=CargarArchivo(&juego);
				free(juego.nombreArch);
			}while(resp==0);
			
    		jugar(&juego);
    	}
    }while(opcion!=4);
	
}

/* lee tableros de un archivo elije uno aleatoriamente y lo carga en el tablero del juego*/
int GenerarTablero(tablero* t)
{
	FILE* arch=NULL;
	t->tab=NULL;
	char * nombre=GenerarNombre(t->dim);
	arch=fopen(nombre,"r");
	free(nombre);
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
		elegido=randInt(0, cant-1);
		while(!feof(arch)&&(!salir))
		{
			if(i==elegido)
				//t->tab=malloc(sizeof(char*)*(t->dim));
				if(validarMemoria((void**)(&(t->tab)),sizeof(char*)*(t->dim)))
					return 3;
			for(j=0;j<t->dim&&(!salir);j++)
			{
				if(i==elegido)
				{	//(t->tab)[j]=malloc(sizeof(char)*(t->dim));
					(t->tab)[j]=NULL;
					if(validarMemoria((void**)((t->tab)+j),sizeof(char)*(t->dim)))
						return 3;
				}
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
				/*for(j=0;j<t->dim;j++)
					free((t->tab)[j]);
				free(t->tab);*/
				liberarTablero(t);
			}
		}
		fclose(arch);
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
						printf("Error de Formato.\n");
						break;
		case 3:
						errorMemoria();
						break;
	}
}	
	
/*Genera el nombre del archivo en el cual buscar los tableros a partir de la dimension ingresada por el usuario*/
char * GenerarNombre(int dimension)
{
	char *nombre=NULL;
	//nombre=malloc(sizeof(*nombre)*6);
	if(validarMemoria((void**)(&nombre),6))
		errorMemoria();
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
	int jugador1=1,jugador2=2,termino;
	juego->puntosJug1=0;
	juego->puntosJug2=0;

	do
	{
		printf("Botones J1: %d, J2:%d\n\n",juego->puntosJug1,juego->puntosJug2);
		imprimir(juego->tableroJuego);
		printf("Turno jugador %d\n",(juego->proximoTurno==0)?jugador1:jugador2);
		if((termino=hayGanador(juego->tableroJuego)))//por si empieza con tablero vacio
			printf("El ganador es el jugador %d!!!\n",(juego->proximoTurno==0)?jugador1:jugador2);
		else
		{
			if(juego->proximoTurno==1&&juego->modoJuego==1)
			{	if(jugarAi(&(juego->tableroJuego),&(juego->puntosJug2))==1)
				{
					errorMemoria();
				}
			}
			else if(juego->proximoTurno==1)
				termino=jugar2P(juego);
			else
				termino=jugar2P(juego);
			if(!termino)
			{
				if((termino=hayGanador(juego->tableroJuego)))//si no hay mas jugadas posibles o si quedo vacio el tablero
					printf("El ganador es el jugador %d!!!\n\n\n",(juego->proximoTurno==0)?jugador1:jugador2);
				else
					juego->proximoTurno=(juego->proximoTurno+1)%2;
			}
		}
	}while(!termino);
	liberarTablero(&(juego->tableroJuego));
}


void ElegirDim(tablero * t)
{
	char c;
	do
	{
		c=0;
		printf("Ingrese la dimensión del tablero (Mínima: 5 (5x5), Máxima: 30 (30x30)): ");
		scanf("%d%c", &(t->dim),&c);
		if(c!='\n')
			LIMPIABUFFER();
	}while(t->dim < 5 || t->dim > 30);
}




int jugar2P(tJuego* juego)
{
	int resp;
	do
	{
		resp=LeerComando(juego);
		
		if(resp==1||resp==3)//si es salir y guardar o guardar
		{
			if(Guardar(juego))
				printf("El archivo se guardo exitosamente.\n");
		}
		
	}while(resp==3);//si puso solo guardar
	return resp==1||resp==2;
}


int LeerComando(tJuego * juego)
{
	movimiento mov;
	char cmd[MAX_LONG];
	char name[MAX_NAME] = {0};
	int done = 0;
	int F1, C1, F2, C2,longitud;
	char aux;
	do
	{
		printf("Ingrese el comando: ");
		fgets(cmd, MAX_LONG, stdin);
		if(strcmp(cmd, "quit\n") == 0)
		{
			printf("¿Está seguro que quiere salir (Y/N)? ");
			fgets(cmd, MAX_LONG, stdin);
			if(strcmp(cmd, "Y\n") == 0)
			{
				printf("¿Desea guardar la partida antes de salir (Y/N)? ");
				fgets(cmd, MAX_LONG, stdin);
				if(strcmp(cmd, "Y\n") == 0)
				{
					
						printf("Ingrese el nombre del archivo: ");//falta validar nombre con espacio
						fgets(name, MAX_NAME, stdin);
						sscanf(name,"%s",name);
						if((longitud=strlen(name)) > 0 && name[0] != '\n') 
						{
								juego->nombreArch=NULL;
								if(validarMemoria((void**)(&(juego->nombreArch)),sizeof(char)*(longitud+1)))
									errorMemoria();
								//juego->nombreArch=malloc(sizeof(char)*(longitud+1));
								sprintf(juego->nombreArch,"%s",name);
								done = 1;
						}
						else printf("Debe ingresar un nombre válido de archivo.\n");
					
				}
				else if(strcmp(cmd, "N\n") == 0)
				{
					done = 2;
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
				if((longitud=strlen(name)) > 0) 
				{
					juego->nombreArch=NULL;
					if(validarMemoria((void**)(&(juego->nombreArch)),sizeof(char)*(longitud+1)))
						errorMemoria();
					//juego->nombreArch=malloc(sizeof(char)*(longitud+1));
					sprintf(juego->nombreArch,"%s",name);
					done = 3;
				}
				else printf("Debe ingresar un nombre válido de archivo.\n");
			}
			else if(sscanf(cmd, "[%d,%d][%d,%d]%c", &F1, &C1, &F2, &C2, &aux) == 5 && aux == '\n')
			{
				int error,puntos;
				int direccionCorte = -1;
				mov.inicio.fila = F1;
				mov.inicio.columna = C1;
				mov.final.fila = F2;
				mov.final.columna = C2;
				if((direccionCorte = JugadaValida(&(juego->tableroJuego), &mov, &error)) != -1) 
				{
					puntos=EfectuarCorte(juego->tableroJuego.tab, &mov);
					if(juego->proximoTurno==0)
						juego->puntosJug1+=puntos;
					else
						juego->puntosJug2+=puntos;

					done = 4;
				}
				else
				{
					switch(error)
					{
						case 1: /*ReportarErrorPosicion(mov.inicio);
							break;*/
						case 2: /*ReportarErrorPosicion(mov.final);
							break;*/
						case 3: /*ReportarErrorEspacioVacio(mov.final);
							break;*/
						case 4: /*ReportarErrorEspacioVacio(mov.inicio);
							break;*/
						case 5: /*ReportarErrorLineaRecta();
							break;*/
						case 6: /*ReportarErrorVariedades();
							break;*/
						printf("Error\n");
					}
				} 
			}
			else printf("Comando inválido.\n");
		}
	}
	while(done == 0);
	return done;
}

int Guardar(tJuego * juego)
{
	int i;
	int dim = juego -> tableroJuego.dim; //Guarda la dirección del tablero en una variable auxiliar
	(juego -> proximoTurno)++;
	//Crea el archivo con el nombre nombreArch
	FILE * archPartida;
    archPartida = fopen(juego->nombreArch, "wb");
	free(juego->nombreArch);
	

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
	(juego -> proximoTurno)--;
	
	return 1;
}

void leerNombre(tJuego* juego)
{
	char c;
	if(validarMemoria((void**)(&(juego->nombreArch)),sizeof(char)*MAX_NAME))
		errorMemoria();
	
	do
	{
		c=0;
		printf("Ingrese el nombre del archivo(sin espacios) que quiere cargar:\n");
		scanf("%s%c",juego->nombreArch,&c);
		if(c!='\n')
		{
			LIMPIABUFFER();
			printf("El nombre del archivo debe estar seguido por enter.\n");
		}
	}while(c!='\n');
	
}

/*Carga el archivo*/
int CargarArchivo(tJuego * juego)
{
	
	int i;
	FILE * archPartida;
	int dim = juego -> tableroJuego.dim; //Guarda la dirección del tablero en una variable auxiliar
	//Pregunta si existe el archivo, y en ese caso lo abre en modo lectura 
	//(por ser lazy, si no existe el archivo nunca lo abre), y corrobora que no haya errores
	if(!Existe(juego->nombreArch) || (archPartida = fopen(juego->nombreArch, "rb")) == NULL)
		return 0;
	
	//Lee los datos del archivo y carga las variables
	fread(&(juego -> modoJuego), sizeof(juego -> modoJuego), 1, archPartida);
	fread(&(juego -> proximoTurno), sizeof(juego -> proximoTurno), 1, archPartida);
	fread(&(juego -> tableroJuego.dim), sizeof(dim), 1, archPartida);
	
	juego -> tableroJuego.tab =NULL;
	if(validarMemoria((void**)&(juego->tableroJuego.tab),juego->tableroJuego.dim * sizeof(char*)))
		errorMemoria();
	for(i = 0; i < juego->tableroJuego.dim; i++)
	{	
		juego->tableroJuego.tab[i]=NULL;
		if(validarMemoria((void**)&(juego->tableroJuego.tab[i]),juego->tableroJuego.dim))
			errorMemoria();
		fread(juego -> tableroJuego.tab[i], juego->tableroJuego.dim, 1, archPartida);
	}
	(juego->proximoTurno)--;
	//Cierra el archivo
	fclose(archPartida);
	return 1;
}

int Existe(char *archivo)
{
	struct stat buffer;
	return (stat(archivo, &buffer) == 0);
}

void errorMemoria(void)
{
	printf("Error de memoria.\n");
	exit(0);
}
