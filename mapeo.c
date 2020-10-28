#include <stdio.h>
#include <stdlib.h>
#include "lista.c"
#include "mapeo.h"

#define max(a,b)    (((a) > (b)) ? (a) : (b))

// claves y valores son punteros genericos
// tabla hash abierta usando el tda lista
// HASH ABIERTO: consiste en tener en cada pos de la tabla una lista de los elementos que
//  de acuerdo a la funcion de hash, correspondan a dicha posicion.

//Modularizo las interfaces para que no quede la implementacion primero
void reHash(tMapeo m);
void (*fEliminarClave)(void *);
void (*fEliminarValor)(void *);
void fEliminarEntrada(tElemento e);

//factor de carga
const float FC = 0.75;


void crear_mapeo(tMapeo * m, int ci, int (*fHash)(void *), int (*fComparacion)(void *, void *)){

    int cantInicial = max(10, ci);
    (*m) = (tMapeo) malloc(sizeof (struct mapeo));

    if (*m == NULL){
        exit (MAP_ERROR_MEMORIA);
    }else{
        tLista * lista = (tLista*) malloc(sizeof(tLista) * cantInicial);
        //Inicializacion de las listas en cada bucket de la tabla
        for (int i=0; i < cantInicial; i++){
            crear_lista(&lista[i]);
        }
        (*m)->longitud_tabla = cantInicial;
        (*m)->cantidad_elementos = 0;
        (*m)->tabla_hash = lista;
        (*m)->hash_code = fHash;
        (*m)->comparador = fComparacion;
    }
}

/**
     Inserta una entrada con clave C y valor V, en M.
     Si una entrada con clave C y valor Vi ya existe en M, modifica Vi por V.
     Retorna NULL si la clave C no existia en M, o Vi en caso contrario.
     Finaliza indicando MAP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/
tValor m_insertar(tMapeo m, tClave c, tValor v){

    if(m == NULL || c == NULL || v == NULL) {
        exit(MAP_ERROR_MEMORIA);
    }else{
        tLista l;
        tPosicion posA, posF;
        tEntrada entrada,nueva;
        tValor vi = NULL;
        int encontre = 0; //bool
        int bucket = m->hash_code(c) % m->longitud_tabla; //valor de la clave C

        l = *(m->tabla_hash+bucket);
        posA = l_primera(l);
        posF = l_fin(l);

        //Recorre el bucket para encontrar la palabra repetida
        while (posA != posF && !encontre) {
            entrada = (tEntrada) l_recuperar(l,posA);
            tClave *clave = entrada->clave;
            if(m->comparador(clave,c) != 0){
                encontre = 1; //La encontro!
                vi = (tValor) entrada->valor; //valor a retornar
                entrada->valor = v; //Modifica el valor de la entrada
            }else{
                posA = l_siguiente(l,posA); //sigue buscando
            }
        }
        if(!encontre){ //agregar al mapeo nueva entrada
            if(((m->cantidad_elementos +1) / (m->longitud_tabla)) >= FC){ //factor de carga superado
                reHash(m);
            }
            //Como la entrada no existe se crea un lugar para ella y se inserta
            nueva = (tEntrada) malloc(sizeof(struct entrada));
            nueva->clave = c;
            nueva->valor = v;
            l_insertar(l,posA,nueva);
            m->cantidad_elementos++;
        }
        return vi;
    }
}

/**
     Elimina la entrada con clave C en M, si esta existe.
     La clave y el valor de la entrada son eliminados mediante las funciones fEliminarC y fEliminarV.
**/
void m_eliminar(tMapeo m, tClave c, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){

    if (c == NULL){
        exit(MAP_ERROR_MEMORIA);
    }else{
        int hashCode = m->hash_code(c) % m->longitud_tabla;
        tLista bucket = m->tabla_hash[hashCode];
        tEntrada entrada;
        tPosicion posA = l_primera(bucket);
        tPosicion posF = l_fin(bucket);
        int eliminado = 0;
        //funciones para elimianr
        fEliminarClave = fEliminarC;
        fEliminarValor = fEliminarV;

        //Se recorre el bucket de la tabla a fin de encontrar la clave con elemento a eliminar.
        while(posA != posF && eliminado!=1){
            entrada = (tEntrada) l_recuperar(bucket, posA); //entrada para comparar
            if (m->comparador(c, entrada->clave) == 0){ //Lo encontro!
                eliminado = 1;
                l_eliminar(bucket, posA, &fEliminarEntrada);
            }
            else
                posA = l_siguiente(bucket, posA); //continua recorriendo
        }
    }
}

