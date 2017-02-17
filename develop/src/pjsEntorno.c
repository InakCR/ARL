/******************************************************************************

Nombre del módulo: pjsEntorno.c

Descripción: 
        Funciones para el manejo de la lista de pjs que hay en un entorno.

Autor: Miguel Gomez-Tavira

Fecha: 14-04-2013

Modulos propios que necesita: 
- pjsEntorno.h

Modificaciones: 
[14-04-2013] Creación de fichero y comienzo de implementación del pseudocódigo.
[14-04-2013] Terminadas las funciones:
 *           -iniPjsEnt
 *           -destruirPjsEnt
 *           -iniNodoPj
 *           -destruyeNodoPj
 *           -buscarPjsEnt
 *           -pushNodoPj
 *           -popNodoPj
 *           -esVacioPjsEnt
 [01-05-2013] Iñaki Cadalso corrige comentarios de funciones
 *          

Mejoras pendientes: 
- Pruebas de funciones.
- Correcion de comentarios, en cabecera y fuente.

 ******************************************************************************/


/*=== Cabeceras =============================================================*/
#include "pjsEntorno.h"

/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------

Nombre: iniIPjsEnt

Descripción:
Reserva memoria para personajes de Entorno.

Argumentos de entrada:
1. pjsEnt, puntero al inventario.

