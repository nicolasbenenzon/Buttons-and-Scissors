#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "buttonsAndScissorsBack.h"
#include "buttonsAndScissorsFront.h"
#include "FrontTestSuite.h"



void lecturaTableroInicialTest(CuTest * cuTest)
{
	/*actual representa la dimension del tablero que va a leer
	** si devuelve 0 no hubo error, 1 si no existe el archivo y 2 si hay un error de formato
	*/
	tablero t;
	t.dim= 5;
	int actual = GenerarTablero(&t);
	int esperado = 0;
	CuAssertIntEquals_Msg(cuTest,"El archivo era correcto y encontro error.\n", esperado, actual);
	t.dim= 6;
	actual = GenerarTablero(&t); 
	esperado = 2;
	CuAssertIntEquals_Msg(cuTest,"Deberia haber devuelto error de formato.\n", esperado, actual);
	t.dim= 7;
	actual = GenerarTablero(&t);
	esperado = 1;
	CuAssertIntEquals_Msg(cuTest,"Deberia haber devuelto que no existe el archivo.\n", esperado, actual);
	t.dim= 10;
	actual = GenerarTablero(&t);
	esperado = 1;
	CuAssertIntEquals_Msg(cuTest,"Deberia haber devuelto que no existe el archivo.\n", esperado, actual);
	t.dim= 15;
	actual = GenerarTablero(&t);
	esperado = 0;
	CuAssertIntEquals_Msg(cuTest,"El archivo era correcto y encontro error.\n", esperado, actual);
	
}


void CargarArchivoTest(CuTest * cuTest) 
{
	tJuego juego;
	juego.nombreArch = "PartidoXXX";
	int actual = CargarArchivo(&juego);
	int esperado = 0;
	char * mensaje = "Los valores de respuesta no coinciden";
	CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);

	juego.nombreArch = "TestPartidaGuardada";
	actual = CargarArchivo(&juego);
	esperado = 1;
	mensaje = "Los valores de respuesta no coinciden";
	CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);

}


void GuardarTest(CuTest * cuTest) 
{
	tJuego juego;
	juego.tableroJuego.tab = malloc(5 * sizeof(char*));
	for(int i = 0; i < 5; i++)
	{
		juego.tableroJuego.tab[i] = malloc(5);
	}
	juego.tableroJuego.tab[0][0] = '0'; juego.tableroJuego.tab[0][1] = 'A'; juego.tableroJuego.tab[0][2] = '0'; juego.tableroJuego.tab[0][3] = '0'; juego.tableroJuego.tab[0][4] = '0';
	juego.tableroJuego.tab[1][0] = '0'; juego.tableroJuego.tab[1][1] = '0'; juego.tableroJuego.tab[1][2] = '0'; juego.tableroJuego.tab[1][3] = 'B'; juego.tableroJuego.tab[1][4] = 'D';
	juego.tableroJuego.tab[2][0] = '0'; juego.tableroJuego.tab[2][1] = '0'; juego.tableroJuego.tab[2][2] = 'B'; juego.tableroJuego.tab[2][3] = '0'; juego.tableroJuego.tab[2][4] = '0';
	juego.tableroJuego.tab[3][0] = '0'; juego.tableroJuego.tab[3][1] = 'C'; juego.tableroJuego.tab[3][2] = 'D'; juego.tableroJuego.tab[3][3] = 'C'; juego.tableroJuego.tab[3][4] = 'A';
	juego.tableroJuego.tab[4][4] = 'B'; juego.tableroJuego.tab[4][1] = '0'; juego.tableroJuego.tab[4][2] = '0'; juego.tableroJuego.tab[4][3] = '0'; juego.tableroJuego.tab[4][4] = '0';
	
	juego.tableroJuego.dim = 5;
	juego.nombreArch=malloc(9*sizeof(char));
	sprintf(juego.nombreArch, "Partido1");
	juego.modoJuego = 1;
	juego.proximoTurno = 1;

	int actual = Guardar(&juego);
	int esperado = 1;
	char * mensaje = "Los valores de respuesta no coinciden";
	CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
}



CuSuite * FrontTestSuite()
{
	CuSuite * cuSuite = CuSuiteNew();
	SUITE_ADD_TEST(cuSuite, lecturaTableroInicialTest);
	SUITE_ADD_TEST(cuSuite, CargarArchivoTest);
	SUITE_ADD_TEST(cuSuite, GuardarTest);
	return cuSuite;
}