/**
     Destruye el mapeo M, elimininando cada una de sus entradas.
     Las claves y valores almacenados en las entradas son eliminados mediante las funciones fEliminarC y fEliminarV.
**/
void m_destruir(tMapeo * m, void (*fEliminarC)(void *), void (*fEliminarV)(void *)){
    int cant = (*m)->longitud_tabla;
    //funciones para eliminar
    fEliminarValor = fEliminarV;
    fEliminarClave = fEliminarC;

    //en todas las posiciones de la pabla de eliminan los buckets
    for (int i=0; i < cant; i++){
        tLista liberar = (*m)->tabla_hash[i];
        l_destruir(&((*m)->tabla_hash[i]), &fEliminarEntrada);
        free(liberar); //libero un bucket
    }

    //se libera el mapeo
    free(m);
    (*m) = NULL;
}

/**
     Recupera el valor correspondiente a la entrada con clave C en M, si esta existe.
     Retorna el valor correspondiente, o NULL en caso contrario.
**/
tValor m_recuperar(tMapeo m, tClave c){
    int bucket = m->hash_code(c) % m->longitud_tabla;
    tLista l = m->tabla_hash[bucket]; //directamente calculo el lugar y hago la lista
    tValor recuperar = NULL;
    tPosicion posA, posF;
    tEntrada entrada;

    if(l_longitud(l) != 0){
        //principio y fin de cada bucket
        posA = l_primera(l);
        posF = l_fin(l);
        int encontre = 0; //bool
        while(posA!=posF && !encontre){ //Se recorre la lista correspondiente al bucket.
            entrada = (tEntrada) l_recuperar(l, posA);
            if (m->comparador(c, entrada->clave) == 0){ //Las claves son iguales, lo encontro!
                recuperar = entrada->valor;
                encontre = 1;
            }
            else
                posA = l_siguiente(l, posA);
        }
    }

    return recuperar;
}


/*
    ###############################################
     IMPLEMENTACION DE LAS INTERFACES DE FUNCIONES
    ###############################################
*/

/**
    Cuando se supero el factor de cargar:
        -Duplica el tamaño de la tabla hash.
        -Vuelve a calular la funcion hash para reacomodar todos los elementos correctamente.
**/
void reHash(tMapeo m){
    tEntrada entrada;
    tPosicion posA,posF; //se inicializan luego
    int viejaLong = m->longitud_tabla;
    int nuevaLong = 2 * m->longitud_tabla; //duplica el tamaño de la tabla
    tLista *lista = malloc(sizeof(tLista) * nuevaLong);

    //crea todos los nuevos buckets
	for (int i=0; i < nuevaLong; i++){
        crear_lista(lista + i);
	}

    for(int i = 0; i<viejaLong;i++){ // recorro los bucket a copiar
        // primera y ultima pos del bucket
        tLista bucket = m->tabla_hash[i];
        posA = l_primera(bucket);
        posF = l_fin(bucket);

        // vuelve a llenar cada lista en la nueva tabla
        while (posA != posF) {
            entrada = (tEntrada) l_recuperar(m->tabla_hash[i],posA);
            int bucketActual = m->hash_code(entrada->clave) % m->longitud_tabla;
            l_insertar(lista[bucketActual], l_fin(*lista), entrada);
            posA = l_siguiente(*lista, posA);
        }
        bucket->siguiente = NULL;
        bucket->elemento = NULL;
        bucket = NULL;
        free(bucket);
    }
    //actualizo valores
    (m)->tabla_hash = lista;
}

/**
      Funcion que elimina y libera el espacio de una entrada
**/
void fEliminarEntrada(tElemento e){
    tEntrada entrada = (tEntrada) e;
    fEliminarValor(entrada->valor);
    fEliminarClave(entrada->clave);
    free(entrada);
    entrada = NULL;
}

