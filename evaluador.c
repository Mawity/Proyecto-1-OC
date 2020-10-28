#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapeo.h"

#define OPEN_FILE_ERROR -1
#define PROG_INIT_ERROR -2

int fHash(void *p);
int fComparacion(void *e1, void *e2);
void leer_palabra(char *palabra, FILE *archivo);

int main(int argc, char *argv[]){
    tMapeo mapeo;
    if(argc == 2){
        char *nombre_archivo[20];
        *nombre_archivo = argv[1];

        printf("%s\n","Creando mapeo...");

        crear_mapeo(&mapeo,9,&fHash,&fComparacion);

        // Abro el archivo a leer
        FILE *archivo;
        if((archivo = fopen(nombre_archivo,"r")) == NULL){
            printf("%s\n","Archivo invalido");
            return -1;
        } else {
            if(feof(archivo))
                printf("%s\n","Archivo vacio");
            else {
                tValor cant;
                char *palabra = (char*) malloc(30*sizeof(char));
                while(!feof(archivo)){
                    leer_palabra(palabra,archivo);
                    cant = m_recuperar(mapeo,palabra);

                    if(m_recuperar(mapeo, palabra) != NULL){
                        cant++;
                        m_insertar(mapeo,palabra,cant);
                    } else { //si la palabra no estaba en el mapeo
                        m_insertar(mapeo,palabra,(tValor) 1);
                    }
                    rewind(archivo);
                }
            }
          }
    } else
        printf("%s\n","Error en el numero de argumentos");

    int op,seguir;
    char word[15];
    while(seguir){
        printf("%s\n\n\n","---------------------Menu de opciones--------------------");
        printf("%s\n\n","1. Cantidad de apariciones\n2. Salir");
        scanf("%d",&op);
        fflush(stdin);
        //OPCIONES DE USUARIO
        switch(op){
          case 1: {
            printf("%s","---> Ingrese a una palabra: ");
            scanf("%s",word);
            printf("\n");
            fflush(stdin);
            tValor cant = m_recuperar(mapeo,word);
            printf("*** La cantidad de veces que aparece la palabra es: %d", cant);//warning por falta de casteo de int a tValor
            break;
          }
          case 2:
            printf("%s\n","---> Ha finalizado la ejecucion del programa");
            seguir = 0;
        }
    }
    return 0;
}

void leer_palabra(char *palabra, FILE *archivo){
    int i = 0;
    char caract = 0;
    while((caract = fgetc(archivo)) != EOF){
        if(caract != '\n' && caract != ' '){
        palabra[i++] = caract;
        }
    }
}

int fHash(void *p){
    return ((int)strlen(p));
}

int fComparacion(void *e1, void *e2){
    return (strcmp(e1,e2));
    return (strcmp(e1,e2)==0);
}
