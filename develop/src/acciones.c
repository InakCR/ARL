/******************************************************************************

Nombre del m�dulo: acciones.c

Descripci�n:
        Funciones para el manejo de datos de la consola, tanto para capturar
informaci�n que el usuario introducir� por medio de la consola, como para
mostrar informaci�n que el programa le transmitir� al usuario.

Autor: I�aki Cadalso

Fecha: 14-03-2013

Modulos propios que necesita:
- acciones.h


Modificaciones:

[14-03-2013] Terminadas las funciones:
 *           -tratamientoCadena
[28-03-2013] Terminadas las funciones:
 *           -Va�idacionComplemento
[05-04-2013] Terminadas las funciones:
 *			 -examinar
 *			 -coger
[27-04-2013] Eliminada la funcion:
 *            -ValidacionComplemento
 *            Añadida la funcion:
 *            -Combate.
 *            -hablar
[01-05-2013] Iñaki Cadalso corrige comentarios
 * 
[02-06-2013] Añadida funcion :
 *              -ComprobarPos
Mejoras pendientes:
- Ha falta en cambio de estructuras por acabar atacar,hablar,usar
  y correcta implementacion de coger(a distancia)

 ******************************************************************************/


/*=== Cabeceras =============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "acciones.h"
#include "consola.h"
#include "inventarioInterfaz.h"
#include "interface.h"
#include "mapa.h"




/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------

Nombre: hablar

Descripción:
        Gestiona las conversaciones con personajes amigos.

Argumentos de entrada:
1. ent, recibe un entorno por puntero.
2. pj,personaje amigo.
3. inter, interfaz a modificar.
4. pnj,personaje principal.


Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
STATUS hablar(ENTORNO *ent, INTERFAZ *inter, PERSONAJE *pj, PERSONAJE *pnj) {
    char* c = NULL;
    FILE* f = NULL;
    BOOL interactuar;
    MAPA *mapaEnt = NULL;
    int x, y, z, t;

    c = (char *) malloc(sizeof (char) *300);

    getMapaEnt(ent, &mapaEnt);
    getInteractuarPj(pj, &interactuar);
    getNombrePj(pj, c);
    getColPj(pnj, &x);
    getFilaPj(pnj, &y);
    getColPj(pj, &z);
    getFilaPj(pj, &t);

    if (comprobarPos(x, y, z, t) == FALSE) {
        free(c);
        escribeConsola(inter, "Acercate al él.");
        return OKE;
    }

    if (strcmp(c, "PRINCESA") == 0) {
        free(c);
        pintaFinBueno(inter);
        return OKE;
    }
    if (interactuar == FALSO) {
        free(c);
        escribeConsola(inter, "No es un amigo,¡¡¡¡¡ es un enemigo !!!!!");
    } else {
        f = fopen("covn.txt", "r");
        fgets(c, 300, f);
        escribeConsola(inter, c);
        free(c);
    }
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: tratamientoCadena

Descripción:
        Trata la cadena

Argumentos de entrada:

1. acc, cadena de tratar.

Retorno:
-  char, segunda palabra de la cadena


-----------------------------------------------------------------------------*/

char* tratamientoCadena(char **acc) {
    char s2[4] = " \n\t";
    char *ptr;
    int i;
    char* cadena;

    cadena = strdup(*acc);
    for (i = 0; cadena[i]; i++) { /* Cambia las minusculas a mayusculas con la funcion toupper */
        cadena[i] = toupper(cadena[i]);
    }
    *acc = strtok(cadena, s2);
    ptr = strtok(NULL, s2);
    return ptr;

}

/*-----------------------------------------------------------------------------

Nombre: coger

Descripción:
        Modifica el inventario del personaje.

Argumentos de entrada:

1. ent, recibe un entorno por puntero.
2. inv, inventario del personaje.
3. obj, objeto a introducir en el inventario


Retorno:
-  char, del estado de la accion.

-----------------------------------------------------------------------------*/
char* coger(ENTORNO *ent, PERSONAJE* pnj, OBJETO* obj) {
    NODO_INV* nodo = NULL;
    MAPA* mapa = NULL;
    char *nom = NULL;
    char * c = NULL;
    char gh = ' ';
    int x, y, z, t;

    if (obj == NULL) {
        c = "No existe ese objeto.";
        return c;
    }

    nom = (char*) malloc(sizeof (char)*100);

    getMapaEnt(ent, &mapa);
    getNombreObj(obj, nom);
    getColumnaObj(obj, &x);
    getFilaObj(obj, &y);
    getFilaPj(pnj, &t);
    getColPj(pnj, &z);

    if (comprobarPos(x, y, z, t) == VERDADERO) {

        popNodoInv(ent->invEnt, &nodo, nom);

        if (pushNodoInv(pnj->inv, nodo) == OKE) {
            free(nom);
            modGrahMap(mapa, gh, x, y);
            c = "Se ha cogido el objeto.";
            return c;
        } else {
            c = "No se ha podido coger el objeto, inventario lleno.";
            pushNodoInv(ent->invEnt, nodo);
            free(nom);
            return c;
        }
    }
    c = "No se ha podido coger el objeto, acercate a él.";
    return c;

}

