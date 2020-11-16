#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mapeo.h"

#define OPEN_FILE_ERROR -1
#define PROG_INIT_ERROR -2
#define MEMORY_ALLOC_ERROR -3

// Interfaz de funciones
int fHash(void *p);
int fComparacion(void *e1, void *e2);
void fEliminarC(void *clave);
void fEliminarV(void *valor);


tMapeo mapeo;
FILE *archivo;


int main(int argc, char *argv[]){

//analizar el archivo y mapearlo
if(argc == 2){
    char *nombre_archivo[32]; //el nombre del archvo tiene que ser menor a 32 caract
    *nombre_archivo = argv[1]; //lo hago asi para no hardcodear el codigo asignando a argv[1]="file.txt"
    crear_mapeo(&mapeo,50,&fHash,&fComparacion);

    // Abro el archivo a leer
    archivo = fopen(*nombre_archivo,"r");
    if(archivo == NULL){
        printf("%s\n","Archivo invalido");
        exit(OPEN_FILE_ERROR);
    } else {
        if(feof(archivo))
            printf("%s\n","Archivo vacio");
        else {//mapeo las palabras

            //strdup() duplica la cadena y hace malloc correctamente
            //strtok() divide la cadena en palabras para interpretar una por una, la division la define fin[]
            int *cantWord;
            int *nuevaEntrada;
            char fin[] = "\n. ";
            char cadena[255];
            char *word, *palabras;

            while(!feof(archivo)) {
                fgets(cadena, 100, archivo);
                palabras = strtok(cadena, fin);

                while(palabras != NULL){
                    word = strdup(palabras);
                    if(word==NULL){ exit(MEMORY_ALLOC_ERROR); }

                    cantWord = m_recuperar(mapeo, palabras);

                    if(cantWord==NULL){
                        nuevaEntrada = malloc(sizeof(int));
                        if(nuevaEntrada == NULL){
                            exit(MEMORY_ALLOC_ERROR);
                        }
                        *nuevaEntrada = 1;
                        m_insertar(mapeo, word, nuevaEntrada);
                    }else{
                        free(word);
                        *cantWord = *(cantWord) + 1;
                    }

                    palabras = strtok(NULL, fin);
                    /*  Poniendo de primer parametro NULL hacemos que corte el ciclo porque no tiene mas cadena para dividir
                            por lo tanto al terminar con una palabra termina y vuelve a buscar otra.
                        El metodo destruye el primer parametro por lo tanto no vuelve a leer la misma palabra
                     */
                }
            }
            fclose(archivo);
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
int cantApariciones = 0;//valor entero de la cantidad de veces que aparece la palabra
char *wordMenu;
wordMenu = (char *) malloc(32*sizeof(char));

while(seguir){
    printf("%s\n\n\n","---------------------Menu de opciones--------------------");
    printf("%s\n\n","1. Cantidad de apariciones\n2. Salir");
    scanf("%d",&op);
    fflush(stdin);

    switch(op){
      case 1: {
        printf("%s","---> Ingrese a una palabra: \n");
        scanf("%s",(char*)wordMenu);
        fflush(stdin);
        cant = m_recuperar(mapeo,wordMenu);
        if(cant!=NULL){
            cantApariciones = *((int*) cant);
        }//transformo el tValor "cant" a valor entero "cantApariciones"

        printf("*** La cantidad de veces que aparece la palabra es: %d\n\n\n",cantApariciones);
        break;
      }
      case 2:
        printf("%s\n","---> Ha finalizado la ejecucion del programa");
        m_destruir(&mapeo, &fEliminarC, &fEliminarV);
        fclose(archivo);
        seguir = 0;
        break;
    }
  }
return 0;
}

/*
    ###############################################
     IMPLEMENTACION DE LAS INTERFACES DE FUNCIONES
    ###############################################
*/

/*  Funcion Hash, fuentes:
    1) http://www.cse.yorku.ca/~oz/hash.html
    2) https://stackoverflow.com/questions/7666509/hash-function-for-string
*/
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
   return (strcmp((char*)e1,(char*)e2));
   return (strcmp((char*)e1,(char*)e2)==0);
}

void fEliminarC(void *clave) {
    free(clave);
    clave = NULL;
}

void fEliminarV(void *valor) {
    free(valor);
    valor = NULL;
}
