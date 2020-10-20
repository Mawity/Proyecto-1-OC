#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
void crear_lista(tLista* l){
    ///Asigno memoria.
    *l=(tLista) malloc(sizeof(struct celda));
    ///Si la memoria no se asigno produce un error.
    if(*l==NULL)
        exit(LST_ERROR_MEMORIA);

    (*l) -> elemento=NULL; ///elemento nulo.
    (*l) -> siguiente=NULL; ///el puntero al sig elemento es nulo.

}

void l_insertar(tLista l, tPosicion p, tElemento e)
{
    ///Asigno memoria.
    tPosicion nuevaCelda=(tPosicion) malloc(sizeof(struct celda));
    ///Si la memoria no se asigno produce un error.
    if(nuevaCelda==NULL)
        exit(LST_ERROR_MEMORIA);
    ///Asigno a los elementos de la estructura su correspondiente dato.
    nuevaCelda->elemento=e;
    nuevaCelda->siguiente=p->siguiente;
    p->siguiente=nuevaCelda;
}

void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento))
{

    if(p->siguiente==NULL)//chequea si la posicion p es valida.
            exit(LST_POSICION_INVALIDA); //Lista Posicion Invalida;
    ///Guardo en una variable auxiliar los datos de la posicion a eliminar.
    tPosicion aux=p->siguiente;
    ///Actualizo el puntero de la posicion anterior con la posicion guardad en la variable auxiliar.
    p->siguiente=(aux->siguiente);
    ///Elimino el elemento.
    fEliminar(aux->elemento);
    aux->elemento=NULL;    //Elimino puntero
    aux->siguiente=NULL;
    free(aux); //libero el espacio de la celda a eliminar
}

void l_destruir(tLista* l, void (*fEliminar)(tElemento))
{
    ///Guardo la posicion del primer elemento.
    tPosicion actual=(*l)->siguiente;
    tPosicion aux;
    ///Mientras no se acabe la lista.
    while(actual != NULL){
        ///Elimino el elemento.
        fEliminar(actual->elemento);
        ///Guardo en una variable auxiliar el puntero a la posicion en la que estoy trabajando.
        aux=actual;
        ///Actualizo la posicion actual.
        actual=(aux->siguiente);

        aux->elemento=NULL;    //Elimino punteros
        aux->siguiente=NULL;
        free(aux);
    }
    free(*l); //elimino puntero a la lista
    l=NULL;   //elimino puntero de puntero a la lista
}

tElemento l_recuperar(tLista l, tPosicion p)
{
    ///Si la siguiente posicion es nula significa que estoy pidiendo el elemento utilizando la posicion fin que con posicion indirecta es una operacion invalida.
    if(p->siguiente==NULL)
        exit(LST_POSICION_INVALIDA);
    ///Retorono el elemento de la posicion pedida.
    return (p->siguiente->elemento);
}

tPosicion l_primera(tLista l)
{   ///Retorno la primera posicion, en este caso devuelvo el centinela.
    return l;
}

tPosicion l_siguiente(tLista l, tPosicion p)
{
    ///Si la siguiente posicion es nula significa que estoy pidiendo el siguiente a la posicion fin que es una operacion invalida al estar trabajando con posicion indirecta.
    if(p->siguiente == NULL)
        exit (LST_NO_EXISTE_SIGUIENTE);
    ///Retorno la siguiente posicion.
    return p->siguiente;
}

tPosicion l_anterior(tLista l, tPosicion p)
{
    ///Si la posicion en la que estoy trabajando es la primera posicion significa que le paso la posicion del centinela y al no exisitir su anterior es una operacion invalida.
    if(p == l_primera(l))
        exit(LST_NO_EXISTE_ANTERIOR);
    ///Guardo la posicion dada en una variable auxiliar.
    tPosicion anterior=l;
    ///Recorro la lista de posiciones hasta encontrar el anterior de la posicion dada.
    while (anterior->siguiente != p){
        anterior=anterior->siguiente;
    }
    ///Devuelvo la posicon anterior a la dada.
    return anterior;
}

tPosicion l_ultima(tLista l)
{
    ///Si la lista esta vacia devuelvo el primer elemento.
    if(l->siguiente == NULL){
        return l;
    }
    ///Guardo la primera posicion en una variable auxiliar.
    tPosicion iterador=l;
    ///Recorro la lista hasta llegar a la ultima posicion.
    while(iterador->siguiente->siguiente !=NULL){
        iterador=iterador->siguiente;
    }
    ///Devuelvo la ultima posicion.
    return iterador;
}

tPosicion l_fin(tLista l)
{
    ///Guardo la primera posicion en una variable auxiliar.
    tPosicion iterador=l;
    ///Recorro la lista hasta llegar a la posicion fin.
    while(iterador->siguiente != NULL){
        iterador=iterador->siguiente;
    }
    ///Retorno la posicion fin.
    return iterador;
}

int l_longitud(tLista l)
{
    ///Creo una variable contador.
    int cont=0;
    ///Guardo la primera posicion en una variable auxiliar.
    tPosicion iterador=l;
    ///Recorro la lista hasta la ultima posicion, aumentando el contador al pasar por cada posicion.
    while(iterador->siguiente !=NULL){
        iterador=iterador->siguiente;
        cont++;
    }
    ///Retorno el contador.
    return cont;
}