/*-----------------------------------------------------------------------------

Nombre: examinar

Descripción:
        Encuentra la descripcion pedida.

Argumentos de entrada:

1. ent, a tomar la descripcion.
2. pj, a tomar la descripcion.
3. obj, a tomar la descripcion.


Retorno:
-  char, descripcion solicitada.

-----------------------------------------------------------------------------*/
char* examinar(ENTORNO *ent, OBJETO *obj, PERSONAJE *pj) {
    char * c = NULL;
    c = (char*) malloc(sizeof (char)*100);

    if (pj == NULL && obj == NULL)
        getDescripcionEnt(ent, c);
    else if (pj == NULL)
        getDescObj(obj, c);
    else
        getDescPj(pj, c);
    return c;
}

/*-----------------------------------------------------------------------------

Nombre: atacar

Descripción:
        Modifica al enemigo y al jugador del entorno.

Argumentos de entrada:

1. ent, a tomar el personaje.
2. inter, interfaz a modificar.
3. ene, a atacar


Retorno:
-  char, del estado de la accion.

-----------------------------------------------------------------------------*/

char* atacar(ENTORNO *ent, INTERFAZ *inter, PERSONAJE* pnj, PERSONAJE* ene) {

    int x, y, z, t;
    char* c = NULL;
    BOOL atacable;

    if (ent == NULL || ene == NULL)
        return c = "No existe el enemigo";

    getAtacablePj(ene, &atacable);

    if (atacable == FALSO)
        return c = "Es amigo, no te ganes otro enemigo más :)";


    getFilaPj(pnj, &y);
    getColPj(pnj, &x);
    getFilaPj(ene, &t);
    getColPj(ene, &z);

    if (comprobarPos(x, y, z, t) == VERDADERO) {
        c = combate(ent, pnj, inter, ene);
        return c;
    }

    c = "Acercate al enemigo,cobarde";
    return c;
}

/*-----------------------------------------------------------------------------

Nombre: usar

Descripción:
        Modifica al jugador o entorno segun el objeto.

Argumentos de entrada:

1. ent, a tomar el personaje.
2. obj, objeto a usar .
3. inv, a coger el objeto.


Retorno:
-  char, del estado de la accion.

-----------------------------------------------------------------------------*/
char* usar(ENTORNO *ent, OBJETO* obj, PERSONAJE* pnj) {

    int pf, pd, pvt, pv;
    int x, y;
    char* nom;
    char* c;
    /*MAPA* mapaEnt = NULL;*/
    NODO_INV* nodo = NULL;

    nom = (char*) malloc(sizeof (char));

    getNombreObj(obj, nom);
    getColPj(pnj, &x);
    getFilaPj(pnj, &y);

    if (buscarEnInventario(pnj->inv, &nodo, nom) == OKE) {
        if ((strcmp(nom, "ESPADA") == 0)) {
            getFuerzaPj(pnj, &pf);
            pf++;
            setFuerzaPj(pnj, pf);
        }
        if ((strcmp(nom, "LIBRO") == 0)) {
            getDefensaPj(pnj, &pd);
            pd++;
            setDefensaPj(pnj, pd);
        }

        if ((strcmp(nom, "PECHERA") == 0)) {
            getDefensaPj(pnj, &pd);
            pd = pd + 5;
            setDefensaPj(pnj, pd);
        }
        if ((strcmp(nom, "PANTALONES") == 0)) {
            getDefensaPj(pnj, &pd);
            pd = pd + 3;
            setDefensaPj(pnj, pd);
        }
        if ((strcmp(nom, "GUANTES") == 0)) {
            getDefensaPj(pnj, &pd);
            pd++;
            setDefensaPj(pnj, pd);
        }
        if ((strcmp(nom, "BOTAS") == 0)) {
            getDefensaPj(pnj, &pd);
            pd++;
            setDefensaPj(pnj, pd);
        }
        if ((strcmp(nom, "ESCUDO") == 0)) {
            getDefensaPj(pnj, &pd);
            pd = pd + 3;
            setDefensaPj(pnj, pd);
        }
        if ((strcmp(nom, "CASCO") == 0)) {
            getDefensaPj(pnj, &pd);
            pd = pd + 2;
            setDefensaPj(pnj, pd);
        }
        if ((strcmp(nom, "POCION") == 0)) {
            getVitPj(pnj, &pv);
            getVitTotPj(pnj, &pvt);
            pv = pvt;
            setVitPj(pnj, pv);

        }
        if ((strcmp(nom, "POCION DE CURACION") == 0)) {
            getVitTotPj(pnj, &pvt);
            pvt = pvt + 5;
            setVitTotPj(pnj, pvt);
        }
        popNodoInv(pnj->inv, &nodo, nom);
        destruyeNodoInv(nodo);
        free(nom);
        c = "Objeto usado";
        return c;
    } else {
        c = "El objeto no se encuentra en el inventario";
        return c;
    }

}

