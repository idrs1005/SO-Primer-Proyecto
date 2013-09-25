
/******************************/
/*	DECLARACION DE FUNCIONES  */
/******************************/

void movimiento_de_arriba(int derecha, int izquierda, int i, int j, struct parametros *p);
void movimiento_de_abajo(int derecha, int izquierda, int i, int j, struct parametros *p);
void movimiento_de_izquierda(int arriba, int abajo, int i, int j, struct parametros *p);
void movimiento_de_derecha(int arriba, int abajo, int i, int j, struct parametros *p);

int revisarArriba(int i, int j, int filas, int columnas);
int revisarAbajo(int i, int j, int filas, int columnas);
int revisarIzquierda(int i, int j, int filas, int columnas);
int revisarDerecha(int i, int j, int filas, int columnas);

void *moverseArriba(void *parametros);
void *moverseAbajo(void *parametros);
void *moverseIzquierda(void *parametros);
void *moverseDerecha(void *parametros);

void calcularFilasyColumnas(char *archivo);
void llenar_laberinto(struct nodo **laberinto);


/******************************/
/*	DECLARACION DE VARIABLES  */
/******************************/

int filas = 1;
int columnas = 1;
int semaforo = 1;
struct nodo **laberinto;
pthread_t moverseAbajo_t;
pthread_t moverseDerecha_t;

/*********************************/
/*	IMPLEMENTACION DE FUNCIONES  */
/*********************************/


void imprimirlaberinto()
{
    int i, j;
    while(1)
    {
      if (semaforo)
      {
          semaforo = 0;
          for (i = 0; i < 4; i++)
          {
              for (j = 0; j < 4; j++)
              {
                  printf("%d,%d,%d,%d    ", laberinto[i + j *4]->arriba, laberinto[i + j *4]->abajo,
                          laberinto[i + j *4]->izquierda, laberinto[i + j *4]->derecha);
              }
              printf("\n");
          }
          printf("\n");
      }
      break;
    }
    semaforo = 1; 
}

void *moverseArriba(void *parametros)
{
    struct parametros *p;    
    p = (struct parametros *) parametros ;
    int cantidad_de_movimientos = p->paso_casillas;
    int i = p->i;
    int j = p->j;
    int filas = p->filas;
    int columnas = p->columnas;
    if (laberinto[i + j * columnas]->casilla == 2)
    {
        laberinto[i + j * columnas]->arriba = 1;
        cantidad_de_movimientos++;
        printf("El hilo llego, la cantidad de movimientos fueron %d\n", cantidad_de_movimientos);
        imprimirlaberinto();
        pthread_exit(0); 
    }
    for (i; i >= 0; i--)
    {
          cantidad_de_movimientos++;
          while(1)
          {
              if (semaforo)
              {
                  semaforo = 0;
                  laberinto[i + j * columnas]->arriba = 1;
                  break;
              }
              sleep(0.5);               
          }
          semaforo = 1;
          imprimirlaberinto();                
          int arriba = revisarArriba(i , j ,filas, columnas);
          int derecha = revisarDerecha(i , j ,filas, columnas);
          int izquierda = revisarIzquierda(i , j ,filas, columnas);
          printf("Arriba = %d, derecha = %d, izquierda = %d\n\n", arriba, derecha, izquierda);
          sleep(5);
          p->paso_casillas = cantidad_de_movimientos;
          movimiento_de_arriba(derecha, izquierda, i, j, p);                  
          if (arriba == 2)
          {
              //LLEGO AL DESTINO
              laberinto[(i-1) + j * columnas]->arriba = 1;
              pthread_exit(0); 
          }
          else if (arriba == 1)
          {
              //continua haca arriba
              continue;
          }
          else
          {
              printf("El hilo termino en (%d,%d), la cantidad de movimientos fueron %d\n",laberinto[i + j * columnas]->x,
              		 laberinto[i + j * columnas]->y, cantidad_de_movimientos);
              pthread_exit(0);
          }
          
    }
    pthread_exit(0);
}

