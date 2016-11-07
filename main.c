#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "buttonsAndScissorsBack.h"
#include "buttonsAndScissorsFront.h"
int main()
{
	srand(time(NULL));
	tJuego juego;
	int opcion=Menu(),error;
	if(opcion==1||opcion==2)
    {
    	//printf("opcion=%d\n",opcion);
    	juego.modoJuego=opcion-1;
    	juego.tableroJuego.dim=5;
    	//juego.tableroJuego.dim=ElegirDIm();
    	if((error=GenerarTablero(&(juego.tableroJuego)))==0)
		  jugar(&juego);
        else
			imprimirErrorTablero(error);
        
    }
   /* else if(opcion==3)
    {
    	cargar();
    	jugar()
    }*/
	
	
	return 0;
}