/*-----------------------------------------------------------------------------

Nombre: combate

Descripción:
        calculos de atacar enemigo-personaje.

Argumentos de entrada:

1. pj, personaje principal.
2. inter, interfaz a modificar.
3. ene, a atacar.


Retorno:
-  char, del estado de la accion.

-----------------------------------------------------------------------------*/
char* combate(ENTORNO* ent, PERSONAJE *pj, INTERFAZ *inter, PERSONAJE *ene) {
    int pv, pvt, pf, pd;
    int ev, evt, ef, ed;
    int x, y;
    char* c = NULL;
    char* nom = NULL;
    char gh = ' ';

    /*FILE *f=NULL;*/
    MAPA* mapaEnt = NULL;
    NODO_PJ* nodo = NULL;

    nom = (char*) malloc(sizeof (char)*50);

    getMapaEnt(ent, &mapaEnt);

    getColPj(ene, &x);
    getFilaPj(ene, &y);
    getNombrePj(ene, nom);

    getVitPj(pj, &pv);
    getVitTotPj(pj, &pvt);
    getFuerzaPj(pj, &pf);
    getDefensaPj(pj, &pd);

    getVitPj(ene, &ev);
    getVitTotPj(ene, &evt);
    getFuerzaPj(ene, &ef);
    getDefensaPj(ene, &ed);

    if (ed < pf)
        ev = ev - (pf - ed);

    if (pd < ef)
        pv = pv - (ef - pd);

    setVitPj(pj, pv);
    setVitPj(ene, ev);

    if (pv <= 0) {
        c = "Estas muerto";
        pintaFin(inter);
        free(nom);
        usleep(180000);
        return c;

    } else if (ev <= 0) {

        popNodoPj(ent->pjsEnt, &nodo, nom);
        destruyeNodoPj(nodo);
        free(nom);
        modGrahMap(mapaEnt, gh, x, y);

        c = "Enemigo abatido, has subido de nivel";
        pvt++;
        pf++;
        pd++;

        setVitTotPj(pj, pvt);
        setFuerzaPj(pj, pf);
        setDefensaPj(pj, pd);
        return c;
    } else if (ed < pf) {
        c = "Es muy efectivo, continua atacando";
        free(nom);
        return c;
    } else {
        c = "No es muy efectivo, quizas deberias pensar en mejorar tus habilidades";
        free(nom);
        return c;
    }
    free(nom);
    return c;
}

/*-----------------------------------------------------------------------------

Nombre: comprobacionPos

Descripción:
       Comprueba la posicion del personaje respecto enemigos/objetos..

Argumentos de entrada:

1. x, columna personaje.
2. y, fila personaje.
3. z, columna enemigo/objeto.
4. t, fila enemigo/objeto.


Retorno:
-  BOOL,Verdaderv o falso , segun este cerca o no.

-----------------------------------------------------------------------------*/
BOOL comprobarPos(int x, int y, int z, int t) {
    x--;
    if (x == z && y == t)
        return VERDADERO;
    x++;
    y--;
    if (x == z && y == t)
        return VERDADERO;
    y = y + 2;
    if (x == z && y == t)
        return VERDADERO;
    y--;
    x++;
    if (x == z && y == t)
        return VERDADERO;
    return FALSO;

}

STATUS nivelFinal(ENTORNO* ent, INTERFAZ* inter) {
    MAPA* map = NULL;
    PERSONAJE* dg = NULL;
    int col, i;
    char gh = ' ';

    getMapaEnt(ent, &map);
    dg = getPersonajeEnt(ent, "DRAGON");
    getColPj(dg, &col);
    col = col - DISTANCIA;

    for (i = 1; i < 10; i++) {
        modGrahMap(map, gh, col, i);
        pintaMapa(inter, map);
        usleep(180000);
        doupdate();

    }
    
    return OKE;
}

BOOL compruebaNivel(PERSONAJE* pj) {
    int f, d;

    getFuerzaPj(pj, &f);
    getDefensaPj(pj, &d);

    if (d > MAXDEFENSA && f > MAXFUERZA)
        return VERDADERO;
    return FALSO;

}



