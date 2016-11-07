#include <stdio.h>
#include "buttonsAndScissorsFront.h"
#include "CuTest.h"

/*void strLenTest(CuTest * cuTest);

CuSuite * 
strTestSuite(void) 
{
	CuSuite * cuSuite = CuSuiteNew();
	SUITE_ADD_TEST(cuSuite, strLenTest);
	return cuSuite;
}

void 
strLenTest(CuTest * cuTest) 
{
	char * entrada = "Hola Mundo!";
	int actual = strlen(entrada);
	int esperado = 10;
	char * mensaje = "Los valores de las longitudes no coinciden";
	CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
}*/
void CargarArchivoTest(CuTest * cuTest);
void GuardarTest(CuTest * cuTest);

CuSuite * 
FrontTestSuite(void) 
{
	CuSuite * cuSuite = CuSuiteNew();
	SUITE_ADD_TEST(cuSuite, CargarArchivoTest);
	SUITE_ADD_TEST(cuSuite, GuardarTest);
	return cuSuite;
}

void 
CargarArchivoTest(CuTest * cuTest) 
{
	char * nombreArchivo = "PartidoXXX";
	tJuego juego;
	int actual = CargarArchivo(nombreArchivo, &juego);
	int esperado = 0;
	char * mensaje = "Los valores de respuesta no coinciden";
	CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
}

void 
GuardarTest(CuTest * cuTest) 
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
	juego.nombreArch = "Partido1";
	juego.modoJuego = 1;
	juego.proximoTurno = 1;

	int actual = Guardar(&juego);
	int esperado = 1;
	char * mensaje = "Los valores de respuesta no coinciden";
	CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
}
