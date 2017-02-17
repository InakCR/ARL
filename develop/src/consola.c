/******************************************************************************

Nombre del módulo: consola.c

Descripción: 
        Funciones para el manejo de datos de la consola, tanto para capturar 
información que el usuario introducirá por medio de la consola, como para
mostrar información que el programa le transmitirá al usuario.

Autor: Miguel Angel Gomez-Tavira

Fecha: 25-03-2013

Modulos propios que necesita: 
- consola.h
- tipos.h

Modificaciones: 
[25-03-2013] Creación de fichero y comienzo de implementación del pseudocódigo.
[30-03-2013] Terminadas las funciones:
 *           -iniciaConsola
 *           -capturaConsola
 *           -escribeConsola
 *           -modoAcciones
 *           -destruyeConsola
[31-03-2013] Borrada la función destruyeConsola, se libera en terminaInterfaz

 ******************************************************************************/

/*=== Cabeceras =============================================================*/
#include "tipos.h"
#include "consola.h"
#include "acciones.h"
#include "seleccion.h"
/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------

Nombre: iniciaConsola

Descripción:
  Inicia la ventana de la consola, reservando memoria para la misma y el 
panel en el que esta va encajada. 
  El tamaño de esta ventana es relativo al tamaño de la terminal, y su posición
es fija, en la ventana general.

Argumentos de entrada: 
1. interfaz, se pasa por puntero la interfaz, en la que esta contenida la 
   ventana de la consola.

Retorno: 
-  OKE  , si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS iniciaConsola(INTERFAZ* interfaz) {

    if (interfaz != NULL) {

        interfaz->ventana[CCONS]->_scroll = TRUE; /*Activamos el scroll.*/
        keypad(interfaz->ventana[CCONS], TRUE);   /*Activamos el teclado, para que reconozca teclas complejas.*/
        mvwprintw(interfaz->ventana[CCONS],       /*Escribimos en la consola, el modo en que esta inicializa. */
                interfaz->ventana[CCONS]->_maxy - 3, 1, "Modo texto:");
        mvwaddstr(interfaz->ventana[CCONS],       /*Movemos el puntero de la ventana a la posición de inicio. */
                interfaz->ventana[CCONS]->_maxy - 2, 1, ">"); 
        doupdate(); /*Actualizamos el contenido de los paneles.*/
        return OKE;
    }
    return ERROR;
}

/*-----------------------------------------------------------------------------

Nombre: capturaConsola

Descripción:
    Esta función consta de un bucle que va capturando de la consola, los datos
que el usuario introduce, para realizar las distintas acciones posibles.

Argumentos de entrada:
1. interfaz, se pasa por puntero la interfaz, en la que esta contenida la 
   ventana de la consola.
2. node, nodo que contiene el entorno en el cual se desarrolla el juego.
3. pj, personaje jugador.
4. msg, puntero a una cadena de caracteres en la que guardamos los datos que el
   usuario introduce.

Retorno: 
-  OKE  , si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS capturaConsola(INTERFAZ* interfaz, NODO_MUNDO* node, PERSONAJE* pj, char * msg) {

    if (interfaz == NULL)
        return ERROR;

    mvwprintw(interfaz->ventana[CCONS], /*Escribimos en la consola, el modo en que esta inicializa. */
            interfaz->ventana[CCONS]->_maxy - 3, 1, "Modo texto:");
    mvwaddstr(interfaz->ventana[CCONS], /*Movemos el puntero de la ventana a la posición de inicio. */
            interfaz->ventana[CCONS]->_maxy - 2, 1, ">");
    update_panels(); /*Actualizamos los paneles.*/
    
    while (strcmp(msg, "salir") != 0) { /*El bucle repite la captura de datos, hasta que el usuario escribe "salir".*/
        if (strcmp(msg, "s") == 0) { /*Si el usuario pulsa s y enter, cambiamos al modo acciones.*/
            mvwaddstr(interfaz->ventana[CCONS], /*Movemos el puntero de la ventana a la posición de inicio. */
                    interfaz->ventana[CCONS]->_maxy - 2, 1, ">");
            update_panels();
            modoAcciones(interfaz, &node, pj);
        }
        if(strcmp(msg,"s")!= 0)
                seleccionAccion(node, pj, interfaz, msg);
        mvwaddstr(interfaz->ventana[CCONS],
                interfaz->ventana[CCONS]->_maxy - 2, 1, ">");
        wgetstr(interfaz->ventana[CCONS], msg); /*Capturamos la cadena que introduce el usuario.*/
        scroll(interfaz->ventana[CCONS]);       /*Hacemos scroll de 1 fila a la consola.*/
        wdeleteln(interfaz->ventana[CCONS]);    /*Borramos la linea en la que el usuario ha escrito.*/
        box(interfaz->ventana[CCONS], 0, 0);    /*Añadimos una caja para marcar su espacio.*/
        update_panels();
    }
    mvwaddstr(interfaz->ventana[CCONS],
            interfaz->ventana[CCONS]->_maxy - 2, 1, ">");
    doupdate();
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: escribeConsola

