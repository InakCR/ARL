/******************************************************************************

Nombre del fichero: mapa.h

Nombre del módulo correspondiente: mapa.c

Descripción:
Cabeceras del módulo Interfaz para las funciones relativas al mapa.

Autor: Miguel Angel Gomez-Tavira

 ******************************************************************************/

#ifndef MAPA_H
#define	MAPA_H

/*=== Cabeceras =============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <panel.h>
#include "entorno.h"
#include "interface.h"
#include "mundo.h"
#include "tipos.h"


/*=== Definiciones ==========================================================*/

/*=== Prototipos de Funciones ===============================================*/
/*-----------------------------------------------------------------------------
pintaMapa: Muestra por pantalla el contenido del mapa.
-----------------------------------------------------------------------------*/
extern STATUS pintaMapa(INTERFAZ* interfaz, MAPA* map);

/*-----------------------------------------------------------------------------
pintaAyuda: Pinta las instrucciones simplificadas del juego por pantalla.
-----------------------------------------------------------------------------*/
extern STATUS pintaAyuda(INTERFAZ* interfaz);

/*-----------------------------------------------------------------------------
pintaCreditos: Pinta los creditos de realizacion por pantalla.
-----------------------------------------------------------------------------*/
extern STATUS pintaCreditos(INTERFAZ* interfaz);

/*-----------------------------------------------------------------------------
pintaFin: Pinta el final malo del juego.
-----------------------------------------------------------------------------*/
extern STATUS pintaFin(INTERFAZ* interfaz);

/*-----------------------------------------------------------------------------
pintaFinBueno: Pinta el final bueno del juego.
-----------------------------------------------------------------------------*/
extern STATUS pintaFinBueno(INTERFAZ* interfaz);

/*****************************************************************************/
#endif	/* MAPA_H */

