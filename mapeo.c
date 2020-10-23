#include "mapeo.h"
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

// claves y valores son punteros genericos
// tabla hash abierta usando el tda lista
// HASH ABIERTO: consiste en tener en cada pos de la tabla una lista de los elementos que
//  de acuerdo a la funcion de hash, correspondan a dicha posicion.

tLista map[10];

void crear_mapeo(tMapeo * m, int ci, int (*fHash)(void *), int (*fComparacion)(void *, void *)){
  if((*m) != NULL){
    tMapeo mapeo = (tMapeo) malloc(sizeof(struct mapeo));
    mapeo->longitud_tabla = 10;
    mapeo->cantidad_elementos = 0;
    tLista lista;
    crear_lista(&lista);
    mapeo->tabla_hash = (&lista);
    mapeo->comparador = fComparacion;
    mapeo->hash_code = fHash;

    int i;
    for(i = 0; i < mapeo.longitud_tabla; i++){
      tLista list;
      crear_lista(&list);
      map[i] = list;
    }

    *m = mapeo;
  } else
    exit(MAP_ERROR_MEMORIA);
}

int fHash(void *p){
   return ((int)strlen(p));
}

int fComparacion(void *e1, void *e2){
   return (strcmp(e1,e2));
   return (strcmp(e1,e2)==0);
}

int factor_carga(){
  // debe ser menor o igual a 75% de la long de la tabla
}

tValor m_insertar(tMapeo m, tClave c, tValor v){

}

void m_eliminar(tMapeo m, tClave c, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){

}

void m_destruir(tMapeo * m, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){

}

tValor m_recuperar(tMapeo m, tClave c){

}
