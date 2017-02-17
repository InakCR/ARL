/******************************************************************************
*
*  Nombre del fichero: entorno.h
*
*  Nombre del módulo correspondiente: entorno.c
*
*  Descripción: Estructuras del entorno 
*
*  Realizado por: Miguel Angel Gomez-Tavira/Diego Chicote
*
******************************************************************************/

#ifndef MUNDO_H
#define	MUNDO_H

/*=== Cabeceras =============================================================*/
#include "entorno.h"
#include "interface.h"

/*=== Definiciones ==========================================================*/
/*Tamaño máximo del mundo.*/
#define MAX_MUNDO 10

/*Nodos del mundo que recogen tanto los datos del entorno que almacena cada
 uno de ellos, así como las direcciones de los nodos colindantes.*/
typedef struct NODO_MUNDO{

    ENTORNO * ent;
    struct NODO_MUNDO* siguiente;
    struct NODO_MUNDO* anterior;
 
}NODO_MUNDO;

/*Mundo en el que se guardan los entornos que conforman el juego
 Esta implementado a modo de una lista.*/
typedef struct{
    NODO_MUNDO* primero;
    NODO_MUNDO* ultimo;
    int         numEntornos;
    PERSONAJE* pj;
}MUNDO;

/*------------------------------------------------------------------
 *@name iniMundo
 *@brief Inicializa un mundo, reservando memoria para este
 *@param (MUNDO * world)
 *@return -  OKE, si se ha terminado sin problemas
   - ERROR_RM, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern STATUS iniMundo(MUNDO* world);

/*------------------------------------------------------------------
 *@name destruirMundo
 *@brief Destruye un mundo, liberando memoria de este
 *@param (MUNDO * world)
 *@return -  OKE, si se ha terminado sin problemas
   - ERROR_RM, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern STATUS destruirMundo(MUNDO* world);

/*------------------------------------------------------------------
 *@name iniNodoMundo
 *@brief Inicializa un nodo del mundo, reservando memoria para este
 *@param (NODO_MUNDO* nodo,ENTORNO* ent)
 *@return -  OKE, si se ha terminado sin problemas
   - ERROR_RM, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern STATUS iniNodoMundo (NODO_MUNDO* nodo,ENTORNO* ent);

/*------------------------------------------------------------------
 *@name destruyeNodoMundo
 *@brief Destruye un nodo del mundo, liberando memoria de este
 *@param (NODO_MUNDO* nodo)
 *@return -  OKE, si se ha terminado sin problemas
   - ERROR_RM, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern STATUS destruyeNodoMundo(NODO_MUNDO* nodo);

/*------------------------------------------------------------------
 *@name buscarEnMundo
 *@brief Busca un entorno dentro del mundo por su nombre
 *@param (MUNDO* world,NODO_MUNDO* nodo, const char* nombreEnt) 
 *@return -  OKE, si se ha terminado sin problemas
   - ERROR_RM, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern STATUS buscarEnMundo(MUNDO* world,NODO_MUNDO* nodo, const char* nombreEnt) ;

/*------------------------------------------------------------------
 *@name pushNodoMundo
 *@brief inserta un nodo en el mundo
 *@param (MUNDO* world, NODO_MUNDO* nodo)
 *@return -  OKE, si se ha terminado sin problemas
   - ERROR_RM, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern STATUS pushNodoMundo(MUNDO* world, NODO_MUNDO* nodo);

/*------------------------------------------------------------------
 *@name popNodoMundo
 *@brief Extrae un nodo del mundo
 *@param (MUNDO* world, NODO_MUNDO* nodo,char* nombreEnt)
 *@return -  OKE, si se ha terminado sin problemas
   - ERROR_RM, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern STATUS popNodoMundo(MUNDO* world, NODO_MUNDO* nodo,char* nombreEnt);

/*------------------------------------------------------------------
 *@name esVacioMundo
 *@brief Comprueba si un mundo esta vacio
 *@param (MUNDO * world).
 *@return - VERDADERO, si el mundo esta vacio
   - FALSO si contiene algo
------------------------------------------------------------------*/
extern BOOL esVacioMundo (MUNDO* world);

extern ENTORNO* getEntornoNodoMundo(NODO_MUNDO* nodo);

#endif /* MUNDO_H */
