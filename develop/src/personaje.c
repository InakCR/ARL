/******************************************************************************

Nombre del módulo: personaje.c

Descripción:
        Funciones para el manejo de los personajes que intervienen en el juego,
 tanto en personaje jugador(PJ), como aquellos controlados por la inteligencia
 artificial(PNJ).

Autor: Diego Chicote

Fecha: 19-03-2013

Módulos propios que necesita:
- personaje.h

Notas: Faltan funciones por implementar; se irán añadiendo a medida que sean
       necesarias.

Modificaciones:
[19-03-2013] Creación de fichero y comienzo de implementación del pseudocódigo.
[19-03-2013] Terminadas las funciones:
 *           -iniPj
 *           -destruyePj
 *           -getIDPj
 *           -getColPj
 *           -setColPj
 *           -getFilaPj
 *           -setFilaPj
 *           -getNombrePj
 *           -setNombrePj
 *           -getDescPj
 *           -setDescPj
 *           -getGraphPj
 *           -setGraphPj
 *           -getInventarioPj
 *           -setInventarioPj
 *           -getVitalidadPj
 *           -setVitalidadPj
 *           -getFuerzaPj
 *           -setFuerzaPj
 *           -getDefensaPj
 *           -setDefensaPj
 *           -getInteractuarPj
 *           -setInteractuarPj
 *           -getAtacablePj
 *           -setAtacablePj
[14-04-2013]Miguel Gomez-Tavira comenta las funciones.
[14-04-2013]Añadidas la funciones:
 *           -setIDPJ
 *           -getVitTotPj
 *           -setVitTotPj
 *           -copiaPj
[27-04-2013]Iñaki añade la funciones:
 *           -getObjetoInv
 *
 [01-05-2013] Iñaki Cadalso corrige comentarios de funciones
 * 
 [16-05-2013] Iñaki Cadalso cambia funciones con tipos *int a int ;
 *           -creaPersonaje, para el personaje principal.
 * 
Mejoras pendientes:
- Pruebas de funciones.
- Correcion de comentarios, en cabecera y fuente.

 ******************************************************************************/

/*=== Cabeceras =============================================================*/
#include "personaje.h"


/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------

Nombre: iniPj

Descripción:
  Reserva memoria para personaje y sus elementos.

Argumentos de entrada:
1. pj, puntero a personaje.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR_RM, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS iniPj(PERSONAJE* pj) {



    if (pj == NULL)
        return ERROR_RM;

    pj->id = (char*) malloc(sizeof (MAX_ID));
    if (pj->id == NULL) {
        free(pj);
        return ERROR_RM;
    }
    pj->nombre = (char*) malloc(sizeof (MAX_NOM_PJ));
    if (pj->nombre == NULL) {
        free(pj->id);
        free(pj);
        return ERROR_RM;
    }
    /*
    pj->descripcion = (char*) malloc(sizeof (MAX_DES_PJ));
    if (pj->descripcion == NULL) {
        free(pj->nombre);
        free(pj->id);
        free(pj);
        return ERROR_RM;
    }
     */
    pj->inv = (INVENTARIO*) malloc(sizeof (INVENTARIO));
    if (pj->inv == NULL) {
        free(pj->descripcion);
        free(pj->nombre);
        free(pj->id);
        free(pj);
        return ERROR_RM;
    }
    return OKE;
}