void *moverseAbajo(void *parametros)
{
    struct parametros *p;    
    p = (struct parametros *) parametros;
    int cantidad_de_movimientos = p->paso_casillas;
    int i = p->i;
    int j = p->j;
    int filas = p->filas;
    int columnas = p->columnas;
    if (laberinto[i + j * columnas]->casilla == 2)
    {
        laberinto[i + j * columnas]->abajo = 1;
        cantidad_de_movimientos++;
        printf("El hilo llego, la cantidad de movimientos fueron %d\n", cantidad_de_movimientos);
        imprimirlaberinto();
        pthread_exit(0); 
    }
    for (i; i < filas; i++)
    {
          cantidad_de_movimientos++;
          while(1)
          {
              if (semaforo)
              {
                  semaforo = 0;
                  laberinto[i + j * columnas]->abajo = 1;
                  break; 
              }
              sleep(0.5);               
          }
          semaforo = 1;
          imprimirlaberinto();
          int abajo = revisarAbajo(i , j ,filas, columnas);
          int derecha = revisarDerecha(i , j ,filas, columnas);
          int izquierda = revisarIzquierda(i , j ,filas, columnas);
          printf("Abajo = %d, derecha = %d, izquierda = %d\n\n", abajo, derecha, izquierda);
          sleep(5);
          p->paso_casillas = cantidad_de_movimientos;
          movimiento_de_abajo(derecha, izquierda, i, j, p);
          if (abajo == 2)
          {
              //LLEGO AL DESTINO
              laberinto[(i+1) + j * columnas]->abajo = 1; 
              pthread_exit(0); 
          }
          else if (abajo == 1)
          {
              //continua hacia abajo
              continue;
          }
          else
          {
              //no puede continuar, termina
              printf("El hilo termino en (%d,%d), la cantidad de movimientos fueron %d\n",laberinto[i + j * columnas]->x,
              		 laberinto[i + j * columnas]->y, cantidad_de_movimientos);
              pthread_exit(0);
          }
          
    }
    pthread_exit(0);
}

void *moverseIzquierda(void *parametros)
{
    struct parametros *p;    
    p = (struct parametros *) parametros;
    int cantidad_de_movimientos = p->paso_casillas;
    int i = p->i;
    int j = p->j;
    int filas = p->filas;
    int columnas = p->columnas;
    if (laberinto[i + j * columnas]->casilla == 2)
    {
        laberinto[i + j * columnas]->izquierda = 1;
        cantidad_de_movimientos++;
        printf("El hilo llego, la cantidad de movimientos fueron %d\n", cantidad_de_movimientos);
        imprimirlaberinto();
        pthread_exit(0); 
    }
    for (j; j >= 0; j--)
    {
          cantidad_de_movimientos++;
          while(1)
          {
              if (semaforo)
              {
                  semaforo = 0;
                  laberinto[i + j * columnas]->izquierda = 1;
                  break;
              }
              sleep(0.5);               
          }
          semaforo = 1;
          imprimirlaberinto();         
          int izquierda = revisarIzquierda(i , j ,filas, columnas);
          int arriba = revisarArriba(i , j ,filas, columnas);
          int abajo = revisarAbajo(i , j ,filas, columnas);
          printf("Izquierda = %d, arriba = %d, abajo = %d\n\n", izquierda, arriba, abajo);
          sleep(5);
          p->paso_casillas = cantidad_de_movimientos;
          movimiento_de_izquierda(arriba, abajo, i, j, p);
          if (izquierda == 2)
          {
              //LLEGO AL DESTINO
              laberinto[i + (j-1) * columnas]->izquierda = 1;
              pthread_exit(0); 
          }
          else if (izquierda == 1)
          {
              //continua hacia la izquierda
              continue;
          }
          else
          {
              //no puede continuar, termina
              printf("El hilo termino en (%d,%d), la cantidad de movimientos fueron %d\n",laberinto[i + j * columnas]->x,
              		 laberinto[i + j * columnas]->y, cantidad_de_movimientos);
              pthread_exit(0);
          }
    }
    pthread_exit(0);
}

