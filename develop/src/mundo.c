/******************************************************************************

Nombre del módulo: mundo.c

Descripción: 
         Funciones para el manejo del mundo que es el que contiene los entornos
         que coforman en juego

Autor: Diego Chicote

Fecha: 14-04-2013

Modulos propios que necesita: 
- mundo.h

Modificaciones: 
[14-04-2013] Creación de fichero y comienzo de implementación del pseudocódigo.
[14-04-2013] Terminadas las funciones:
 *           -iniMundo
 *           -destruirMundo
 *           -iniNodoMundo
 *           -destruyeNodoMundo
 *           -buscarEnMundo
 *           -pushNodoMundo
 *           -popNodoMundo
 *           -esVacioMundo
[15-04-2013] :añadidos comentarios en:
 *           -iniMundo
 *           -destruirMundo
 *           -iniNodoMundo
 *           -destruyeNodoMundo
 *           -buscarEnMundo
 *           -pushNodoMundo
 *           -popNodoMundo
 *           -esVacioMundo
[2-5-2013]  :Diego chicote añade funcion:
 *           -getEntornoNodoMundo
[16-5-2013] Inaki Cadalso cambia la estructura de mundo añadiendo Personaje
 *                         y su consecuencia en el cambio de iniMundo;
Mejoras pendientes: 
- Pruebas de funciones.

 ******************************************************************************/

#include "mundo.h"
#include "personaje.h"

