//erikams79@gmail.com
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#include "nodo.h"
#include "buscador.h"


int main(int argc, char *argv[])
{
	//Se le envía el archivo .txt por parámetros
        calcularFilasyColumnas(argv[1]);

        laberinto = malloc( filas * columnas * sizeof(struct nodo )); 
        
        llenar_laberinto(laberinto);

        //Inicia los movimientos
        struct nodo *nodoDerecha;
        nodoDerecha = laberinto[1 * columnas];
        struct nodo *nodoAbajo;
        nodoAbajo = laberinto[1];
        int derecha = nodoDerecha->casilla;
        int abajo = nodoAbajo->casilla;

        struct parametros parametroDe;//  = malloc(sizeof(struct parametros));
        parametroDe.filas = filas;
        parametroDe.columnas = columnas;

        struct parametros parametroAb;//  = malloc(sizeof(struct parametros));
        parametroAb.filas = filas;
        parametroAb.columnas = columnas;  
        
        if (derecha == 0)
        {
            laberinto[0]->derecha = 1;
            parametroDe.i = 0;
            parametroDe.j = 1;
            parametroDe.paso_casillas = 1;
            pthread_create(&moverseDerecha_t, NULL, moverseDerecha, ( void *)&parametroDe);            
        }
        if (abajo == 0)
        {
            laberinto[0]->abajo = 1;
            parametroAb.i = 1;
            parametroAb.j = 0;
            parametroAb.paso_casillas = 1;
            pthread_create(&moverseAbajo_t, NULL, moverseAbajo, ( void *)&parametroAb);
        }
        if (derecha == 0)
        {
            pthread_join(moverseDerecha_t, NULL);    
        }
        if (abajo == 0)
        {         
            pthread_join(moverseAbajo_t, NULL);
        }  
        return 0;
}
