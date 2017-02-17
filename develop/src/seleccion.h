/******************************************************************************
 *
 *  Nombre del fichero: seleccion.h
 *
 *  Nombre del módulo correspondiente: Logica.
 *
 *  Descripción: Protipos de las funciones para la distribucion de las acciones.
 *
 *  Realizado por: Iñaki Cadalso Reymundo.
 *
 ******************************************************************************/

#include "acciones.h"
#include "entorno.h"
#include "mundo.h"

/*------------------------------------------------------------------
 *@name seleccionAccionInmediata
 *@brief Gestiona el movimiento sobre el entorno.
 *@param (NODO_MUNDO *nmundo,PERSONAJE*pj,INTERFAZ * inter, int acc) Nodo donde se encuentra entorno a modificar,jugador a interaccionar, interfaz a modificar y direccion del movimiento.
 *@return ERROR o OK.
------------------------------------------------------------------*/
extern STATUS seleccionAccionInmediata(NODO_MUNDO** nmundo,PERSONAJE*pj,INTERFAZ * inter, int acc);
/*------------------------------------------------------------------
 *@name seleccionAccion
 *@brief Gestiona la seleccion de la accion de logica
 *@param (NODO_MUNDO* nmundo,PERSONAJE*pj,INTERFAZ * inter, char *cad)Nodo donde se encuentra entorno a modificar, jugador a interaccionar, interfaz a modificar y accion.
 *@return ERROR o OK.
------------------------------------------------------------------*/
extern STATUS seleccionAccion(NODO_MUNDO* nmundo,PERSONAJE*pj, INTERFAZ *inter ,char *cad);




