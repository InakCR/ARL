/******************************************************************************
 *
 *  Nombre del fichero: inventario.h
 *
 *  Nombre del módulo correspondiente: inventario.c
 *
 *  Descripción: Estructuras del inventario 
 *
 *  Realizado por: Diego Chicote
 *
 ******************************************************************************/

#ifndef INVENTARIOS_H
#define	INVENTARIOS_H

/*=== Cabeceras =============================================================*/
#include "objeto.h"

/*=== Definiciones ==========================================================*/
/*Tamaño máximo del inventario.*/
#define MAX_INV 8

/*Nodo del inventario que recogen tanto los datos del objeto que almacena cada
 uno de ellos, así como las direcciones de los nodos colindantes.*/
typedef struct NODO_INV {
    OBJETO* obj;
    struct NODO_INV* siguiente;
    struct NODO_INV* anterior;

} NODO_INV;

/*Inventario en el que el PJ(Personaje jugador) y los NPC(Personajes manejados
 * por la IA(Inteligencia Artificial), almacenan los objetos que llevan.
 Esta implementado a modo de una lista.*/
typedef struct {
    NODO_INV* primero;
    NODO_INV* ultimo;
    int numObjetos;
} INVENTARIO;

/*------------------------------------------------------------------
 *@name iniInventario
 *@brief Inicializa un inventario, reservando memoria para este
 *@param (INVENTARIO* inv) 
 *@return STATUS OKE , si reserva correctamente
 *              ERROR_RM , si no reserva correctamente
------------------------------------------------------------------*/
extern STATUS iniInventario(INVENTARIO* inv);

/*------------------------------------------------------------------
*@name copiaInventario
*@brief Copia el inventario origen en el Invnetario destino
*@param (INVENTARIO* dst,const INVENTARIO* org)
*@return STATUS OK si se copia el objeto correctamente
*              ERROR si no se realiza la copia correctamente
------------------------------------------------------------------*/
extern STATUS copiaInventario(INVENTARIO* dst,const INVENTARIO* org);

/*------------------------------------------------------------------
 *@name destruirInventario
 *@brief Destruye un inventario, liberando la memoria
 *@param (Inventario * inventario); el inventatio a destruir
 *@return STATUS OK si elimina el objeto correctamente
 *		ERROR_LM si no lo elimina correctamente
------------------------------------------------------------------*/
extern STATUS destruirInventario(INVENTARIO * inv);

/*------------------------------------------------------------------
 *@name iniNodoInv
 *@brief Crea un nodoInv con un objeto reservando memoria
 *@param (NODO_INV* nodo, OBJETO* obj); 
 *@return STATUS OK si reserva memoria correctamente
 *		ERROR_RM si no reserva memoria correctamente
------------------------------------------------------------------*/
extern STATUS iniNodoInv(NODO_INV* nodo, OBJETO* obj);

/*------------------------------------------------------------------
*@name copiaNodoInventario
*@brief Copia el NodoInventario origen en en el NodoInventario destino
*@param (NODO_INV* dst,const NODO_INV* org)
*@return STATUS OKE si se copia correctamente
*               ERROR si no se realiza la copia correctamente
------------------------------------------------------------------*/
extern STATUS copiaNodoInventario(NODO_INV* dst,const NODO_INV* org);

/*------------------------------------------------------------------
 *@name destruyeNodoInv
 *@brief Destruye un Nodoinventario, liberando la memoria
 *@param (NODO_INV* nodo); el NodoInventario a destruir
 *@return STATUS OK si elimina el objeto correctamente
 *		ERROR_LM si no lo elimina correctamente
------------------------------------------------------------------*/
extern STATUS destruyeNodoInv(NODO_INV* nodo);

/*------------------------------------------------------------------
 *@name buscarEnInventario
 *@brief Busca un objeto en un inventario dada du id.
 *@param (INVENTARIO * inv, NODO_INV* nodo, const char* nombreObj); el inventario
 *              donde buscar ,el nodo donde copiar el objeto buscado por el char nombre. 
 *@return STATUS OKE si encuentra el objeto 
 *		 ERROR si no lo encuentra
------------------------------------------------------------------*/
extern STATUS buscarEnInventario(INVENTARIO * inv, NODO_INV** nodo, const char* nombreObj);

/*------------------------------------------------------------------
 *@name pushNodoInv
 *@brief Annade un objeto al inventario, annadiendolo a la cadena de
 *	objetos y aumentando en 1 el numObjetos
 *@param (INVENTARIO* inv, NODO_INV* nodo); el inventario en el que va a 
 *	annadir nodo con el objeto.
 *@return STATUS:OKE si annade correctamente
 *		ERROR si no lo annade correctamente
------------------------------------------------------------------*/
extern STATUS pushNodoInv(INVENTARIO* inv, NODO_INV* nodo);

/*------------------------------------------------------------------
 *@name popNodoInv
 *@brief Annade un objeto al inventario, annadiendolo a la cadena de
 *	objetos y aumentando en 1 el numObjetos
 *@param (INVENTARIO* inv, NODO_INV* nodo, char* nombreObj); el inventario en el que va a 
 *	extraer el nodo con objeto y el nombre del objeto para encontrarlo.
 *@return STATUS:OKE si  extrae correctamente
 *		ERROR si no extrae correctamente
------------------------------------------------------------------*/
extern STATUS popNodoInv(INVENTARIO* inv, NODO_INV** nodo, char* nombreObj);

/*------------------------------------------------------------------
 *@name esVacioInv
 *@brief Comprueba si el inventario esta vacio
 *@param (INVENTARIO* inv); el inventario a comprobar
 *@return STATUS VERDADERO si elimina el objeto correctamente
 *		FALSO  si no lo elimina correctamente
------------------------------------------------------------------*/
extern BOOL esVacioInv(INVENTARIO* inv);

#endif	/* INVENTARIOS_H */