void *moverseDerecha(void *parametros)
{
    struct parametros *p;    
    p = (struct parametros *) parametros;
    int cantidad_de_movimientos = p->paso_casillas;
    int i = p->i;
    int j = p->j;
    int filas = p->filas;
    int columnas = p->columnas;
    if (laberinto[i + j * columnas]->casilla == 2)
    {
        laberinto[i + j * columnas]->derecha = 1;
        cantidad_de_movimientos++;
        printf("El hilo llego, la cantidad de movimientos fueron %d\n", cantidad_de_movimientos);
        imprimirlaberinto();
        pthread_exit(0); 
    }
    for (j; j < columnas; j++)
    {
          cantidad_de_movimientos++;
          while(1)
          {
              if (semaforo)
              {
                  semaforo = 0;
                  laberinto[i + j * columnas]->derecha = 1;
                  break;
              }
              sleep(0.5);               
          }
          semaforo = 1;
          imprimirlaberinto();          
          int derecha = revisarDerecha(i , j ,filas, columnas);
          int arriba = revisarArriba(i , j ,filas, columnas);
          int abajo = revisarAbajo(i , j ,filas, columnas);
          printf("Derecha = %d, arriba = %d, abajo = %d\n\n", derecha, arriba, abajo);
          sleep(5);
          p->paso_casillas = cantidad_de_movimientos;
          movimiento_de_derecha(arriba, abajo, i, j, p);
          if (derecha == 2)
          {
              //LLEGO AL DESTINO
              laberinto[i + (j+1) * columnas]->derecha = 1;
              pthread_exit(0); 
          }
          else if (derecha == 1)
          {
              //continua hacia la izquierda
              continue;
          }
          else
          {
              //no puede continuar, termina
              printf("El hilo termino en (%d,%d), la cantidad de movimientos fueron %d\n",laberinto[i + j * columnas]->x,
              		 laberinto[i + j * columnas]->y, cantidad_de_movimientos);
              pthread_exit(0);
          }
    }
    pthread_exit(0);
}

void movimiento_de_arriba(int derecha, int izquierda, int i, int j, struct parametros *p)
{
    pthread_t thread_derecha;
    pthread_t thread_izquierda;    
    struct parametros parametroDe;
    parametroDe.filas = p->filas;
    parametroDe.columnas = p->columnas;
    parametroDe.paso_casillas = p->paso_casillas;

    struct parametros parametroIz;//  = malloc(sizeof(struct parametros));
    parametroIz.filas = p->filas;
    parametroIz.columnas = p->columnas;
    parametroIz.paso_casillas = p->paso_casillas;

    if (derecha == 1)
    {
        parametroDe.i = i;
        parametroDe.j = j+1;
        pthread_create(&thread_derecha, NULL, moverseDerecha, ( void *)&parametroDe);
    }
    if (izquierda == 1)
    {
        parametroIz.i = i;
        parametroIz.j = j-1;
        pthread_create(&thread_izquierda, NULL, moverseIzquierda, ( void *)&parametroIz);
    }
    if (derecha == 1)
    {      
        pthread_join(thread_derecha, NULL);
    }
    if (izquierda == 1)
    {    
        pthread_join(thread_izquierda, NULL);
    }
}

void movimiento_de_abajo(int derecha, int izquierda, int i, int j, struct parametros *p)
{
    pthread_t thread_derecha;
    pthread_t thread_izquierda;

    struct parametros parametroDe;    
    parametroDe.filas = p->filas;
    parametroDe.columnas = p->columnas;
    parametroDe.paso_casillas = p->paso_casillas;

    struct parametros parametroIz;
    parametroIz.filas = p->filas;
    parametroIz.columnas = p->columnas;
    parametroIz.paso_casillas = p->paso_casillas;

    if (derecha == 1)
    {
        parametroDe.i = i;
        parametroDe.j = j+1;
        pthread_create(&thread_derecha, NULL, moverseDerecha, ( void *)&parametroDe);        
    }
    if (izquierda == 1)
    {
        parametroIz.i = i;
        parametroIz.j = j-1;
        pthread_create(&thread_izquierda, NULL, moverseIzquierda, ( void *)&parametroIz);       
    }
    if (derecha == 1)
    {
        pthread_join(thread_derecha, NULL);
    }
    if (izquierda == 1)
    {
        pthread_join(thread_izquierda, NULL);
    }
}

