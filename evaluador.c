#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mapeo.c"

#define OPEN_FILE_ERROR -1
#define PROG_INIT_ERROR -2

int fHash(void *p);
int fComparacion(void *e1, void *e2);
void readWord(char *w[]);



int main(int argc, char *argv[]){
tMapeo mapeo;
  if(argc == 2){
	char *nombre_archivo[20];
	*nombre_archivo = argv[1];
	printf("%s\n","Creando mapeo...");
    crear_mapeo(&mapeo,99,&fHash,&fComparacion);

    // Abro el archivo a leer
    FILE *archivo;
    if((archivo = fopen(*nombre_archivo,"r")) == NULL){
		printf("%s\n","Archivo invalido");
		return -1;

    } else {
        if(feof(archivo))
          printf("%s\n","Archivo vacio");
        else {//mapeo las palabras
            //printf("Entre a mapear \n");
            tValor cantWord;
            char *word;
            word = (char *) malloc(50*sizeof(char));

            while (fscanf(archivo, "%s", word) != EOF){
                //printf("%s\n",word); //las lee perfecto
                cantWord = m_recuperar(mapeo,word);
                printf("%d",(tValor)cantWord);
                if((cantWord) != NULL){
                    cantWord++;
                    m_insertar(mapeo,word,cantWord); //no actualiza el valor de cantWord
                } else { //Si aun no se mapeo esa palabra
                    m_insertar(mapeo,word,(tValor) 1);
                }
            //rewind(archivo);
            }
        }
      }
    } else
        printf("%s\n","Error en el numero de argumentos");

    //printf("%s\n","Creando mapeo...");
    //crear_mapeo(&mapeo,9,&fHash,&fComparacion);

    int op;
    int seguir = 1;
    char word[15];
    while(seguir){
        printf("%s\n\n\n","---------------------Menu de opciones--------------------");
        printf("%s\n\n","1. Cantidad de apariciones\n2. Salir");
        scanf("%d",&op);
        fflush(stdin);

        switch(op){
          case 1: {
            printf("%s","---> Ingrese a una palabra: ");
            scanf("%s",word);
            printf("\n");
            fflush(stdin);
            tValor cant = m_recuperar(mapeo,word);
            printf("*** La cantidad de veces que aparece la palabra es: %p",cant);

            break;
          }
          case 2:
            printf("%s\n","---> Ha finalizado la ejecucion del programa");
            seguir = 0;
        }
      }

    return 0;
}

/*
    ###############################################
     IMPLEMENTACION DE LAS INTERFACES DE FUNCIONES
    ###############################################
*/

int fHash(void *p){
   return ((int)strlen(p));
}

int fComparacion(void *e1, void *e2){
   return (strcmp(e1,e2));
   return (strcmp(e1,e2)==0);
}

/*
void readWord(char *w[]){
    char c;
	int i=0;
	while((c = fgetc(archivo)) != EOF) {
		if(c == ' ' || c == '\n') {
			w[i]=c;
		}
		i++;
		//cada ves que lee una palabra termina recorriendo todo el archivo
		//el orden del metodo se podria acotar por el tamaño de la palabra
	}
}
*/
