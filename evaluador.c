#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mapeo.h"

#define OPEN_FILE_ERROR -1
#define PROG_INIT_ERROR -2

// Interfaz de funciones
int fHash(void *p);
int fComparacion(void *e1, void *e2);
void fEliminarC(char *clave);
void fEliminarV(int *valor);
void sacarPunto(char word[]);


tMapeo mapeo;
FILE *archivo;


int main(int argc, char *argv[]){

//analizar el archivo y mapearlo
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

            //hacer por cada palabra nueva un malloc
            //no hacer free, sino se borran las claves
            char *word;
            word = (char *) malloc(50*sizeof(char));
            int cantWord;

            while (fscanf(archivo, "%s", word) != EOF){
                //lee las palabras correctamente
                //no las inserta como debe ser
                sacarPunto(word);
                cantWord = (int) m_recuperar(mapeo,word);
                //printf("cantWord: %d\n",cantWord);
                //desreferenciar el puntero y sumar
                if((cantWord) != 0){
                    cantWord = (int) m_recuperar(mapeo,word) + 1;
                    m_insertar(mapeo,word,(tValor)cantWord);
                } else {
                    word = (char *) malloc(50*sizeof(char)); //reservar lugar para cada palabra nueva
                    m_insertar(mapeo,word,(tValor) 1);
                }
            }
        }
    }
} else{
    printf("%s\n","Error en el numero de argumentos");
    return -2;
}


// MENU DEL EVALUADOR

int op;
int seguir = 1;
tValor cant;
char *wordMenu;
wordMenu = (char *) malloc(50*sizeof(char));

while(seguir){
    printf("%s\n\n\n","---------------------Menu de opciones--------------------");
    printf("%s\n\n","1. Cantidad de apariciones\n2. Salir");
    scanf("%d",&op);
    fflush(stdin);

    switch(op){
      case 1: {
        printf("%s","---> Ingrese a una palabra: \n");
        scanf("%s",(char*)wordMenu);

        cant = m_recuperar(mapeo,wordMenu);
        if(cant!=0){
            printf("not NULL\n");
            cant = m_recuperar(mapeo,wordMenu);
            printf("*** La cantidad de veces que aparece la palabra es: %d\n\n\n",(int)cant);
        }else{
            printf("NULL\n");
            cant = 0;
            printf("*** La cantidad de veces que aparece la palabra es: %d\n\n\n",(int)cant);
        }
        fflush(stdin);
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

/**
    Saca los puntos o comas que esten pegados a las palabras
    Obs: no es la mejor forma porque por cada palabra del archivo vuelve a recorrer la misma palabra
        por lo tanto tiene un tiempo O(n^2) poruqe termina viendo el archivo 2 veces en total.
**/
void sacarPunto(char word[]){
    char letra;
    for(int i=0; i<strlen(word);i++){
        letra = word[i];
        if(letra == '.' && letra==','){
            word[i]='\0';
        }
    }
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