extern STATUS creaPersonaje(PERSONAJE* pj) {
    if (pj == NULL)
        return ERROR;
    setIdPj(pj, "ARL");
    setFilaPj(pj, 2);
    setColPj(pj, 4);
    setNombrePj(pj, "ARL");
    setDescPj(pj, "Este soy yo, en menuda me han metido...");
    setGraphPj(pj, '8');
    setVitTotPj(pj, 10);
    setVitPj(pj, 10);
    setFuerzaPj(pj, 5);
    setDefensaPj(pj, 5);
    setAtacablePj(pj, FALSO);
    setInteractuarPj(pj, FALSO);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: copiaPj

Descripción:
  Copia un personaje en otro.

Argumentos de entrada:
1. dst, puntero a personaje, donde se copiara.
2. org, puntero a personaje, del cual se copiara.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se el puntero que recibe la función apunta a NULL.
-  ERROR_LM, si se produce algún error liberando memoria.

-----------------------------------------------------------------------------*/
extern STATUS copiaPj(PERSONAJE* dst, const PERSONAJE* org) {

    if (dst == NULL || org == NULL)
        return ERROR;
    strcpy(dst->id, org->id);
    dst->fila = org->fila;
    dst->columna = org->columna;
    strcpy(dst->nombre, org->nombre);
    strcpy(dst->descripcion, org->descripcion);
    dst->graphPJ = org->graphPJ;
    dst->inv = org->inv;
    dst->vit = org->vit;
    dst->vitTot = org->vitTot;
    dst->fuerza = org->fuerza;
    dst-> defensa = org->defensa;
    dst->interactuar = org->interactuar;
    dst->atacable = org->atacable;
    return OKE;

}

/*-----------------------------------------------------------------------------

Nombre: destruyePj

Descripción:
  Libera el espacio reservado para personaje.

Argumentos de entrada:
1. pj, puntero a personaje.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se el puntero que recibe la función apunta a NULL.
-  ERROR_LM, si se produce algún error liberando memoria.

-----------------------------------------------------------------------------*/
extern STATUS destruyePj(PERSONAJE * pj) {

    if (pj == NULL)
        return ERROR;
    if (destruirInventario(pj->inv) == ERROR_LM)
        return ERROR_LM;
    free(pj->descripcion);
    free(pj->nombre);
    free(pj->id);
    free(pj);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getIDPj

Descripción:
  Devuelve la id del pj.

Argumentos de entrada:
1. pj, se pasa por ptr el pj.
2. id, la id del pj.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getIDPj(const PERSONAJE * pj, ID id) {

    if (pj == NULL)
        return ERROR;
    strcpy(id, pj->id);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setIdPj

Descripción:
  Modifica el valor del atributo id del personaje.

Argumentos de entrada:
1. pj, el personaje asado por ptr.
2. id, la id que recibira el pj

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si pj o id llegan vacíos.
-  ERROR_FMT, si el tamaño de id es mayor del permitido.

-----------------------------------------------------------------------------*/
extern STATUS setIdPj(PERSONAJE* pj, const ID id) {

    if (pj == NULL || id == NULL)
        return ERROR;
    if (strlen(id) + 1 > MAX_ID)
        return ERROR_FMT;
    strcpy(pj->id, id);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getColPj

Descripción:
  Devuelve la columna en la que se situa el pj.

Argumentos de entrada:
1. pj, personaje pasado por puntero.
2. col, columna en la que está localizado el personaje.
Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getColPj(const PERSONAJE * pj, int* col) {

    if (pj == NULL)
        return ERROR;
    *col = pj->columna;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setColPj

Descripción:
  Modifica la columna en la que se encuentra el pj en el mapa.

Argumentos de entrada:
1. pj, ptr al personaje.
2. col, columna a la que se movera el personaje.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setColPj(PERSONAJE * pj, const int col) {

    if (pj == NULL)
        return ERROR;
    pj->columna = col;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getFilaPj

Descripción:
  Devuelve la fila en la que se situa el personaje en el mapa.

Argumentos de entrada:
1. pj, el personaje pasado por ptr.
2. fila. la fila del mapa en la que se situa el personaje.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getFilaPj(const PERSONAJE * pj, int* fila) {

    if (pj == NULL)
        return ERROR;
    *fila = pj->fila;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setFilaPj

Descripción:
  Modifica la fila en la que se encuentra el personaje en el mapa.

Argumentos de entrada:
1. pj, personaje pasado por ptr.
2. fila, fila en la que se encuentra el personaje.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setFilaPj(PERSONAJE * pj, const int fila) {

    if (pj == NULL)
        return ERROR;
    pj->fila = fila;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getNombrePj

Descripción:
  Devuelve el nombre del pj.

Argumentos de entrada:
1. pj, personaje pasado por ptr.
2. nombrePj, nombre del pj.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getNombrePj(const PERSONAJE * pj, char* nombrePj) {

    if (pj == NULL)
        return ERROR;
    strcpy(nombrePj, pj->nombre);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setNombrePj

Descripción:
  Modifica el nombre del personaje.

Argumentos de entrada:
1. pj, el personaje pasado por ptr.
2. nombrePj, el nombre que tomara el personaje.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si alguno de los datos que recibe la función está vacío.
- ERROR_FMT, si el nombrePj, excede el máximo de los carácteres permitidos.

-----------------------------------------------------------------------------*/
extern STATUS setNombrePj(PERSONAJE * pj, const char * nombrePj) {

    if (pj == NULL || nombrePj == NULL)
        return ERROR;
    if (strlen(nombrePj) + 1 > MAX_NOM_PJ)
        return ERROR_FMT;
    strcpy(pj->nombre, nombrePj);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getDescPj

Descripción:
  Devuelve la descripción del personaje.

Argumentos de entrada:
1. pj, el personaje pasado por ptr.
2. descPj, descripción del personaje.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getDescPj(const PERSONAJE * pj, char* descPj) {

    if (pj == NULL)
        return ERROR;
    strcpy(descPj, pj->descripcion);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setDescPj

Descripción:
  Modifica la descripción del personaje.

Argumentos de entrada:
1. pj, personaje pasado por ptr.
2. descPj, descripción que tomara el personaje.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si alguna de las variables que recibe la función está vacía.
- ERROR_FMT, si la descPj tiene mas carácteres de los permitidos.

-----------------------------------------------------------------------------*/
extern STATUS setDescPj(PERSONAJE * pj, const char * descPj) {

    if (pj == NULL || descPj == NULL)
        return ERROR;
    if (strlen(descPj) + 1 > MAX_DES_PJ)
        return ERROR_FMT;

    pj->descripcion = strdup(descPj);
   


    return OKE;


}

/*-----------------------------------------------------------------------------

Nombre: getGraphPj

Descripción:
  Devuelve el carácter que representa al pj en el mapa.

Argumentos de entrada:
1. pj, el personaje pasado por puntero.
2. graphPj, el carácter que representa al pj en el mapa.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getGraphPj(const PERSONAJE * pj, char* graphPj) {

    if (pj == NULL)
        return ERROR;
    *graphPj = pj->graphPJ;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setGraphPj

Descripción:
  Modifica el carácter que representa al personaje en el mapa.

Argumentos de entrada:
1. pj, personaje pasado por ptr.
2. graphPj, carácter que representa al pj en el mapa.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setGraphPj(PERSONAJE * pj, const char graphPj) {

    if (pj == NULL)
        return ERROR;
    pj->graphPJ = graphPj;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getInventarioPj

Descripción:
  Devuelve un ptr al inventario del personaje.

Argumentos de entrada:
1. pj, personaje pasado por puntero.
2. inv, inventario del personaje.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getInventarioPj(const PERSONAJE * pj, INVENTARIO** invPj) {

    if (pj == NULL)
        return ERROR;
    *invPj = pj->inv;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setInventarioPj

Descripción:
  Asigna un inventario al personaje.

Argumentos de entrada:
1. pj, personaje pasado por ptr.
2. invPj, inventario que recibirá el personaje.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setInventarioPj(PERSONAJE * pj, INVENTARIO * invPj) {

    if (pj == NULL || invPj == NULL)
        return ERROR;
    pj->inv = invPj;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getObjetoInv

Descripción:
  Busca el objeto en el inventari odel pj

Argumentos de entrada:
1. pj, personaje pasado por ptr.
2. nom, nombre del objeto.
Retorno:
- OBJETO*, si se ha encontrado
- NULL, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
OBJETO * getObjetoInv(const PERSONAJE * pj, char * nom) {
    NODO_INV* nodoINV = NULL;
    
    if (pj != NULL) {
        if(buscarEnInventario(pj->inv, &nodoINV, nom)==ERROR)
                return NULL;
        return nodoINV->obj;
    }
    return NULL;
}

/*-----------------------------------------------------------------------------

Nombre: getVitPj

Descripción:
  Devuelve la vitalidad actual del personaje.

Argumentos de entrada:
1. pj, personaje pasado por ptr.
2. vit, vitalidad actual del pj.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getVitPj(const PERSONAJE * pj,int* vit) {

    if (pj == NULL)
        return ERROR;
    *vit = pj->vit;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setVitPj

Descripción:
  Modifica la vitalidad actual del personaje.

Argumentos de entrada:
1. pj, personaje pasado por ptr.
2. vit, vitalidad actual del personaje.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setVitPj(PERSONAJE * pj, const int vit) {

    if (pj == NULL)
        return ERROR;
    pj->vit = vit;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getVitTotPj

Descripción:
  Devuelve la vitalidad total actual del personaje.

Argumentos de entrada:
1. pj, personaje pasado por ptr.
2. vit, vitalidad total del pj.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getVitTotPj(const PERSONAJE * pj, int* vitTot) {

    if (pj == NULL)
        return ERROR;
    *vitTot = pj->vitTot;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setVitTotPj

Descripción:
  Modifica la vitalidad total actual del personaje.

Argumentos de entrada:
1. pj, personaje pasado por ptr.
2. vit, vitalidad total del personaje.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setVitTotPj(PERSONAJE * pj, const int vitTot) {

    if (pj == NULL)
        return ERROR;
    pj->vitTot = vitTot;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getFuerzaPj

Descripción:
  Devuelve la fuerza del personaje.

Argumentos de entrada:
1. pj, personaje pasado por ptr.
2. fza, valor del atributo fuerza del personaje.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getFuerzaPj(const PERSONAJE * pj, int* fza) {

    if (pj == NULL)
        return ERROR;
    *fza = pj->fuerza;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setFuerzaPj

Descripción:
  Modifica la fuerza del personaje.

Argumentos de entrada:
1. pj, personaje pasado por ptr.
2. fza, valor del atributo fuerza del personaje.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setFuerzaPj(PERSONAJE * pj, const int fza) {

    if (pj == NULL)
        return ERROR;
    pj->fuerza = fza;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getDefensaPj

Descripción:
  Devuelve el valor del atributo defensa del personaje.

Argumentos de entrada:
1. pj, personaje pasado por puntero.
2. def, valor del atributo defensa del personaje.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getDefensaPj(const PERSONAJE * pj, int* def) {

    if (pj == NULL)
        return ERROR;
    *def = pj->defensa;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setDefensaPj

Descripción:
  Modifica el valor del atributo defensa del jugador.

Argumentos de entrada:
1. pj, el personaje pasado por puntero.
2. def, valor del atributo defensa.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setDefensaPj(PERSONAJE * pj, const int def) {

    if (pj == NULL)
        return ERROR;
    pj->defensa = def;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getInteractuarPj

Descripción:
  Devuelve se puede entablar conversación con el personaje.

Argumentos de entrada:
1. pj, el personaje pasado por ptr.
2. interactuar, atributo que define si se uede hablar con el personaje.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getInteractuarPj(const PERSONAJE * pj, BOOL* interactuar) {

    if (pj == NULL)
        return ERROR;
    *interactuar = pj->interactuar;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setInteractuarPj

Descripción:
  Modifica la capacidad de interactuar del personaje.

Argumentos de entrada:
1. pj, personaje pasado por interfaz.
2. interactuar, atributo que define si se uede hablar con el personaje.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setInteractuarPj(PERSONAJE * pj, const BOOL interactuar) {

    if (pj == NULL)
        return ERROR;
    pj->interactuar = interactuar;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getAtacablePj

Descripción:
  Devuelve si se puede combatir con el pj.

Argumentos de entrada:
1. pj, el personaje pasado por ptr.
2. atacable, atributo del pj que determina si se puede combatir contra el.

Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getAtacablePj(const PERSONAJE * pj, BOOL* atacable) {

    if (pj == NULL)
        return ERROR;
    *atacable = pj->atacable;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setAtacablePj

Descripción:
  Modifica el atributo que determina si se puede atacar al personaje.

Argumentos de entrada:
1. pj, el personaje pasado por ptr.
2. atacable, atributo del pj que determina si se puede combatir contra el.
Retorno:
- OKE, si se ha terminado sin problemas
- ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setAtacablePj(PERSONAJE * pj, const BOOL atacable) {

    if (pj == NULL)
        return ERROR;
    pj->atacable = atacable;
    return OKE;
}

/*****************************************************************************/