void movimiento_de_izquierda(int arriba, int abajo, int i, int j, struct parametros *p)
{
    pthread_t thread_arriba;
    pthread_t thread_abajo;
    
    struct parametros parametroAr;
    parametroAr.filas = p->filas;
    parametroAr.columnas = p->columnas;
    parametroAr.paso_casillas = p->paso_casillas;

    struct parametros parametroAb;
    parametroAb.filas = p->filas;
    parametroAb.columnas = p->columnas;
    parametroAb.paso_casillas = p->paso_casillas;

    if (arriba == 1)
    {
        parametroAr.i = i-1;
        parametroAr.j = j;
        pthread_create(&thread_arriba, NULL, moverseArriba, ( void *)&parametroAr);
    }
    if (abajo == 1)
    {
        parametroAb.i = i+1;
        parametroAb.j = j;
        pthread_create(&thread_abajo, NULL, moverseAbajo, ( void *)&parametroAb);    
    }
    if (arriba == 1)
    {      
        pthread_join(thread_arriba, NULL);
    }
    if (abajo == 1)
    {    
        pthread_join(thread_abajo, NULL);
    }
}

void movimiento_de_derecha(int arriba, int abajo, int i, int j, struct parametros *p)
{
    pthread_t thread_arriba;
    pthread_t thread_abajo;
    
    struct parametros parametroAr;
    parametroAr.filas = p->filas;
    parametroAr.columnas = p->columnas;
    parametroAr.paso_casillas = p->paso_casillas;

    struct parametros parametroAb;
    parametroAb.filas = p->filas;
    parametroAb.columnas = p->columnas;
    parametroAb.paso_casillas = p->paso_casillas;

    if (arriba == 1)
    {
        parametroAr.i = i-1;
        parametroAr.j = j;
        pthread_create(&thread_arriba, NULL, moverseArriba, ( void *)&parametroAr);
    }
    if (abajo == 1)
    {
        parametroAb.i = i+1;
        parametroAb.j = j;
        pthread_create(&thread_abajo, NULL, moverseAbajo, ( void *)&parametroAb);
    }
    if (arriba == 1)
    {       
        pthread_join(thread_arriba, NULL);
    }
    if (abajo == 1)
    {         
        pthread_join(thread_abajo, NULL);
    }
}

int revisarArriba(int i, int j, int filas, int columnas)
{
    int casillaArribai = i - 1;
    int casillaArribaj = j;
    if (casillaArribai >= 0 && casillaArribai < filas)
    {
        int info;
        int casilla;
        while(1)
        {
            if (semaforo)
            {
                semaforo = 0;
                info = laberinto[casillaArribai + casillaArribaj * columnas]->arriba;
                casilla = laberinto[casillaArribai + casillaArribaj * columnas]->casilla;
                break;
            }
            sleep(0.5);               
        }
        semaforo = 1; 
        
        //Si es = 1 ya se paso en esta direccion
        if (info == 1 || casilla == 1)
        {
            //invalida para seguir
            return -1;
        }
        else if(info == 2)
        {
            return 2;
        }
        else
        {
            //valido para seguir en esta direccion
            return 1;
        }
    }
    else
    {
        //casilla fuera del mapa
        return -1;
    }
}

int revisarAbajo(int i, int j, int filas, int columnas)
{
    int casillaAbajoi = i + 1;
    int casillaAbajoj = j;
    if (casillaAbajoi >= 0 && casillaAbajoi < filas)
    {
        int info;
        int casilla;
        while(1)
        {
            if (semaforo)
            {
                semaforo = 0;
                info = laberinto[casillaAbajoi + casillaAbajoj * columnas]->abajo;
                casilla = laberinto[casillaAbajoi + casillaAbajoj * columnas]->casilla;
                break;
            }
            sleep(0.5);               
        }
        semaforo = 1; 
        //Si es = 1 ya se paso en esta direccion
        if (info == 1 || casilla == 1)
        {
            //invalida para seguir
            return -1;
        }
        else if(info == 2)
        {
            return 2;
        }
        else
        {
            //valido para seguir en esta direccion
            return 1;
        }
    }
    else
    {
        //casilla fuera del mapa
        return -1;
    }
}

