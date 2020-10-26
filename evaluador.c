#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "mapeo.h"

int fHash(void *p);
int fComparacion(void *e1, void *e2);

int main(int argc, char *argv[]){

  if(argc == 2){
  char *nombre_archivo[20];
  *nombre_archivo = argv[1];

  printf("%s\n","Creando mapeo...");
  tMapeo mapeo;
  crear_mapeo(&mapeo,9,fHash,fComparacion);

  // Abro el archivo a leer
  FILE *archivo;
  if((archivo = fopen(nombre_archivo,"r")) == NULL){
    printf("%s\n","archivo invalido");
    return -1;
  } else {
        if(feof(archivo))
          printf("%s\n","Archivo vacío");
        else {
          int i = 0,clave,j;
          char palabra[15];
          while(!feof(archivo)){ //end of file
            while(&archivo[i] != ' ')  //Puede ser que funcione con '&'
                palabra[i++] = fgetc(archivo); //guarda una palabra

            clave = fHash(palabra);
            m_insertar(mapeo,clave,palabra);
            i = 0;
            for(j = 0; j < 15; j++) // limpio el char (debe haber otra forma)
              palabra[j] = ' ';
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

        switch(op){
          case 1: {
            printf("%s","---> Ingrese a una palabra: ");
            scanf("%s",word);
            printf("\n");
            fflush(stdin);
            break;
          }
          case 2:
            printf("%s\n","---> Ha finalizado la ejecución del programa");
            seguir = 0;
        }
      }

  return 0;
}

int fHash(void *p){
   return ((int)strlen(p));
}

int fComparacion(void *e1, void *e2){
   return (strcmp(e1,e2));
   return (strcmp(e1,e2)==0);
}
/*
void *apariciones(char *palabra[],tMapeo mapeo){

}
*/
