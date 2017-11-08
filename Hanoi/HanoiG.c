/********************************************************************************
* PROGRAMA: Hanoi.c                                      						*
* AUTORES:    																	*
* - Oledo Enriquez Gilberto Irving                                    			*
* - Alanís Ramírez Damián                                               		*
* - Mendieta Torres Alfonso Ulises                                      		*
*                                       										*
* VERSIÓN: 1.0                                                         			*
*                                                                       		*
* DESCRIPCIÓN: Programa que sa solucion (recursiva) a las torres de hanoi		*												*
*              (METODO GRAFICO)      											*
* Compilación: cd (ruta_archivos)                                       		*
* gcc -o HanoiG HanoiG.c presentacionWin.c										*
*********************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h> 
#include <windows.h>
#include <math.h>
#include "presentacion.h"  

// Prototipo de funciones
void hidecursor(void);
void imprime( int *tab, int fil, int col, int ultNum );
void mueveDisco( int *tab, int fil, int col, int ultNum, int filOrig, int filDest );
void hanoi( int *tab, int fil, int col, int disc, int ultNum, int O, int A, int D );

//Inicio de programa principal (Main)
int main()
{
int movimientostotales;
hidecursor(); //Se elimina el cursor
system("cls"); //Se limpia la pantalla antes de comenzar
	int fil=3, col, *tablero = NULL;
	int f, c, disc=1, ultNum;
	MoverCursor(60,2); printf ("***************************************\n");
    MoverCursor(63,4); printf ("Instituto Politecnico Nacional\n");
    MoverCursor(63,5); printf ("Escuela Superior de Computo\n");
    MoverCursor(63,6); printf ("Estructuras de Datos: Hanoi\n");
    MoverCursor(60,8); printf ("***************************************\n\n");

	printf( "Indique el numero de discos: " );
	scanf( "%i", &col );

	/*(*Tablero) Array de números enteros declarado en tiempo de ejecución para así poder reservar la memoria 
	necesaria para almacenar el estado de las tres torres.
	Las torres se representan en el array de forma horizontal, por ello el array tiene 3 filas 
	y n columnas.*/
	tablero = (int *)malloc( sizeof(int)*fil*col ); 
	

	// Resetea las torres poniendo "los discos" en una de ellas (torre origen) y 0 en el resto (torre auxiliar y torre destino).
	for( f=0; f < fil; f++ )
		for( c=col-1; c >= 0; c-- )
			if( f==0 )
			{
				tablero[col*f+c] = disc;
				disc+=2;
			}
			else
				tablero[col*f+c] = 0;

	ultNum = disc;

	// Se imprime el tablero antes de iniciar con algun movimiento movimiento:
	system("cls"); //Se limpia la pantalla y se imprime el tablero
	imprime( tablero, fil, col, ultNum );
	Sleep (2000); // El programa "duerme" 1000ml antes de comenzar los movimientos 


	// Se llama a hanoi para comenzar "la partida":
	hanoi( tablero, fil, col, col, ultNum, 0, 1, 2 );
 	movimientostotales = ((pow (2, col))-1);
	MoverCursor(60,16+col); printf ("Se realizaron: %d movimientos\n\n",movimientostotales);
};
//Funcion utilizada para no hacer visible el cursor y poder apresiar el movimiento de los discos
void hidecursor(void){
 HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
  }

 //Declaracion de funciones


/* Nombre de la funcion: imprime
Descripción: Funcion que dibuja las torres (Origen, auxiliar, destino) asi mismo dibuja los discos los cuales son representados
con figuras (ASCII)
Recibe:
					*tab	Puntero a una matriz de tipo entero.
					fil		Entero que indica el numero de filas de la matriz.
					col		Entero que indica el numero de columnas de la matriz.
					disc	Parámetro de tipo entero que indica el numero de discos usados.
					ultNum	Entero que indica el numero que esta usando el disco mas grande.
Devuelve: El dibujo de las torres y los discos */
void imprime( int *tab, int fil, int col, int ultNum )

