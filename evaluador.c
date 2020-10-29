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
        else {//mapeo las palabras (metodos sacados de internet)

            //strdup() duplica la cadena y hace malloc correctamente
            //strtok() divide la cadena en palabras para interpretar una por una, la division la define fin[]
            char *word, *cArchivo, *palabras;
            word = (char *) malloc(50*sizeof(char));
            char fin[] = "\n. ";
            char cadena[255];
            int cantWord;
            //reservo lugar para cadenas desde el archivo que son inicializadas por fgets()
            cArchivo = (char *)malloc(255*sizeof(char));

            while(cArchivo != NULL) {
                //fgets() toma la cadena de 99 caracteres del archivo
                cArchivo = fgets(cadena, 100, archivo); //lee 99, porque lee el EOF o EOL
                palabras = strtok(cArchivo, fin);
                while(palabras != NULL){
                    cantWord = (int) m_recuperar(mapeo, palabras) + 1;
                    word = strdup(palabras);
                    m_eliminar(mapeo,word,(void*)&fEliminarC,(void*)&fEliminarV);//funciona mal si borro esta linea
                    m_insertar(mapeo, word, (tValor) cantWord);
                    palabras = strtok(NULL, fin);
                    /*
                        Poniendo de primer parametro NULL hacemos que corte el ciclo porque no tiene mas cadena para dividir
                            por lo tanto al terminar con una palabra termina y vuelve a buscar otra.
                        El metodo destruye el primer parametro por lo tanto no vuelve a leer la misma palabra
                     */
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
            cant = m_recuperar(mapeo,wordMenu);
            printf("*** La cantidad de veces que aparece la palabra es: %d\n\n\n",(int)cant);
        }else{
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
