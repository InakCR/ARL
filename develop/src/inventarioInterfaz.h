/******************************************************************************

Nombre del fichero: inventarioInterfaz.h

Nombre del módulo correspondiente: inventarioInterfaz.c

Descripción:
Cabeceras del módulo Interfaz para las funciones relativas al inventario.

Autor: Miguel Angel Gomez-Tavira

******************************************************************************/

#ifndef INVENTARIO_INTERFAZ_H
#define	INVENTARIO_INTERFAZ_H

/*=== Cabeceras =============================================================*/
#include "interface.h"
#include "inventario.h"
#include "personaje.h"
#include "mundo.h"

/*=== Definiciones ==========================================================*/
/*=== Prototipos de Funciones ===============================================*/
/*-----------------------------------------------------------------------------
pintaInventario: Muestra por pantalla el contenido del inventario.
-----------------------------------------------------------------------------*/
extern STATUS pintaInventario(INTERFAZ* interfaz,NODO_MUNDO* nodo, INVENTARIO* inventario);
/*-----------------------------------------------------------------------------
pintaStats: Muestra por pantalla el valor de los stats del pj.
-----------------------------------------------------------------------------*/
extern STATUS pintaStats(INTERFAZ* inter,PERSONAJE* pj);
/*****************************************************************************/

#endif	/* INVENTARIO_INTERFAZ_H */

