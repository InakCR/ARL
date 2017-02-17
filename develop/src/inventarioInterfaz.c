/******************************************************************************

Nombre del módulo: inventarioInterfaz.c

Descripción: 
        Funciones para el manejo del panel de stats y el panel de inventarios
 del juego.

Autor: Miguel Angel Gomez-Tavira

Fecha: 25-03-2013

Modulos propios que necesita: 
- interface.h
- inventarioInterfaz.h
- personaje.h
- mundo.h
- tipos.h

Modificaciones: 
[25-03-2013] Creación de fichero y comienzo de implementación del pseudocódigo.
[18-05-2013] Terminadas las funciones:
 *           -pintaInventario
 *           -pintaStats

 ******************************************************************************/

/*=== Cabeceras =============================================================*/
#include "interface.h"
#include "inventarioInterfaz.h"
#include "personaje.h"
#include "tipos.h"
#include "mundo.h"
/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------

Nombre: pintaInventario

Descripción:
 Muestra en el panel de inventarios, el contenido de la mochila del jugador,
asi como los objetos y personajes que se hallan en el inventario.

Argumentos de entrada: 
1. interfaz, se pasa por puntero la interfaz, en la que esta contenida la 
   ventana de la consola.
2. nodo, el nodo donde se encuentra el entorno en el que esta contenido el
   entorno actual.
3. inventario, inventario que almacena los objetos del pj principal.

Retorno: 
-  OKE  , si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS pintaInventario(INTERFAZ* interfaz, NODO_MUNDO* nodo, INVENTARIO* inventario) {

    int i = 0, x = 1, y = 1;
    NODO_INV* aux = NULL;
    NODO_PJ* auxPj = NULL;

    if ((interfaz != NULL) || (inventario != NULL) || (nodo != NULL)) {
        wclear(interfaz->ventana[CINV]);
        wattron(interfaz->ventana[CINV], A_BOLD | A_UNDERLINE);
        mvwprintw(interfaz->ventana[CINV], y, x, "I  Inventario");
        wattroff(interfaz->ventana[CINV], A_BOLD | A_UNDERLINE);
        y++;
        if (inventario->numObjetos > 0 && inventario != NULL) {
            aux = inventario->primero;
            for (i = 0; i < inventario->numObjetos; i++, y++) {
                if (aux != NULL) {
                    if (strlen(aux->obj->nombre) <= 6)
                        mvwprintw(interfaz->ventana[CINV], y, x, "%s\t\t%c", aux->obj->nombre, aux->obj->graph);
                    else
                        mvwprintw(interfaz->ventana[CINV], y, x, "%s\t%c", aux->obj->nombre, aux->obj->graph);
                    aux = aux->siguiente;
                }
            }
            y++;
        } else
            y++;

        wattron(interfaz->ventana[CINV], A_BOLD | A_UNDERLINE);
        mvwprintw(interfaz->ventana[CINV], y, x, "II Objetos");
        wattroff(interfaz->ventana[CINV], A_BOLD | A_UNDERLINE);
        y++;

        if (nodo->ent->numObjEnt > 0 && nodo->ent->invEnt != NULL) {
            aux = nodo->ent->invEnt->primero;
            for (i = 0; i < nodo->ent->numObjEnt; i++, y++) {
                if (aux != NULL) {
                    if (strlen(aux->obj->nombre) <= 6)
                        mvwprintw(interfaz->ventana[CINV], y, x, "%s\t\t%c", aux->obj->nombre, aux->obj->graph);
                    else
                        mvwprintw(interfaz->ventana[CINV], y, x, "%s\t%c", aux->obj->nombre, aux->obj->graph);
                    aux = aux->siguiente;
                }
            }
            y++;
        } else
            y++;

        wattron(interfaz->ventana[CINV], A_BOLD | A_UNDERLINE);
        mvwprintw(interfaz->ventana[CINV], y, x, "III Personajes");
        wattroff(interfaz->ventana[CINV], A_BOLD | A_UNDERLINE);
        y++;
        if (nodo->ent->numPjsEnt > 0 && nodo->ent->pjsEnt != NULL) {

            auxPj = nodo->ent->pjsEnt->primero;
            for (i = 0; i < nodo->ent->numPjsEnt; i++, y++) {
                if (auxPj != NULL) {
                    if (strlen(auxPj->pj->nombre) <= 6)
                        mvwprintw(interfaz->ventana[CINV], y, x, "%s\t\t%c", auxPj->pj->nombre, auxPj->pj->graphPJ);
                    else
                        mvwprintw(interfaz->ventana[CINV], y, x, "%s\t%c", auxPj->pj->nombre, auxPj->pj->graphPJ);
                    auxPj = auxPj->siguiente;
                }
            }
        }
        
        box(interfaz->ventana[CINV], 0, 0);
        update_panels();
        return OKE;
    }
    return ERROR;
}

/*-----------------------------------------------------------------------------

Nombre: pintaStats

Descripción:
 Pinta los stats del personaje.

Argumentos de entrada: 
1. interfaz, se pasa por puntero la interfaz, en la que esta contenida la 
   ventana de los stats.
2. pj, personaje cuyos stats se repreentan.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS pintaStats(INTERFAZ* inter, PERSONAJE* pj) {

    int x = 1, y = 1;

    if (inter == NULL || pj == NULL)
        return ERROR;

    wclear(inter->ventana[CSTATS]);
    
    mvwprintw(inter->ventana[CSTATS], y, x, "Vitalidad: %d // %d", pj->vit, pj->vitTot);

    y += 2;

    mvwprintw(inter->ventana[CSTATS], y, x, "Fuerza   : %d", pj->fuerza);

    y += 2;

    mvwprintw(inter->ventana[CSTATS], y, x, "Defensa  : %d", pj->defensa);
    
    box(inter->ventana[CSTATS],0,0);

    update_panels();

    return OKE;
}
/*****************************************************************************/
