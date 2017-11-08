/********************************************************************************
* PROGRAMA: Hanoi.c                                                             *
* AUTORES:                                                                      *
* - Oledo Enriquez Gilberto Irving                                              *
* - Alanís Ramírez Damián                                                       *
* - Mendieta Torres Alfonso Ulises                                              *
*                                                                               *
* VERSIÓN: 1.0                                                                  *
*                                                                               *
* DESCRIPCIÓN: Programa que sa solucion (recursiva) a las torres de hanoi       *                  
*              (METODO NO GRAFICO)                                              *
* Compilación: cd (ruta_archivos)                                               *
* gcc -o Hanoi Hanoi.c presentacionWin.c                                        *
*********************************************************************************/


#include <stdio.h>
#include <windows.h>
#include <math.h>
#include "presentacion.h"  
//Prototipo de funciones 
void hanoi(int n,int origen, int auxiliar, int destino);

//Inicio de programa principal
void main(void){
    system("cls"); //Se limpia la pantalla antes de comenzar

//Se declaran las 3 torres y se les asigna un numero entero que las identifica
int origen =1, auxiliar =2, destino= 3;
int movimientostotales;
int n;
    MoverCursor(60,2); printf ("***************************************\n");
    MoverCursor(63,4); printf ("Instituto Politecnico Nacional\n");
    MoverCursor(63,5); printf ("Escuela Superior de Computo\n");
    MoverCursor(63,6); printf ("Estructuras de Datos: Hanoi\n");
    MoverCursor(60,8); printf ("***************************************\n\n");
printf("Ingrese el numero de discos: ");
scanf("%d",&n);
fflush(stdin);

printf("\n\nLos movimientos a realizar son: \n\n");
hanoi(n,origen,auxiliar,destino); //Se llama a la funcion hanoi
movimientostotales = ((pow (2, n))-1);
printf ("\n\nNumero total de movimientos realizados: %d \n\n\n\n",movimientostotales);
}

/* Nombre de la funcion: hanoi
    Descripción: Funcion  que da solcion al problema torres de hanoi (solucion recursiva)
Recibe:
                    int n - numero de discos
                    int origen - entero que identifica a la torre de origen 
                    int auxiliar - entero que identifica a la torre de auxiliar 
                    int destino - entero que identifica a la torre de destino
Devuelve: La solucion a al problema torres de hanoi */
void hanoi(int n,int origen, int auxiliar, int destino){

if(n==1){ //Caso base, si numero de discos es igual a 1 entonces mover el disco de la torre origen a la torre destino
printf("Mover disco de la torre %d a la torre %d",origen,destino);
}
else{
hanoi(n-1,origen,destino,auxiliar); //Recursividad (Se llama a la funcion hanoi pero ahora con n-1 discos)
printf("\nMover disco de la torre %d a la torre %d\n",origen,destino); //Instrucciones para el usuario
hanoi(n-1,auxiliar,origen,destino);
}
}