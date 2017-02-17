/******************************************************************************
 *
 *  Nombre del fichero: pjsEntorno.h
 *
 *  Nombre del módulo correspondiente: pjsEntorno.c
 *
 *  Descripción: Estructuras del PjsEntorno 
 *
 *  Realizado por: Miguel Gomez-Tavira
 *
 ******************************************************************************/

#ifndef PJSENTORNO_H
#define	PJSENTORNO_H

/*=== Cabeceras =============================================================*/
#include "personaje.h"

/*=== Definiciones ==========================================================*/
/*Número máximo de personajes.*/
#define MAX_PJS 10

/*Nodo del inventario que recogen tanto los datos del objeto que almacena cada
 uno de ellos, así como las direcciones de los nodos colindantes.*/
typedef struct NODO_PJ {
    PERSONAJE* pj;
    struct NODO_PJ* siguiente;
    struct NODO_PJ* anterior;

} NODO_PJ;

/*Inventario en el que el PJ(Personaje jugador) y los NPC(Personajes manejados
 * por la IA(Inteligencia Artificial), almacenan los objetos que llevan.
 Esta implementado a modo de una lista.*/
typedef struct {
    NODO_PJ* primero;
    NODO_PJ* ultimo;
    int numPjs;
} PJSENTORNO;

/*------------------------------------------------------------------
 *@name iniPjsEnt
 *@brief Inicializa un personajes de entorno, reservando memoria para este
 *@param (PJSENTORNO* pjsEnt) 
 *@return STATUS OKE si reserva correctamente.
 *              ERROR_RM, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern STATUS iniPjsEnt(PJSENTORNO* pjsEnt);

/*------------------------------------------------------------------
 *@name destruirPjsEnt
 *@brief Destruye un personajes de entorno, liberando la memoria
 *@param (PJSENTORNO * pjsEnt); el inventatio a destruir
 *@return STATUS OKE si elimina el objeto correctamente
 *		ERROR_LM si no lo elimina correctamente
------------------------------------------------------------------*/
extern STATUS destruirPjsEnt(PJSENTORNO * pjsEnt);

/*------------------------------------------------------------------
 *@name iniNodoPj
 *@brief reserva memoria para un Nodo Pj
 *@param (NODO_PJ* nodoPj,PERSONAJE* pj); Nodo a crear con un personaje
 *@return STATUS OK si elimina el objeto correctamente
 *		ERROR_RM si no lo elimina correctamente
------------------------------------------------------------------*/
extern STATUS iniNodoPj(NODO_PJ* nodoPj, PERSONAJE* pj);

/*------------------------------------------------------------------
 *@name destruyeNodoPj
 *@brief Destruye un NodoPj, liberando la memoria
 *@param (NODO_PJ* nodoPj); el nodo a destruir
 *@return STATUS OK si elimina el objeto correctamente
 *		ERROR_LM si no lo elimina correctamente
------------------------------------------------------------------*/
extern STATUS destruyeNodoPj(NODO_PJ* nodoPj);

/*------------------------------------------------------------------
 *@name buscarPjsEnt
 *@brief Busca un personaje en un pjsEntorno.
 *@param (PJSENTORNO * pjsEnt,NODO_PJ* nodoPj, const char* nombrePj);PjsEntorno donde
 *      buscar el nodo_PJ con el char.
 *@return STATUS OK si encuentra el objeto 
 *		ERROR si no lo encuentra
------------------------------------------------------------------*/
extern STATUS buscarPjsEnt(PJSENTORNO * pjsEnt, NODO_PJ** nodoPj, const char* nombrePj);

/*------------------------------------------------------------------
 *@name pushNodoPj
 *@brief Annade un nodo de personaje a pjsEntorno.
 *@param (PJSENTORNO* pjsEnt, NODO_PJ* nodoPj); 
 *@return STATUS:OK si annade el objeto correctamente
 *		ERROR si no lo annade correctamente
------------------------------------------------------------------*/
extern STATUS pushNodoPj(PJSENTORNO* pjsEnt, NODO_PJ* nodoPj);

/*------------------------------------------------------------------
 *@name popNodoPj
 *@brief Extrae un node de personaje a pjsEntorno
 *@param (PJSENTORNO* pjsEnt, NODO_PJ* nodoPj,char* nombrePj) PjEntorno donde extraer
 *  el nodo buscado por el char nom dado.
 *@return STATUS:OKE si annade el objeto correctamente
 *		ERROR si no lo annade correctamente
------------------------------------------------------------------*/
extern STATUS popNodoPj(PJSENTORNO* pjsEnt, NODO_PJ** nodoPj, char* nombrePj);
/*------------------------------------------------------------------
 *@name esVacioPjsEnt
 *@brief Comprueba si hay nodos de personaje en el pjsEntorno
 *@param (PJSENTORNO* pjsEnt) donde comprobar
 *@return STATUS VERDADERO si elimina el objeto correctamente
 *		FALSO si no lo elimina correctamente
------------------------------------------------------------------*/
extern BOOL esVacioPjsEnt(PJSENTORNO* pjsEnt);


#endif	/* PJSENTORNO_H */

