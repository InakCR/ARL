/******************************************************************************

Nombre del módulo: inventario.c

Descripción: 
        Funciones para el manejo de datos de la consola, tanto para capturar 
información que el usuario introducirá por medio de la consola, como para
mostrar información que el programa le transmitirá al usuario.

Autor: Diego Chicote

Fecha: 25-02-2013

Modulos propios que necesita: 
- inventario.h

Modificaciones: 
[25-02-2013] Creación de fichero y comienzo de implementación del pseudocódigo.
[25-02-2013] Terminadas las funciones:
 *           -iniInventario
 *           -destruirInventario
 *           -buscarEnInventario
 *           -annadirObjeto
[13-04-2013] Miguel Gomez-Tavira añade las funciones:
 *           -iniNodoInv
 *           -destruyeNodoInv
 *           -annadirObjeto : es ahora pushNodoInv
 *           -popNodoInv
 *           -esVacioInv
[22-04-2013] Miguel Gomez-Tavira añade las funciones:
 *           -copiaInventario
 *           -copiaNodoInventario   
 [01-05-2013] Iñaki Cadalso corrige comentarios de funciones
 * 

Mejoras pendientes: 
- Pruebas de funciones.
- Correcion de comentarios, en cabecera y fuente.

 ******************************************************************************/


/*=== Cabeceras =============================================================*/
#include "inventario.h"

/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------

Nombre: iniInventario

Descripción:
Reserva memoria para el inventario.

Argumentos de entrada:
1. inv, puntero al inventario.

