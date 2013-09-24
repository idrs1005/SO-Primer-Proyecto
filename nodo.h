#include <stdio.h>

/********************************/
/* DECLARACION DE LAS FUNCIONES */
/********************************/



/** 
    Estructura del nodo la matriz
**/
struct nodo 
{
    // 0 = camino, 1 = pared, 2 = salida
    int x;
    int y;
    int casilla;
    int arriba;
    int abajo;
    int derecha;
    int izquierda;
};

/** 
    Estructura del nodo la matriz
**/
struct parametros 
{
    int i;
    int j;
    int filas;
    int columnas;
    int paso_casillas;
};

/***********************************/
/* IMPLEMENTACION DE LAS FUNCIONES */
/***********************************/