int revisarIzquierda(int i, int j, int filas, int columnas)
{
    int casillaIzquierdai = i;
    int casillaIzquierdaj = j - 1;
    if (casillaIzquierdaj >= 0 && casillaIzquierdaj < columnas)
    {
        int info;
        int casilla;
        while(1)
        {
            if (semaforo)
            {
                semaforo = 0;
                info = laberinto[casillaIzquierdai + casillaIzquierdaj * columnas]->izquierda;
                casilla = laberinto[casillaIzquierdai + casillaIzquierdaj * columnas]->casilla;
                break;
            }
            sleep(0.5);               
        }
        semaforo = 1; 
        //Si es = 1 ya se paso en esta direccion
        if (info == 1 || casilla == 1)
        {
            //invalida para seguir
            return -1;
        }
        else if(info == 2)
        {
            return 2;
        }
        else
        {
            //valido para seguir en esta direccion
            return 1;
        }
    }
    else
    {
        //casilla fuera del mapa
        return -1;
    }
}

revisarDerecha(int i, int j, int filas, int columnas)
{
    int casillaDerechai = i;
    int casillaDerechaj = j + 1;
    if (casillaDerechaj >= 0 && casillaDerechaj < columnas)
    {
        int info;
        int casilla;
        while(1)
        {
            if (semaforo)
            {
                semaforo = 0;
                info = laberinto[casillaDerechai + casillaDerechaj * columnas]->derecha;
                casilla = laberinto[casillaDerechai + casillaDerechaj * columnas]->casilla;
                break;
            }
            sleep(0.5);               
        }
        semaforo = 1; 
        //Si es = 1 ya se paso en esta direccion
        if (info == 1 || casilla == 1)
        {
            //invalida para mover
            return -1;
        }
        else if(info == 2)
        {
            return 2;
        }
        else
        {
            //valido para seguir en esta direccion
            return 1;
        }
    }
    else
    {
        //casilla fuera del mapa
        return -1;
    }
}


void calcularFilasyColumnas(char *archivo)
{
	int c;
	
	FILE *file;
	file = fopen(archivo, "r");
	if (file) 
	{
		while ((c = getc(file)) != EOF)
		{
		    if(c == '*')
		    {
			columnas++;
		    }
		    if (c == '/')
		    {
			columnas++;
		    }
		    if (c == '\n')
		    {
			columnas = 0;
			filas++;
		    }
		    if (c == ' ')
		    {
			columnas++;
		    }
		}
	}
	fclose(file);
    
}

void llenar_laberinto(struct nodo **laberinto)
{
	int c;
	FILE *file;
    file = fopen("Prueba.txt", "r");
    int i = 0;
    int j = 0;
    if (file) 
    {
        while ((c = getc(file)) != EOF)
        {
            struct nodo *nodo = malloc(sizeof(struct nodo));
            nodo->x = i;
            nodo->y = j;
            nodo->arriba = 0;
            nodo->abajo = 0;
            nodo->izquierda = 0;
            nodo->derecha = 0;

            if(c == '*')
            {
                nodo->casilla = 1;
                laberinto[i + j * columnas] = (struct nodo *) nodo;
                j++;
            }
            if (c == '/')
            {
                nodo->casilla = 2;
                laberinto[i + j * columnas] = (struct nodo *) nodo;
                j++;
            }
            if (c == ' ')
            {
                nodo->casilla = 0;
                laberinto[i + j * columnas] = (struct nodo *) nodo;
                j++;
            }
            if (c == '\n')
            {
                j = 0;
                i++;
            }
            
        }
    }
        fclose(file);
}