Retorno: 
-  OKE, si se ha terminado sin problemas
- ERROR_RM, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS iniPjsEnt(PJSENTORNO* pjsEnt) {

    
    if (pjsEnt == NULL)
        return ERROR_RM;
    pjsEnt->primero = NULL;
    pjsEnt->ultimo = NULL;
    pjsEnt->numPjs = 0;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: destruirPjsEnt

Descripción:
Libera la memoria reservada para personajes de Entorno.

Argumentos de entrada:
1. pjsEnt, puntero que se liberara.

Retorno: 
- OKE, si se ha terminado sin problemas
- ERROR_LM, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS destruirPjsEnt(PJSENTORNO * pjsEnt) {

    NODO_PJ* aux = NULL;


    if (pjsEnt == NULL)
        return ERROR;

    if (esVacioPjsEnt(pjsEnt)) {
        free(pjsEnt);
        return OKE;
    }

    while (!esVacioPjsEnt(pjsEnt)) {
        aux = pjsEnt->ultimo;
        if (pjsEnt->numPjs == 1) {/*Cuando solo queda un nodo.*/
            pjsEnt->numPjs--;
            pjsEnt->primero = NULL;
            pjsEnt->ultimo = NULL;
            destruyeNodoPj(aux);
            free(pjsEnt);
            return OKE;
        }
        if (aux->siguiente == NULL) {/*Extrayendo desde el final.*/
            pjsEnt->numPjs--;
            aux->anterior->siguiente = NULL;
            pjsEnt->ultimo = aux->anterior;
            aux->anterior = NULL;
            destruyeNodoPj(aux);
        }
    }

    return ERROR_LM;
}

/*-----------------------------------------------------------------------------

Nombre: iniNodoPj

Descripción:
Esta función reserva memoria para un nodo del personaje, e inserta en el un
un personaje.

Argumentos de entrada:
1. NODOPj, el nodo que se iniciara.
2. pj, el objeto que se insertara en el nodo.

Retorno: 
- OKE, si se ha terminado sin problemas
- ERROR, si el objeto que recibe la función esta vacío.
- ERROR_RM, si se produce un error al reservar memoria.

-----------------------------------------------------------------------------*/
extern STATUS iniNodoPj(NODO_PJ* nodoPj, PERSONAJE* pj) {

    if (pj == NULL)
        return ERROR;
    
    if (nodoPj == NULL)
        return ERROR_RM;
    nodoPj->pj=pj;
    nodoPj->anterior = NULL;
    nodoPj->siguiente = NULL;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: destruyeNodoPj

Descripción:
Libera la memoria que se reservo para un nodo del personaje.

Argumentos de entrada:
1. nodoPJ, el nodo que se liberara.

Retorno: 
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS destruyeNodoPj(NODO_PJ* nodoPj) {

    if (nodoPj == NULL)
        return ERROR;
    destruyePj(nodoPj->pj);
    free(nodoPj);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: buscarPjsEnt

Descripción:
Recorre el Personajes de Entorno, buscando en el los nodos un personaje que coincida con
el nombre de personaje que recibe.

Argumentos de entrada:
1. pjsEnt, el personajes de Entorno en el que buscara el personaje
2. nombrePj, el nombre del opersonaje que se busca.

Retorno: 
- OKE,   si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS buscarPjsEnt(PJSENTORNO * pjsEnt, NODO_PJ** nodoPj, const char* nombrePj) {

    int i = 0;
    char * nombre = NULL;
    nombre = (char*) malloc(sizeof (char)*100);
    if (pjsEnt == NULL || esVacioPjsEnt(pjsEnt))
        return ERROR;

    *nodoPj = pjsEnt->primero;

    for (i = 0; i < pjsEnt->numPjs; i++) {
        getNombrePj((*nodoPj)->pj, nombre);
        if (strcmp(nombre, nombrePj) == 0) {
            free(nombre);
            return OKE;
        }
        *nodoPj = (*nodoPj)->siguiente;
    }
    
    return ERROR;
}

/*-----------------------------------------------------------------------------

Nombre: pushNodoPj

Descripción:
Inserta un nodo con personaje en el personajes de Entorno.

Argumentos de entrada:
1. pjsEnt, inventario en el que se insertara el objeto.
2. nodoPj, nodo que se insertara.

Retorno: 
- OKE  , si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS pushNodoPj(PJSENTORNO* pjsEnt, NODO_PJ* nodoPj) {

    if (pjsEnt == NULL || nodoPj == NULL)
        return ERROR;
    if (pjsEnt->numPjs == 0) {
        pjsEnt->numPjs++;
        pjsEnt->primero = nodoPj;
        pjsEnt->ultimo = nodoPj;
        return OKE;
    }
    if (pjsEnt->numPjs < MAX_PJS) {
        pjsEnt->numPjs++;
        pjsEnt->ultimo->siguiente = nodoPj;
        nodoPj->anterior = pjsEnt->ultimo;
        pjsEnt->ultimo = nodoPj;
        return OKE;
    }
    return ERROR;
}

/*-----------------------------------------------------------------------------

Nombre: popObjetoInv

Descripción:
Extrae del personajes Entorno un elemento que coincida con el nombre que se le pasa.

Argumentos de entrada:
1. pjsEnt, personajes entorno que se comprobara.
2. nodoPj,ptr en el que se almacenara el nodo extraido.
3. nombrePj,nombre del personaje que se quiere extraer del inventario.

Retorno: 
- OKE, si funciona correctamente.
- ERROR, si es se produce algún error;

-----------------------------------------------------------------------------*/
extern STATUS popNodoPj(PJSENTORNO* PjEnt, NODO_PJ** nodo, char* nombreObj) {

    if (PjEnt == NULL || nodo == NULL)
        return ERROR;
    if (esVacioPjsEnt(PjEnt))
        return ERROR;
    if (buscarPjsEnt(PjEnt, nodo, nombreObj) == ERROR)
        return ERROR;

    if (PjEnt->numPjs == 1) {/*Si solo hay un nodo en el inventario.*/
        PjEnt->numPjs--;
        (*nodo)=PjEnt->primero;
        PjEnt->primero = NULL;
        PjEnt->ultimo = NULL;
        return OKE;
    }

    if ((*nodo)->anterior == NULL) {/*Si es el primer nodo.*/
        PjEnt->numPjs--;
        (*nodo)->siguiente->anterior = NULL;
        PjEnt->primero = (*nodo)->siguiente;
        (*nodo)->siguiente = NULL;
        return OKE;
    }

    if ((*nodo)->siguiente == NULL) {/*Si es el último nodo.*/
        PjEnt->numPjs--;
        (*nodo)->anterior->siguiente = NULL;
        PjEnt->ultimo = (*nodo)->anterior;
        (*nodo)->anterior = NULL;
        return OKE;
    }

    /*Si esta entre dos nodos*/
    if ((*nodo)->anterior != NULL && (*nodo)->siguiente != NULL) {
        PjEnt->numPjs--;
        (*nodo)->anterior->siguiente = (*nodo)->siguiente;
        (*nodo)->siguiente->anterior = (*nodo)->anterior;
        (*nodo)->anterior = NULL;
        (*nodo)->siguiente = NULL;
        return OKE;
    }

    return ERROR;
}

/*-----------------------------------------------------------------------------

Nombre: esVacioPjsEnt

Descripción:
Comprueba si el personajes de Entorno esta vacío.

Argumentos de entrada:
1. ipjsEnt, inventario que se comprobara.

Retorno: 
- VERDADERO, si está vacío.
- FALSO, si contiene algún objeto.
- ERROR, si es NULL;

-----------------------------------------------------------------------------*/
extern BOOL esVacioPjsEnt(PJSENTORNO* pjsEnt) {

    if (pjsEnt == NULL)
        return ERROR;
    if (pjsEnt->numPjs == 0)
        return VERDADERO;
    return FALSO;
}

/*****************************************************************************/

