#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

// Macros con c�digos de finalizaci�n
#define LST_NO_EXISTE_SIGUIENTE     1
#define LST_NO_EXISTE_ANTERIOR      2
#define LST_POSICION_INVALIDA       3
#define LST_ERROR_MEMORIA           4

// Structs para la manipulaci�n de una lista.
struct celda{
    void * elemento;
    struct celda * siguiente;
};

typedef struct celda * tLista;
typedef struct celda * tPosicion;
typedef void * tElemento;

// ---------------------------------------------------------------------------------------------
// Definici�n de prototipos y documentaci�n de las funciones.
// Obs.: a todo efecto y en tanto no se indique lo contrario, toda posici�n parametrizada
// es considerada v�lida.
// ---------------------------------------------------------------------------------------------

/**
 Inicializa una lista vacia.
 Una referencia a la lista creada es referenciada en *L.
 Finaliza indicando LST_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/
extern void crear_lista(tLista * l);

/**
 Inserta el elemento E, en la posici�n P, en L.
 Con L = A,B,C,D y la posici�n P direccionando C, luego:
 L' = A,B,E,C,D.
 Finaliza indicando LST_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/
extern void l_insertar(tLista l, tPosicion p, tElemento e);

/**
 Elimina la celda P de L.
 El elemento almacenado en la posici�n P es eliminado mediante la funci�n fEliminar.
 Finaliza indicando LST_POSICION_INVALIDA si P es fin(L).
**/
extern void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento));

/**
 Destruye la lista L, elimininando cada una de sus celdas.
 Los elementos almacenados en las celdas son eliminados mediante la funci�n fEliminar.
**/
extern void l_destruir(tLista * l, void (*fEliminar)(tElemento));

 /**
 Recupera y retorna el elemento en la posici�n P.
 Finaliza indicando LST_POSICION_INVALIDA si P es fin(L).
**/
extern tElemento l_recuperar(tLista l, tPosicion p);

/**
 Recupera y retorna la primera posici�n de L.
 Si L es vac�a, primera(L) = ultima(L) = fin(L).
**/
extern tPosicion l_primera(tLista l);

/**
 Recupera y retorna la posici�n siguiente a P en L.
 Finaliza indicando LST_NO_EXISTE_SIGUIENTE si P es fin(L).
**/
extern tPosicion l_siguiente(tLista l, tPosicion p);

/**
 Recupera y retorna la posici�n anterior a P en L.
 Finaliza indicando LST_NO_EXISTE_ANTERIOR si P es primera(L).
**/
extern tPosicion l_anterior(tLista l, tPosicion p);

/**
 Recupera y retorna la �ltima posici�n de L.
 Si L es vac�a, primera(L) = ultima(L) = fin(L).
**/
extern tPosicion l_ultima(tLista l);

/**
 Recupera y retorna la posici�n fin de L.
 Si L es vac�a, primera(L) = ultima(L) = fin(L).
**/
extern tPosicion l_fin(tLista l);

/**
 Retorna la longitud actual de la lista.
**/
extern int l_longitud(tLista l);

#endif // LISTA_H_INCLUDED