{

system("cls"); //Se limpia la pantalla antes de comenzar
	MoverCursor(60,2); printf ("***************************************\n");
    MoverCursor(63,4); printf ("Instituto Politecnico Nacional\n");
    MoverCursor(63,5); printf ("Escuela Superior de Computo\n");
    MoverCursor(63,6); printf ("Estructuras de Datos: Hanoi\n");
    MoverCursor(60,8); printf ("***************************************\n\n");
   
MoverCursor(75,11); printf ("%cComenzamos%c\n\n",173,33);

	int f, c;
	int i,j, esp;


	for( c=col-1; c >= 0; c-- )
	{
		for( f=0; f < fil; f++ )
		{
			esp = ( ultNum - tab[col*f+c] )/2; //Indica la posicion respecto al eje x donde debera colocarse el disco
											  //El disco se coloca de forma "centrada"

			// Espacios a la izquierda para colocar el disco de forma "centrada"
			for( i=0; i < esp; i++ )
				printf( " " );

			// Imprime los discos de forma "centrada"
			for( i=0; i < tab[col*f+c]; i++ )
				printf( "%c",61);

			// Espacios a la derecha para colocar el disco de forma "centrada"
			for( i=0; i < esp; i++ )
				printf( " " );

			printf( "\t" );
		};

		printf( "\n" );

	};
};

/* Nombre de la funcion: mueveDisco
Descripción: Funcion que mueve los discos a una posicion valida
Recibe:
					*tab	Puntero a una matriz de tipo entero.
					fil		Entero que indica el numero de filas de la matriz.
					col		Entero que indica el numero de columnas de la matriz.
					disc	Parámetro de tipo entero que indica el numero de discos usados.
					ultNum	Entero que indica el numero que esta usando el disco mas grande.
					filOrig	Entero que indica el numero de fila de la matriz en la cual hay que coger el numero/disco
					filDest	Entero que indica el numero de fila de la matriz en la cual hay que dejar el numero/disco.
Devuelve: El disco en una posicion valida y se llama a la función que imprime el tablero. */
void mueveDisco( int *tab, int fil, int col, int ultNum, int filOrig, int filDest )
{
	
	int cO=col-1, cD=col-1;


	// Se busca el disco que se encuentre mas arriba y por lo tanto el mas pequeño de la fila de origen.
	while( cO >= 0  &&  tab[col*filOrig+cO] == 0 )
	{
		cO--;
	};
	if( cO < 0 )
		cO = 0;

	// Ahora se calcula cual es la posición libre mas arriba de la fila de destino
	while( cD >= 0  &&  tab[col*filDest+cD] == 0 )
	{
		cD--;
	};

	// Se mueve el disco de la fila de origen a la de destino:
	tab[col*filDest+cD+1] = tab[col*filOrig+cO];
	tab[col*filOrig+cO] = 0;

	// Se imprime el tablero:
	imprime( tab, fil, col, ultNum );
};

/* Nombre de la funcion: hanoi
Descripción: Funcion recursiva que da solucion las torres hanoi
Recibe:
					*tab	Puntero a una matriz de tipo entero.
				fil		Entero que indica el numero de filas de la matriz.
				col		Entero que indica el numero de columnas de la matriz.
				disc	Parámetro de tipo entero que indica el numero de discos usados.
				ultNum	Entero que indica el numero que esta usando el disco mas grande.
				O,A,D	Tres enteros que indican la fila desde donde se ha de coger el disco y a donde se ha de traspasar. 
				La primera vez que se llama a hanoi tienen los valores de: 0 ,1 y 2 respectivamente.
Devuelve: La solucion a las torres de hanoi dado un numero n de discos*/

void hanoi( int *tab, int fil, int col, int disc, int ultNum, int O, int A, int D )
{
	//FUNCION RECURSIVA Se llama recursivamente a hanoi hasta resolver el tablero.

	if( disc==1 ) //Caso base - mover 1 disco de origen a destino
	{
		
		// Se borra la pantalla, se imprime la tabla y se hace una pausa que varia dependiendo del numero de discos:
		system("cls");
		mueveDisco( tab, fil, col, ultNum, O, D );
		if(col<=5) Sleep (700); else if(col<=10) Sleep (800);  else if(col<=15) Sleep (900);  else if(col>15) Sleep (1000);
	}
	else
	{
	
		hanoi( tab, fil, col, disc-1, ultNum, O, D, A ); //Mover n-1 discos

		system("cls");
		mueveDisco( tab, fil, col, ultNum, O, D );
		if(col<=5) Sleep (700); else if(col<=10) Sleep (800); else if(col<=15) Sleep (900); else if(col>15) Sleep (1000);

		hanoi( tab, fil, col, disc-1, ultNum, A, O, D );
	};

};


