#include <stdio.h>

int main(void)
{
	int opcion=menu();
	switch(opcion)
	{
		case 1:case 2:
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
}