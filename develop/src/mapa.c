/******************************************************************************

Nombre del módulo: mapa.c

Descripción: 
        Funciones para la visualización del mapa.

Autor: Miguel Angel Gomez-Tavira

Fecha: 25-03-2013

Modulos propios que necesita: 
- mapa.h
- mundo.h
- entorno.h
- interface.h

Modificaciones: 
[25-03-2013] Creación de fichero y comienzo de implementación del pseudocódigo.
[30-03-2013] Terminadas las funciones:
 *           -pintaMapa
[01-05-2013] Borradas las funciones:
 *           -pintaObjetos
 *           -pintaPersonajes
 *           -actualizaMapa

 ******************************************************************************/

/*=== Cabeceras =============================================================*/
#include "mapa.h"
#include "entorno.h"
#include "interface.h"

/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------

Nombre: pintaMapa

Descripción:
  Pinta el campo mapa de entorno en la ventana mapa, para mostrar gráficamente
el resultado de las acciones del jugador sobre el mapa. 
  El tamaño de esta ventana es relativo al tamaño de la terminal, y su posición
es fija, en la ventana general.

Argumentos de entrada: 
1. interfaz, se pasa por puntero la interfaz, en la que esta contenida la 
   ventana de la consola.
2. map, el mapa del juego.

Retorno: 
-  OKE  , si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS pintaMapa(INTERFAZ* interfaz, MAPA* map) {

    int x = 0, y = 0, i = 0, j = 0;

    if ((interfaz != NULL)&&(map != NULL)) {
        y = (interfaz->ventana[CMAPA]->_maxy - map->filas) / 2;
        x = (interfaz->ventana[CMAPA]->_maxx - map->columnas) / 2;
        for (i = 0; i < map->filas; i++, y++) {
            for (j = 0; j < map->columnas; j++) {
                mvwaddch(interfaz->ventana[CMAPA], y, x + j, map->mapa[i][j]);
            }
        }
        box(interfaz->ventana[CMAPA], 0, 0);
        update_panels();
        return OKE;
    }
    return ERROR;
}

/*-----------------------------------------------------------------------------

Nombre: pintaAyuda

Descripción:
  Pinta el fichero de ayuda, que explica como se juega al juego.

Argumentos de entrada: 
1. interfaz, se pasa por puntero la interfaz, en la que esta contenida la 
   ventana de la consola.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/

extern STATUS pintaAyuda(INTERFAZ* interfaz) {

    FILE* f;
    int x, y;
    char* c = NULL;
    int captura;

    if (interfaz == NULL)
        return ERROR;

    f = fopen("ayuda.txt", "r");

    if (f == NULL)
        return ERROR;

    c = (char *) malloc(sizeof (char) *81);
    y = 1;
    x = 1;

    wclear(interfaz->ventana[CMAPA]);
    box(interfaz->ventana[CMAPA], 0, 0);

    while (!feof(f)) {
        fgets(c, 81, f);
        if (!feof(f)) {
            mvwaddstr(interfaz->ventana[CMAPA], y, x, c);
            y++;
        }
    }

    box(interfaz->ventana[CMAPA], 0, 0);
    update_panels();
    doupdate();

    free(c);
    fclose(f);

    do {
        captura = getchar();
    } while (captura != 115);

    wclear(interfaz->ventana[CMAPA]);
    box(interfaz->ventana[CMAPA], 0, 0);

    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: pintaCreditos

Descripción:
  Pinta el fichero con los creditos de realizacion del juego.

Argumentos de entrada: 
1. interfaz, se pasa por puntero la interfaz, en la que esta contenida la 
   ventana de la consola.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/

extern STATUS pintaCreditos(INTERFAZ* interfaz) {

    FILE* f;
    int x, y;
    char* c = NULL;
    int captura;

    if (interfaz == NULL)
        return ERROR;

    f = fopen("creditos.txt", "r");

    if (f == NULL)
        return ERROR;

    c = (char *) malloc(sizeof (char) *40);
    y = (interfaz->ventana[CMAPA]->_maxy * 0.25);
    x = (interfaz->ventana[CMAPA]->_maxx * 0.25);

    wclear(interfaz->ventana[CMAPA]);
    box(interfaz->ventana[CMAPA], 0, 0);

    while (!feof(f)) {
        fgets(c, 40, f);
        if (!feof(f)) {
            mvwaddnstr(interfaz->ventana[CMAPA], y, x, c, strlen(c) - 1);
            y++;
        }
    }

    box(interfaz->ventana[CMAPA], 0, 0);
    update_panels();
    doupdate();
    free(c);
    fclose(f);

    do {
        captura = getchar();
    } while (captura != 115);

    wclear(interfaz->ventana[CMAPA]);
    box(interfaz->ventana[CMAPA], 0, 0);

    return OK;
}

/*-----------------------------------------------------------------------------

Nombre: pintaFin

Descripción:
  Pinta el fichero con la imagen del final malo del juego.

Argumentos de entrada: 
1. interfaz, se pasa por puntero la interfaz, en la que esta contenida la 
   ventana de la consola.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS pintaFin(INTERFAZ* interfaz) {

    FILE* f;
    int x, y;
    char* c = NULL;
    int captura;

    if (interfaz == NULL)
        return ERROR;

    f = fopen("finalMalo.txt", "r");

    if (f == NULL)
        return ERROR;

    c = (char *) malloc(sizeof (char) *81);
    y = 1;
    x = 1;

    wclear(interfaz->ventana[CMAPA]);
    box(interfaz->ventana[CMAPA], 0, 0);

    while (!feof(f)) {
        fgets(c, 81, f);
        if (!feof(f)) {
            mvwaddstr(interfaz->ventana[CMAPA], y, x, c);
            y++;
        }
    }

    box(interfaz->ventana[CMAPA], 0, 0);
    update_panels();
    doupdate();

    free(c);
    fclose(f);

    do {
        captura = getchar();
    } while (captura != 115);

    wclear(interfaz->ventana[CMAPA]);
    box(interfaz->ventana[CMAPA], 0, 0);

    return OK;
}

/*-----------------------------------------------------------------------------

Nombre: pintaFinBueno

Descripción:
  Pinta el fichero con la imagen del final bueno del juego.

Argumentos de entrada: 
1. interfaz, se pasa por puntero la interfaz, en la que esta contenida la 
   ventana de la consola.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS pintaFinBueno(INTERFAZ* interfaz) {

    FILE* f;
    int x, y;
    char* c = NULL;
    int captura;

    if (interfaz == NULL)
        return ERROR;

    f = fopen("finBueno.txt", "r");

    if (f == NULL)
        return ERROR;

    c = (char *) malloc(sizeof (char) *81);
    y = 1;
    x = 1;

    wclear(interfaz->ventana[CMAPA]);
    box(interfaz->ventana[CMAPA], 0, 0);

    while (!feof(f)) {
        fgets(c, 81, f);
        if (!feof(f)) {
            mvwaddstr(interfaz->ventana[CMAPA], y, x, c);
            y++;
        }
    }

    box(interfaz->ventana[CMAPA], 0, 0);
    update_panels();
    doupdate();

    free(c);
    fclose(f);

    do {
        captura = getchar();
    } while (captura != 115);

    wclear(interfaz->ventana[CMAPA]);
    box(interfaz->ventana[CMAPA], 0, 0);

    return OK;
}
/*****************************************************************************/