Descripción:
Función que escribe un mensaje en la consola.

Argumentos de entrada:
1. interfaz, se pasa por puntero la interfaz, en la que esta contenida la 
   ventana de la consola.
2. msg, puntero a una cadena de caracteres en la que guardamos la cadena que el
   usuario vera escritos en la consola.

Retorno: 
-  OKE  , si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS escribeConsola(INTERFAZ* interfaz, char * msg) {

    if (interfaz == NULL || msg == NULL)
        return ERROR;
    
    scroll(interfaz->ventana[CCONS]);       /*Hacemos scroll de 1 fila a la consola.*/
    wdeleteln(interfaz->ventana[CCONS]);    /*Borramos la linea en la que el usuario ha escrito.*/
    wdeleteln(interfaz->ventana[CCONS]);
    box(interfaz->ventana[CCONS], 0, 0);    /*Añadimos una caja para marcar su espacio.*/
    mvwprintw(interfaz->ventana[CCONS], /*Pintamos el mensaje en la consola.*/
            interfaz->ventana[CCONS]->_maxy - 3, 1, msg);
    mvwaddstr(interfaz->ventana[CCONS], /*Movemos el puntero de la ventana a la posición de inicio. */
            interfaz->ventana[CCONS]->_maxy - 2, 1, ">");
    box(interfaz->ventana[CCONS], 0, 0); /*Añadimos una caja para marcar su espacio.*/
    doupdate(); /*Actualizamos los paneles.*/
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: modoAcciones

Descripción:
  Función que cambia el modo de captura de datos de la consola, para mover al
personaje jugador.

Argumentos de entrada: 
1. interfaz, se pasa por puntero la interfaz, en la que esta contenida la 
   ventana de la consola.
2. node, nodo del mundo donde se desarrolla el juego.
3. pj, personaje jugador.

Retorno: 
-  OKE  , si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS modoAcciones(INTERFAZ* interfaz, NODO_MUNDO** node, PERSONAJE* pj) {

    int c = 0;

    if (interfaz == NULL)
        return ERROR;
    
    noecho(); /*Desactivamos el echo en la consola.*/
    mvwprintw(interfaz->ventana[CCONS], /*Escribimos en la consola, el modo activo. */
            interfaz->ventana[CCONS]->_maxy - 3, 1, "Modo acciones:");
    mvwaddstr(interfaz->ventana[CCONS], /*Movemos el puntero de la ventana a la posición de inicio. */
            interfaz->ventana[CCONS]->_maxy - 2, 1, ">");
    doupdate(); /*Actualizamos los paneles.*/
    while ((c = wgetch(interfaz->ventana[CCONS])) != 's') { /*Iniciamos el bucle para capturar las acciones inmediatas.*/
        seleccionAccionInmediata(node, pj, interfaz, c);
    }
    escribeConsola(interfaz, "Modo texto:");
    echo(); /*Reactivamos el echo antes de volver*/
    return OKE;
}

/*****************************************************************************/
