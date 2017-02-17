/******************************************************************************

Nombre del m�dulo: seleccion.c

Descripci�n:
Funciones para la seleccion de las correctas funciones de acciones,


Autor: I�aki Cadalso

Fecha: 14-03-2013

Modulos propios que necesita:
- seleccion.h
- acciones.h

Modificaciones:
[14-03-2013] Pseudoc�digo de movimiento en SeleccionInmediata
[28-03-2013] Modificacion de las funciones:
 *           -seleccionAccionInmediata
 *             cambio a codigo funcional.
[6-04-2013] funciones terminadas:
 *           -seleccionAccion
[6-04-2013] Modificacion de las funciones:
 *           -Cambio de argumentos recibidos en seleccion inmediata
 *           -Cambio de argumentos recibidos en Validacion de complemento
 *           -Inicializaciones
 [27-04-2013] Modificacion de las funciones:
 *            -Cambio de argumentos recibidos en seleccion inmediata,
 *              recibe tambien el nodo de mundo.

Mejoras pendientes:
- 


 ******************************************************************************/


/*=== Cabeceras =============================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "seleccion.h"
#include "consola.h"
#include "mapa.h"
#include "mundo.h"
#include "inventarioInterfaz.h"

/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------

Nombre: seleccionAccionInmediata

Descripción:
        Gestiona el movimiento sobre el entorno.

Argumentos de entrada:
1. nmundo, recibe un nodo de entorno por puntero.
2. pnj, personaje principal.
3. inter, interfaz a modificar.
4. acc, valor entero de la tecla de movimiento.


Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS seleccionAccionInmediata(NODO_MUNDO** nmundo, PERSONAJE* pnj, INTERFAZ * inter, int acc) {

    MAPA* mapa = NULL;
    INVENTARIO* inv = NULL;
    int x, y, t, z;
    char *c = "No te puedes mover en esa direccion";
    char gh = ' ', gh2 = '<', gh3 = '>';
    char* ghpj = NULL;

    ghpj = (char*) malloc(sizeof (char)*10);

    if (nmundo == NULL)
        return ERROR;

    getFilaPj(pnj, &y);
    getColPj(pnj, &x);
    getMapaEnt((*nmundo)->ent, &mapa);
    getGraphPj(pnj, ghpj);
    getInventarioPj(pnj, &inv);


    switch (acc) {

        case(KEY_UP):
            y--;
            if (compareGrahMap(mapa, gh, x, y) == FALSO) {
                if (compareGrahMap(mapa, gh3, x, y) != FALSO) {
                    y++;
                    modGrahMap(mapa, gh, x, y);
                    *nmundo = (*nmundo)->siguiente;
                    getMapaEnt((*nmundo)->ent, &mapa);
                    setColPj(pnj, mapa->salCol);
                    setFilaPj(pnj, mapa->salFil);
                    modGrahMap(mapa, *ghpj, mapa->salCol, mapa->salFil);
                    pintaInventario(inter, &(**nmundo), inv);
                    pintaMapa(inter, mapa);
                    c = "Has avanzado de entorno";
                }
                if (compareGrahMap(mapa, gh2, x, y) != FALSO) {
                    y++;
                    modGrahMap(mapa, gh, x, y);
                    *nmundo = (*nmundo)->anterior;
                    getMapaEnt((*nmundo)->ent, &mapa);
                    setColPj(pnj, mapa->enCol);
                    setFilaPj(pnj, mapa->enFil);
                    modGrahMap(mapa, *ghpj, mapa->enCol, mapa->enFil);
                    pintaInventario(inter, &(**nmundo), inv);
                    pintaMapa(inter, mapa);
                    c = "Has retrocedido de entorno";
                }


                escribeConsola(inter, c);
            } else {
                z = y;
                z++;
                modGrahMap(mapa, gh, x, z);
                setFilaPj(pnj, y);
                modGrahMap(mapa, *ghpj, x, y);
                pintaMapa(inter, mapa);
            }
            break;
        case(KEY_DOWN):
            y++;
            if (compareGrahMap(mapa, gh, x, y) == FALSO) {
                if (compareGrahMap(mapa, gh3, x, y) != FALSO) {
                    y--;
                    modGrahMap(mapa, gh, x, y);
                    *nmundo = (*nmundo)->siguiente;
                    getMapaEnt((*nmundo)->ent, &mapa);
                    setColPj(pnj, mapa->salCol);
                    setFilaPj(pnj, mapa->salFil);
                    modGrahMap(mapa, *ghpj, mapa->salCol, mapa->salFil);
                    pintaInventario(inter, &(**nmundo), inv);
                    pintaMapa(inter, mapa);
                    c = "Has avanzado de entorno";
                }
                if (compareGrahMap(mapa, gh2, x, y) != FALSO) {
                    y--;
                    modGrahMap(mapa, gh, x, y);
                    *nmundo = (*nmundo)->anterior;
                    getMapaEnt((*nmundo)->ent, &mapa);
                    setColPj(pnj, mapa->enCol);
                    setFilaPj(pnj, mapa->enFil);
                    modGrahMap(mapa, *ghpj, mapa->enCol, mapa->enFil);
                    pintaInventario(inter, &(**nmundo), inv);
                    pintaMapa(inter, mapa);
                    c = "Has retrocedido de entorno";
                }


                escribeConsola(inter, c);
            } else {
                z = y;
                z--;
                modGrahMap(mapa, gh, x, z);
                setFilaPj(pnj, y);
                modGrahMap(mapa, *ghpj, x, y);
                pintaMapa(inter, mapa);
            }
            break;
        case(KEY_LEFT):
            x--;
            if (compareGrahMap(mapa, gh, x, y) == FALSO) {
                if (compareGrahMap(mapa, gh3, x, y) != FALSO) {
                    x++;
                    modGrahMap(mapa, gh, x, y);
                    *nmundo = (*nmundo)->siguiente;
                    getMapaEnt((*nmundo)->ent, &mapa);
                    setColPj(pnj, mapa->salCol);
                    setFilaPj(pnj, mapa->salFil);
                    modGrahMap(mapa, *ghpj, mapa->salCol, mapa->salFil);
                    pintaInventario(inter, &(**nmundo), inv);
                    pintaMapa(inter, mapa);
                    c = "Has avanzado de entorno";
                }
                if (compareGrahMap(mapa, gh2, x, y) != FALSO) {
                    x++;
                    modGrahMap(mapa, gh, x, y);
                    *nmundo = (*nmundo)->anterior;
                    getMapaEnt((*nmundo)->ent, &mapa);
                    setColPj(pnj, mapa->enCol);
                    setFilaPj(pnj, mapa->enFil);
                    modGrahMap(mapa, *ghpj, mapa->enCol, mapa->enFil);
                    pintaInventario(inter, &(**nmundo), inv);
                    pintaMapa(inter, mapa);
                    c = "Has retrocedido de entorno";
                }


                escribeConsola(inter, c);
            } else {

                t = x;
                t++;
                modGrahMap(mapa, gh, t, y);
                setColPj(pnj, x);
                modGrahMap(mapa, *ghpj, x, y);
                pintaMapa(inter, mapa);
            }
            break;
        case(KEY_RIGHT):
            x++;
            if (compareGrahMap(mapa, gh, x, y) == FALSO) {
                if (compareGrahMap(mapa, gh3, x, y) != FALSO) {
                    x--;
                    modGrahMap(mapa, gh, x, y);
                    *nmundo = (*nmundo)->siguiente;
                    getMapaEnt((*nmundo)->ent, &mapa);
                    setColPj(pnj, mapa->salCol);
                    setFilaPj(pnj, mapa->salFil);
                    modGrahMap(mapa, *ghpj, mapa->salCol, mapa->salFil);
                    pintaInventario(inter, &(**nmundo), inv);
                    pintaMapa(inter, mapa);
                    c = "Has avanzado de entorno";
                }
                if (compareGrahMap(mapa, gh2, x, y) != FALSO) {
                    x--;
                    modGrahMap(mapa, gh, x, y);
                    *nmundo = (*nmundo)->anterior;
                    getMapaEnt((*nmundo)->ent, &mapa);
                    setColPj(pnj, mapa->enCol);
                    setFilaPj(pnj, mapa->enFil);
                    modGrahMap(mapa, *ghpj, mapa->enCol, mapa->enFil);
                    pintaInventario(inter, &(**nmundo), inv);
                    pintaMapa(inter, mapa);
                    c = "Has retrocedido de entorno";
                }



                escribeConsola(inter, c);
            } else {
                t = x;
                t--;
                modGrahMap(mapa, gh, t, y);
                setColPj(pnj, x);
                modGrahMap(mapa, *ghpj, x, y);
                pintaMapa(inter, mapa);
            }
            break;
        default:

            escribeConsola(inter, "No se reconoce el comando.");
            break;
    }
    refresh();
    free(ghpj);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: seleccionAccion

Descripción:
        Gestiona las acciones  sobre el entorno.

Argumentos de entrada:
1. nmundo, Nodo donde se encuentra entorno a modificar.
2. pnj, personaje principal.
3. inter, interfaz a modificar.
4. cad, accion.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS seleccionAccion(NODO_MUNDO* nmundo, PERSONAJE *pnj, INTERFAZ *inter, char *cad) {
    MAPA* map = NULL;
    OBJETO * obj = NULL;
    PERSONAJE *pj = NULL;
    INVENTARIO* inv = NULL;
    char *cop = NULL;

    cop = tratamientoCadena(&cad);

    if (cop == NULL) {
        escribeConsola(inter, "No te entiendo...");
        return ERROR;
    }
    pj = getPersonajeEnt(nmundo->ent, cop);
    obj = getObjetoEnt(nmundo->ent, cop);
    getInventarioPj(pnj, &inv);
    getMapaEnt(nmundo->ent, &map);

    if (obj == NULL)
        obj = getObjetoInv(pnj, cop);

    if (strcmp(cad, "HABLAR") == 0) {
        if(pj==NULL)
            return ERROR;
        hablar(nmundo->ent, inter, pj, pnj);
        if (nmundo->siguiente == NULL) {
            if (compruebaNivel(pnj) == VERDADERO) {
                nivelFinal(nmundo->ent, inter);
                return OKE;
            }
            escribeConsola(inter, "No tienes suficiente nivel");
        }
        return OKE;

    } else if (strcmp(cad, "USAR") == 0) {

        escribeConsola(inter, usar(nmundo->ent, obj, pnj));
        pintaInventario(inter, nmundo, inv);
        pintaStats(inter, pnj);

        return OKE;
    } else if (strcmp(cad, "COGER") == 0) {
        escribeConsola(inter, coger(nmundo->ent, pnj, obj));
        pintaMapa(inter, map);
        pintaInventario(inter, nmundo, inv);
        return OKE;

    } else if (strcmp(cad, "ATACAR") == 0) {

        escribeConsola(inter, atacar(nmundo->ent, inter, pnj, pj));
        pintaMapa(inter, map);
        pintaInventario(inter, nmundo, inv);
        pintaStats(inter, pnj);

        return OKE;
    } else if (strcmp(cad, "EXAMINAR") == 0) {

        escribeConsola(inter, (examinar(nmundo->ent, obj, pj)));


        return OKE;

    } else if (strcmp(cad, "AYUDA") == 0) {
        pintaAyuda(inter);
        pintaMapa(inter, map);
        return OKE;
    } else if (strcmp(cad, "CREDITOS") == 0) {
        pintaCreditos(inter);
        pintaMapa(inter, map);
        return OKE;



    } else {
        escribeConsola(inter, "No existe esa accion,consulta ayuda.");
    }
    return ERROR;
}

