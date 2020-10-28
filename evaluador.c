#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mapeo.c"

#define OPEN_FILE_ERROR -1
#define PROG_INIT_ERROR -2

// Interfaz de funciones
int fHash(void *p);
int fComparacion(void *e1, void *e2);
void fEliminarC(char *clave);
void fEliminarV(int *valor);
void sacarPunto(char word[]);

int main(int argc, char *argv[]){
tMapeo mapeo;
FILE *archivo;
  if(argc == 2){
	char *nombre_archivo[20];
	*nombre_archivo = argv[1];
    crear_mapeo(&mapeo,99,&fHash,&fComparacion);

    // Abro el archivo a leer
    if((archivo = fopen(*nombre_archivo,"r")) == NULL){
		printf("%s\n","Archivo invalido");
		return -1;

    } else {
        if(feof(archivo))
          printf("%s\n","Archivo vacio");
        else {//mapeo las palabras
            tValor cantWord;
            char *word;
            word = (char *) malloc(50*sizeof(char));

            while (fscanf(archivo, "%s", word) != EOF){
                //sacarle el punto a la palabra
                sacarPunto(word);

                //printf("%s\n",word); //DEBUG
                cantWord = m_recuperar(mapeo,word);
                //printf("%p\n",(tValor)cantWord); //DEBUG
                if((cantWord) != NULL){
                    cantWord++;
                    m_eliminar(mapeo,word,(void*)&fEliminarC, (void*)&fEliminarV);
                    m_insertar(mapeo,word,cantWord);
                } else {
                    m_insertar(mapeo,word,(tValor) 1);
                }
            //rewind(archivo);
            }
        }
      }
    } else
        printf("%s\n","Error en el numero de argumentos");


    // MENU DEL EVALUADOR
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
            printf("*** La cantidad de veces que aparece la palabra es: %p\n\n\n",cant);
            break;
          }
          case 2:
            printf("%s\n","---> Ha finalizado la ejecucion del programa");
            m_destruir(&mapeo, (void*) &fEliminarC, (void*) &fEliminarV);
            fclose(archivo);
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

void sacarPunto(char word[]){
    char letra;
    for(int i=0; i<strlen(word);i++){
        letra = word[i];
        if(letra == '.'){
            word[i]='\0';
        }
    }
    //printf("Palabra sin el punto:%s\n",word);
}

int fHash(void *p){
    char* word = p;
    int hash = 0;
    int i=0;
    while(i<strlen(word)){
        hash = 31 * hash + word[i];
        i++;
    }

    return abs(hash);
}

int fComparacion(void *e1, void *e2){
   return (strcmp(e1,e2));
   return (strcmp(e1,e2)==0);
}

void fEliminarC(char *clave) {
    clave = NULL;
    free(clave);
}

void fEliminarV(int *valor) {
    valor = NULL;
    free(valor);
}