Retorno: 
-  OKE, si se ha terminado sin problemas
- ERROR_RM, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS iniInventario(INVENTARIO* inv) {

   
    if (inv == NULL)
        return ERROR_RM;
    inv->primero = NULL;
    inv->ultimo = NULL;
    inv->numObjetos = 0;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: copiaInventario

Descripción:
Esta función reserva memoria para un nodo del inventario, e inserta en el un
un objeto.

Argumentos de entrada:
1. NODO_INV, el nodo que se iniciara.
2. obj, el objeto que se insertara en el nodo.

Retorno: 
- OKE, si se ha terminado sin problemas
- ERROR, si el objeto que recibe la función esta vacío.
- ERROR_RM, si se produce un error al reservar memoria.

-----------------------------------------------------------------------------*/
extern STATUS copiaInventario(INVENTARIO* dst, const INVENTARIO* org) {

    NODO_INV* d   = NULL;
    NODO_INV* aux = NULL;
    
    if (dst == NULL || org == NULL)
        return ERROR;
    aux = org->primero;
    while(aux->siguiente != NULL){
        if(copiaNodoInventario(d,aux) != OKE){
            destruirInventario(dst);
            return ERROR_RM;
        }
        aux = aux->siguiente;
    }
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: destruirInventario

Descripción:
Libera la memoria reservada para el inventario.

Argumentos de entrada:
1. inventario, puntero al inventario que se liberara.

Retorno: 
- OKE, si se ha terminado sin problemas
- ERROR_LM, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS destruirInventario(INVENTARIO * inv) {

    NODO_INV* aux = NULL;


    if (inv == NULL)
        return ERROR;

    if (esVacioInv(inv)) {
        free(inv);
        return OKE;
    }

    while (!esVacioInv(inv)) {
        aux = inv->ultimo;
        if (inv->numObjetos == 1) {/*Cuando solo queda un nodo.*/
            inv->numObjetos--;
            inv->primero = NULL;
            inv->ultimo = NULL;
            destruyeNodoInv(aux);
            free(inv);
            return OKE;
        }
        if (aux->siguiente == NULL) {/*Extrayendo desde el final.*/
            inv->numObjetos--;
            aux->anterior->siguiente = NULL;
            inv->ultimo = aux->anterior;
            aux->anterior = NULL;
            destruyeNodoInv(aux);
        }
    }

    return ERROR_LM;
}

/*-----------------------------------------------------------------------------

Nombre: iniNodoInv

Descripción:
Esta función reserva memoria para un nodo del inventario, e inserta en el un
un objeto.

Argumentos de entrada:
1. NODO_INV, el nodo que se iniciara.
2. obj, el objeto que se insertara en el nodo.

Retorno: 
- OKE, si se ha terminado sin problemas
- ERROR, si el objeto que recibe la función esta vacío.
- ERROR_RM, si se produce un error al reservar memoria.

-----------------------------------------------------------------------------*/
extern STATUS iniNodoInv(NODO_INV* nodo, OBJETO* obj) {

    if (obj == NULL)
        return ERROR;
    
    if (nodo == NULL)
        return ERROR_RM;
    nodo->obj=obj;
    nodo->anterior = NULL;
    nodo->siguiente = NULL;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: copiaNodoInventario

Descripción:
Inserta un nodo con objeto en el inventario.

Argumentos de entrada:
1. inv, inventario en el que se insertara el objeto.
2. nodo, nodo que se insertara en el inventario.

Retorno: 
- OKE  , si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS copiaNodoInventario(NODO_INV* dst, const NODO_INV* org) {

    if (org == NULL)
        return ERROR;
    if (iniNodoInv(dst, org->obj) != OKE)
        return ERROR;
    dst->anterior = org->anterior;
    dst->siguiente= org->siguiente;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: destruyeNodoInv

Descripción:
Libera la memoria que se reservo para un nodo del inventario.

Argumentos de entrada:
1. nodo, el nodo que se liberara.

Retorno: 
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS destruyeNodoInv(NODO_INV* nodo) {

    if (nodo == NULL)
        return ERROR;
    destruyeObj(nodo->obj);
    free(nodo);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: buscarEnInventario

Descripción:
Recorre el inventario, buscando en el los nodos un objeto que coincida con
el nombre de objeto que recibe.

Argumentos de entrada:
1. inv, el inventario en el que buscara el objeto.
2. nombreObj, el nombre del objeto que se busca.

Retorno: 
- OKE,   si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS buscarEnInventario(INVENTARIO * inv, NODO_INV** nodo, const char* nombreObj) {

    int i = 0;
    char * nombre = NULL;

    if (inv == NULL || esVacioInv(inv))
        return ERROR;

    nombre = (char*) malloc(sizeof (MAX_NOM_OBJ));
    *nodo = inv->primero;

    for (i = 0; i < inv->numObjetos; i++) {
        getNombreObj((*nodo)->obj, nombre);
        if (strcmp(nombre, nombreObj) == 0) {
            free(nombre);
            return OKE;
        }
        *nodo = (*nodo)->siguiente;
    }
    free(nombre);
    return ERROR;
}

/*-----------------------------------------------------------------------------

Nombre: pushNodoInv

Descripción:
Inserta un nodo con objeto en el inventario.

Argumentos de entrada:
1. inv, inventario en el que se insertara el objeto.
2. nodo, nodo que se insertara en el inventario.

Retorno: 
- OKE  , si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS pushNodoInv(INVENTARIO* inv, NODO_INV* nodo) {

    if (inv == NULL || nodo == NULL)
        return ERROR;
    if (inv->numObjetos == 0) {
        inv->numObjetos++;
        inv->primero = nodo;
        inv->ultimo = nodo;
        return OKE;
    }
    if (inv->numObjetos < MAX_INV) {
        inv->numObjetos++;
        inv->ultimo->siguiente = nodo;
        nodo->anterior = inv->ultimo;
        inv->ultimo = nodo;
        return OKE;
    }
    return ERROR;
}

/*-----------------------------------------------------------------------------

Nombre: popObjetoInv

Descripción:
Extrae del inventario un elemento que coincida con el nombre que se le pasa.

Argumentos de entrada:
1. inv, inventario que se comprobara.
2. nodo,ptr en el que se almacenara el nodo extraido.
3. nombreObj,nombre del objeto que se quiere extraer del inventario.

Retorno: 
- OKE, si funciona correctamente.
- ERROR, si es se produce algún error;

-----------------------------------------------------------------------------*/
extern STATUS popNodoInv(INVENTARIO* inv, NODO_INV** nodo, char* nombreObj) {

    if (inv == NULL || nodo == NULL)
        return ERROR;
    if (esVacioInv(inv))
        return ERROR;
    if (buscarEnInventario(inv, nodo, nombreObj) == ERROR)
        return ERROR;

    if (inv->numObjetos == 1) {/*Si solo hay un nodo en el inventario.*/
        inv->numObjetos--;
        (*nodo)=inv->primero;
        inv->primero = NULL;
        inv->ultimo = NULL;
        return OKE;
    }

    if ((*nodo)->anterior == NULL) {/*Si es el primer nodo.*/
        inv->numObjetos--;
        (*nodo)->siguiente->anterior = NULL;
        inv->primero = (*nodo)->siguiente;
        (*nodo)->siguiente = NULL;
        return OKE;
    }

    if ((*nodo)->siguiente == NULL) {/*Si es el último nodo.*/
        inv->numObjetos--;
        (*nodo)->anterior->siguiente = NULL;
        inv->ultimo = (*nodo)->anterior;
        (*nodo)->anterior = NULL;
        return OKE;
    }

    /*Si esta entre dos nodos*/
    if ((*nodo)->anterior != NULL && (*nodo)->siguiente != NULL) {
        inv->numObjetos--;
        (*nodo)->anterior->siguiente = (*nodo)->siguiente;
        (*nodo)->siguiente->anterior = (*nodo)->anterior;
        (*nodo)->anterior = NULL;
        (*nodo)->siguiente = NULL;
        return OKE;
    }

    return ERROR;
}

/*-----------------------------------------------------------------------------

Nombre: esVacioInv

Descripción:
Comprueba si el inventario esta vacío.

Argumentos de entrada:
1. inv, inventario que se comprobara.

Retorno: 
- VERDADERO, si está vacío.
- FALSO, si contiene algún objeto.
- ERROR, si es NULL;

-----------------------------------------------------------------------------*/
extern BOOL esVacioInv(INVENTARIO* inv) {

    if (inv == NULL)
        return ERROR;
    if (inv->numObjetos == 0)
        return VERDADERO;
    return FALSO;
}

/*****************************************************************************/