/*-----------------------------------------------------------------------------

Nombre: iniMundo

Descripción:
Reserva memoria para el mundo.

Argumentos de entrada:
1. world, puntero al mundo.

Retorno: 
-  OKE, si se ha terminado sin problemas
- ERROR_RM, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS iniMundo(MUNDO* world) {

   
    if (world == NULL)
        return ERROR_RM;
    world->primero = NULL;
    world->ultimo = NULL;
    world->numEntornos = 0;
    
    world->pj=(PERSONAJE*)malloc(sizeof(PERSONAJE));
    iniPj(world->pj);
    creaPersonaje(world->pj);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: destruirMundo

Descripción:
 * Libera la memoria reservada para el mundo

Argumentos de entrada:
1. world, puntero al mundo.

Retorno: 
-  OKE, si se ha terminado sin problemas
- ERROR_RM, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS destruirMundo(MUNDO* world) {

    NODO_MUNDO* aux = NULL;


    if (world == NULL)
        return ERROR;

    if (esVacioMundo(world)) {
        free(world);
        return OKE;
    }
    while (!esVacioMundo(world)) {
        aux = world->ultimo;
        if (world->numEntornos == 1) {
            world->numEntornos--;
            world->primero = NULL;
            world->ultimo = NULL;
            destruyeNodoMundo(aux);
            free(world);
            return OKE;
        }
        if (aux->siguiente == NULL) {
            world->numEntornos--;
            aux->anterior->siguiente = NULL;
            world->ultimo = aux->anterior;
            aux->anterior = NULL;
            destruyeNodoMundo(aux);
        }
    }

    return ERROR;
}

/*-----------------------------------------------------------------------------

Nombre: iniNodoMundo

Descripción:
Esta función reserva memoria para un nodo del mundo, e inserta en el un
un entorno.

Argumentos de entrada:
1. NODO_MUNDO, el nodo que se iniciara.
2. ent, el entorno que se insertara en el nodo.

Retorno: 
- OKE, si se ha terminado sin problemas
- ERROR, si el entorno que recibe la función esta vacío.
- ERROR_RM, si se produce un error al reservar memoria.

-----------------------------------------------------------------------------*/
extern STATUS iniNodoMundo(NODO_MUNDO* nodo,ENTORNO* ent){

    if (ent == NULL)
        return ERROR;
    
    if (nodo == NULL)
        return ERROR_RM;
    nodo->ent=ent;
    nodo->anterior = NULL;
    nodo->siguiente = NULL;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: destruyeNodoMundo

Descripción:
Libera la memoria que se reservo para un nodo del mundo.

Argumentos de entrada:
1. nodo, el nodo que se liberara.

Retorno: 
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS destruyeNodoMundo(NODO_MUNDO* nodo){

    if (nodo == NULL)
        return ERROR;
    destruirEntorno(nodo->ent);
    free(nodo);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: buscarEnMundo

Descripción:
Recorre el mundo, buscando en el los nodos un entorno que coincida con
el nombre de entorno que recibe.

Argumentos de entrada:
1. world, el mundo en el que buscara el entorno.
2. nombreEnt, el nombre del entorno que se busca.

Retorno: 
- OKE,   si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS buscarEnMundo(MUNDO* world,NODO_MUNDO* nodo, const char* nombreEnt) {

    int i = 0;
    char * nombre = NULL;

    if (world == NULL || esVacioMundo(world))
        return ERROR;

    nombre = (char*) malloc(sizeof (MAX_NOM_ENT));
    nodo = world->primero;

    for (i = 0; i < world->numEntornos; i++) {
        getNombreEnt(world->primero->ent, nombre);
        if (strcmp(nombre, nombreEnt) == 0) {
            free(nombre);
            return OKE;
        }
        nodo = nodo->siguiente;
    }
    free(nombre);
    return ERROR;
}

/*-----------------------------------------------------------------------------

Nombre: pushNodoInv

Descripción:
Inserta un nodo con entorno en el mundo.

Argumentos de entrada:
1. world, mundo en el que se insertara el entorno.
2. nodo, nodo que se insertara en el mundo.

Retorno: 
- OKE  , si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS pushNodoMundo(MUNDO* world, NODO_MUNDO* nodo){

    if (world == NULL || nodo == NULL)
        return ERROR;
    if (world->numEntornos == 0) {
        world->numEntornos++;
        world->primero = nodo;
        world->ultimo = nodo;
        return OKE;
    }
    if (world->numEntornos < MAX_MUNDO) {
        world->numEntornos++;
        (world->ultimo)->siguiente = nodo;
        nodo->anterior = world->ultimo;
        world->ultimo = nodo;
        return OKE;
    }
    return ERROR;
}

/*-----------------------------------------------------------------------------

Nombre: popNodoMundo

Descripción:
Extrae del mundo un elemento que coincida con el nombre que se le pasa.

Argumentos de entrada:
1. world, mundo que se comprobara.
2. nodo,ptr en el que se almacenara el nodo extraido.
3. nombreEnt,nombre del entorno que se quiere extraer del mundo.

Retorno: 
- OKE, si funciona correctamente.
- ERROR, si es se produce algún error;

-----------------------------------------------------------------------------*/
extern STATUS popNodoMundo(MUNDO* world, NODO_MUNDO* nodo,char* nombreEnt){
    
    if (world == NULL || nodo == NULL)
        return ERROR;
    if (esVacioMundo(world))
        return ERROR;
    if (buscarEnMundo(world, nodo, nombreEnt) == ERROR)
        return ERROR;

    if (world->numEntornos == 1) {
        world->numEntornos--;
        world->primero = NULL;
        world->ultimo = NULL;
        return OKE;
    }

    if (nodo->anterior == NULL) {
        world->numEntornos--;
        (nodo->siguiente)->anterior = NULL;
        world->primero = nodo->siguiente;
        nodo->siguiente = NULL;
        return OKE;
    }

    if (nodo->siguiente == NULL) {
        world->numEntornos--;
        nodo->anterior->siguiente = NULL;
        world->ultimo = nodo->anterior;
        nodo->anterior = NULL;
        return OKE;
    }


    if (nodo->anterior != NULL && nodo->siguiente != NULL) {
        world->numEntornos--;
        nodo->anterior->siguiente = nodo->siguiente;
        nodo->siguiente->anterior = nodo->anterior;
        nodo->anterior = NULL;
        nodo->siguiente = NULL;
        return OKE;
    }

    return ERROR;
}

/*-----------------------------------------------------------------------------

Nombre: esVacioMundo

Descripción:
Comprueba si el mundo esta vacío.

Argumentos de entrada:
1. world, mundo que se comprobara.

Retorno: 
- VERDADERO, si está vacío.
- FALSO, si contiene algún entorno.
- ERROR, si es NULL;

-----------------------------------------------------------------------------*/
extern BOOL esVacioMundo(MUNDO* world){

    if (world == NULL)
        return ERROR;
    if (world->numEntornos == 0)
        return VERDADERO;
    return FALSO;
}

extern ENTORNO* getEntornoNodoMundo(NODO_MUNDO* nodo){

    return nodo->ent;
}