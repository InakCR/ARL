/******************************************************************************

Nombre del módulo: interface.c

Descripción: 
        Funciones para generar la interfaz de juego, asi como las diversas
 imagenes de introduccion.

Autor: Miguel Angel Gomez-Tavira

Fecha: 25-03-2013

Modulos propios que necesita: 
- interface.h
- tipos.h

Modificaciones: 
[25-03-2013] Creación de fichero y comienzo de implementación del pseudocódigo.
[30-03-2013] Terminadas las funciones:
 *           -iniciaInterfaz
 *           -terminaInterfaz
[12-06-2013] Terminadas las funciones:
 *           -pintaTitulo
 *           -pintaPresentacion
 *           -pintaFinMal
 *           -pintaFinBien

 ******************************************************************************/

/*=== Cabeceras =============================================================*/
#include <ncurses.h>
#include <unistd.h>
#include "interface.h"

/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------

Nombre: iniciaInterfaz

Descripción:
  Inicia la interfaz de juego, reservando memoria para la misma.

Argumentos de entrada: 

Retorno: 
- INTERFAZ*, puntero a la interfaz inicializada.
- NULL, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern INTERFAZ* iniciaInterfaz() {

    INTERFAZ* interfaz;
    int i = 0;

    initscr();
    cbreak();
    mvaddstr(stdscr->_maxy / 2, stdscr->_maxx / 2, "Pulsa F11.");
    getch();
    clear();
    start_color();
    if (pintaTitulo() != OKE)
        return NULL;

    interfaz = (INTERFAZ*) malloc(sizeof (INTERFAZ));
    if (interfaz == NULL)
        return NULL;

    interfaz->ventana[CMAPA] = newwin((stdscr->_maxy)*0.75, (stdscr->_maxx)*0.75, 2, 2);
    interfaz->ventana[CINV] = newwin((stdscr->_maxy)*0.75, (stdscr->_maxx)*0.20, 2, ((stdscr->_maxx)*0.75) + 4);
    interfaz->ventana[CCONS] = newwin((stdscr->_maxy)*0.20, (stdscr->_maxx)*0.75, ((stdscr->_maxy)*0.75) + 2, 2);
    interfaz->ventana[CSTATS] = newwin((stdscr->_maxy)*0.20, (stdscr->_maxx)*0.20, ((stdscr->_maxy)*0.75) + 2, ((stdscr->_maxx)*0.75) + 4);

    for (i = 0; i < MAX_VENT; i++) {
        box(interfaz->ventana[i], 0, 0);
        interfaz->paneles[i] = new_panel(interfaz->ventana[i]);
    }

    return interfaz;

}

/*-----------------------------------------------------------------------------

Nombre: pintaTitulo

Descripción:
Pinta el titulo de juego que se le pase por fichero.

Argumentos de entrada:

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS pintaTitulo() {

    FILE* f;
    char* c = NULL;
    int captura = 0;
    int y = 0, x = 0;

    noecho();

    y = (stdscr->_maxy * 0.15);
    x = (stdscr->_maxx * 0.25);
    c = (char *) malloc(sizeof (char) *71);

    f = fopen("Titulo_ARL.txt", "r");
    if (f != NULL) {
        while (!feof(f)) {
            if (!feof(f)) {
                fgets(c, 71, f);
                if (strcmp(c, "\n") != 0) {
                    usleep(100000);
                    mvaddstr(y++, x, c);
                    refresh();
                }
            }
        }
        free(c);
        fclose(f);
    }

    do {
        captura = getchar();
    } while (captura < 49 || captura > 50);/*No termina hasta que recibe 1 o 2.*/

    switch (captura) {
        case 49:
            clear();
            pintaPresentacion();
            echo();
            return OKE;
            break;
        case 50:
            echo();
            return ERROR;
            break;
        default:
            return ERROR;
            break;
    }

    echo();
    return ERROR;

}

/*-----------------------------------------------------------------------------

Nombre: pintaPresentacion

Descripción:
Pinta la presentacion del juego que se le pase por fichero.

Argumentos de entrada:

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS pintaPresentacion() {

    FILE* f;
    char* c = NULL;
    int y = 0, x = 0, i = 0, j = 0;

    noecho();

    y = (stdscr->_maxy * 0.25);
    x = (stdscr->_maxx * 0.25);
    c = (char *) malloc(sizeof (char) *83);

    f = fopen("intro.txt", "r");
    if (f != NULL) {
        while (!feof(f)) {
            fgets(c, 83, f);
            if (!feof(f)) {
                if (strcmp(c, "\n") != 0)
                    for (i = 0; i < strlen(c); i++) {
                        usleep(50000);
                        mvaddch(y, x, c[i]);
                        x++;
                        refresh();
                    }
                j++;
                y = (stdscr->_maxy * 0.25) + j;
                x = (stdscr->_maxx * 0.25);
            }

        }

        free(c);
        fclose(f);
        mvaddstr(++y, x, "Pulsa cualquier tecla para continuar...");
        getch();
        clear();
    }
    return OKE;

}

/*-----------------------------------------------------------------------------

Nombre: pintaFinMal

Descripción:
Pinta la imagen del final malo del juego que se le pase por fichero.

Argumentos de entrada:

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS pintaFinMal() {

    FILE* f;
    char* c = NULL;
    int y = 0, x = 0;

    noecho();

    y = (stdscr->_maxy * 0.01);
    x = (stdscr->_maxx * 0.15);
    c = (char *) malloc(sizeof (char) *98);

    f = fopen("finalMalo.txt", "r");
    if (f != NULL) {
        while (!feof(f)) {
            fgets(c, 97, f);
            if (!feof(f)) {
                if (strcmp(c, "\n") != 0) {
                    mvaddstr(y++, x, c);
                    refresh();
                }
            }
        }
        free(c);
        fclose(f);
        getch();
        return OKE;
    }
    return ERROR;

}

/*-----------------------------------------------------------------------------

Nombre: pintaFinBien

Descripción:
Pinta la imagen del final bueno del juego que se le pase por fichero.

Argumentos de entrada:

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS pintaFinBien() {

    FILE* f;
    char* c = NULL;
    int y = 0, x = 0;

    noecho();

    y = (stdscr->_maxy * 0.10);
    x = (stdscr->_maxx * 0.35);
    c = (char *) malloc(sizeof (char) *41);

    f = fopen("finalBueno.txt", "r");
    if (f != NULL) {
        while (!feof(f)) {
            fgets(c, 41, f);
            if (!feof(f)) {
                if (strcmp(c, "\n") != 0) {
                    mvaddstr(y++, x, c);
                    refresh();
                }
            }
        }
        free(c);
        fclose(f);
        getch();
        return OKE;
    }
    return ERROR;

}

/*-----------------------------------------------------------------------------

Nombre: terminaInterfaz

Descripción:
Libera la memoria reservada para la interfaz.

Argumentos de entrada:
1. interfaz, se pasa por puntero la interfaz, en la que esta contenida la 
   ventana de la consola.

Retorno: 

-----------------------------------------------------------------------------*/
extern void terminaInterfaz(INTERFAZ * interfaz) {

    int i = 0;

    if (interfaz != NULL) {
        for (i = 0; i < MAX_VENT; i++) {
            del_panel(interfaz->paneles[i]);
        }

        for (i = 0; i < MAX_VENT; i++) {
            delwin(interfaz->ventana[i]);
        }
    }

    endwin();
}
/*****************************************************************************/
