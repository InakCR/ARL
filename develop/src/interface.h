/******************************************************************************

Nombre del fichero: interface.h

Nombre del módulo correspondiente: interface.c

Descripción:
Cabeceras del módulo Interface para la representación gráfica.

 ******************************************************************************/

#ifndef INTERFACE_H
#define	INTERFACE_H

/*=== Cabeceras =============================================================*/

#include "tipos.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <panel.h>
#include <unistd.h>

/*=== Definiciones ==========================================================*/
#define MAX_VENT 4
#define CMAPA  0
#define CINV 1
#define CCONS  2
#define CSTATS 3

typedef struct {
    WINDOW * ventana[MAX_VENT];
    PANEL * paneles[MAX_VENT];
} INTERFAZ;

/*=== Prototipos de Funciones ===============================================*/

/*-----------------------------------------------------------------------------
iniciaInterfaz: Inicia la interfaz del juego.
-----------------------------------------------------------------------------*/
extern INTERFAZ* iniciaInterfaz();

/*-----------------------------------------------------------------------------
pintaTitulo: Pinta la pantalla de titulo.
-----------------------------------------------------------------------------*/
extern STATUS pintaTitulo();

/*-----------------------------------------------------------------------------
pintaPresentacion: Pinta la intro del juego.
-----------------------------------------------------------------------------*/
extern STATUS pintaPresentacion();

/*-----------------------------------------------------------------------------
pintaFinBien: Pinta el final bueno.
-----------------------------------------------------------------------------*/
extern STATUS pintaFinBien();

/*-----------------------------------------------------------------------------
pintaFinMal: Pinta el final malo.
-----------------------------------------------------------------------------*/
extern STATUS pintaFinMal();

/*-----------------------------------------------------------------------------
terminaInterfaz: libera la memoria usada para la interfaz.
-----------------------------------------------------------------------------*/
extern void terminaInterfaz(INTERFAZ* interfaz);
/*****************************************************************************/

#endif	/* INTERFACE_H */
