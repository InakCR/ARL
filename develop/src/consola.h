/******************************************************************************

Nombre del fichero: consola.h

Nombre del módulo correspondiente: consola.c

Descripción:
Cabeceras del módulo Entradas para las funciones relativas a la consola.

Autor: Miguel Angel Gomez-Tavira

******************************************************************************/

#ifndef CONSOLA_H
#define	CONSOLA_H

/*=== Cabeceras =============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <panel.h>
#include "entorno.h"
#include "interface.h"
#include "mundo.h"

/*=== Definiciones ==========================================================*/

/*=== Prototipos de Funciones ===============================================*/
/*-----------------------------------------------------------------------------
iniciaConsola: Función que inicia la consola.
-----------------------------------------------------------------------------*/
extern STATUS iniciaConsola(INTERFAZ* interfaz);
/*-----------------------------------------------------------------------------
capturaConsola: Función que captura los datos introducidos en la consola.
-----------------------------------------------------------------------------*/
extern STATUS capturaConsola(INTERFAZ* interfaz,NODO_MUNDO* node,PERSONAJE* pj ,char * msg);
/*-----------------------------------------------------------------------------
escribeConsola: Función que escribe un mensaje en la consola.
-----------------------------------------------------------------------------*/
extern STATUS escribeConsola(INTERFAZ* interfaz, char * msg);
/*-----------------------------------------------------------------------------
modoAcciones: Función que captura datos de la consola para acciones de tipo
              inmediato.
-----------------------------------------------------------------------------*/
extern STATUS modoAcciones(INTERFAZ* interfaz,NODO_MUNDO** node,PERSONAJE* pj);

/*****************************************************************************/
#endif	/* CONSOLA_H */

