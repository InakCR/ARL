/******************************************************************************
*
*  Nombre del fichero: objetos.h
*
*  Nombre del módulo correspondiente: objeto.c
*
*  Descripción: Estructuras del objeto
*
*  Realizado por: Diego Chicote
*
******************************************************************************/

#ifndef OBJETOS_H
#define	OBJETOS_H

/*=== Cabeceras =============================================================*/
#include "tipos.h"

/*=== Definiciones ==========================================================*/

#define MAX_NOM_OBJ 30
#define MAX_DES_OBJ 100

/* La estructura OBJETO lleva el control de los objetos que aparecen en
 * el juego.
 */
typedef struct {
    
    ID    id;
    int   fila;
    int   columna;
    char* nombre;
    char* descripcion;
    char  graph;
        
    BOOL  movil;
    BOOL  movido;
    BOOL  ilumina;
    BOOL  encendido;
    BOOL  rompible;
    BOOL  roto;
    BOOL  teleport;
    

}OBJETO;

/*------------------------------------------------------------------
*@name iniObj
*@brief Inicializa un objeto, reservando memoria para este
*@return Un objeto nuevo,  si reserva correctamente
------------------------------------------------------------------*/
extern STATUS iniObj(OBJETO* obj);

/*------------------------------------------------------------------
*@name copiaObjeto
*@brief Copia el objeto origen en el objeto destino
*@param (OBJETO * dst) el objeto donde se copiara
*@param (OBJETO * orig) el objeto que se copiara
*@return STATUS OK si se copia el objeto correctamente
*@return STATUS ERROR si no se realiza la copia correctamente
------------------------------------------------------------------*/
extern STATUS copiaObjeto(OBJETO* dst,const OBJETO* org);

/*------------------------------------------------------------------
*@name destruyeObj
*@brief Destruye un objeto, liberando la memoria de este
*@param (OBJETO * obj) el objeto a destruir
*@return STATUS OK si elimina el entorno correctamente
*		ERROR_LM si no lo elimina correctamente
------------------------------------------------------------------*/
extern STATUS destruyeObj(OBJETO * obj);

/*------------------------------------------------------------------
*@name getIDObj
*@brief devuelve la IDobjeto
*@param (OBJETO * obj) el objeto del que se quiere la ID
*@return la ID del objeto
------------------------------------------------------------------*/
extern STATUS getIDObj(const OBJETO * obj, ID id);

/*------------------------------------------------------------------
*@name setIDObj
*@brief modifica la IDobjeto
*@param (OBJETO * obj) el objeto del que se quiere la ID
*@param (ID * id) id que tomara el objeto
*@return Devuelve si la función se ejecuto correctamente
------------------------------------------------------------------*/
extern STATUS setIDObj(OBJETO * obj,const ID id);

/*------------------------------------------------------------------
*@name posicionYObj
*@brief devuelve la posicion Y de un objeto
*@param (OBJETO * obj) objeto del que se quiere la posicion
*@return la posicion Y del objeto
------------------------------------------------------------------*/
extern STATUS getFilaObj(const OBJETO * obj,int* fila);

/*------------------------------------------------------------------
*@name setposYObj
*@brief CArga la posicion Y del objeto
*@param (OBJETO * obj, char * posY) el objeto donde se carga y la 
*        posicion Y a cargar
*@return STATUS OK si carga correctamente
*		ERROR si no carga correctamente
------------------------------------------------------------------*/
extern STATUS setFilaObj(OBJETO * obj,const int posY);

/*------------------------------------------------------------------
*@name posicionXObj
*@brief devuelve la posicion X de un objeto
*@param (OBJETO * obj) objeto del que se quiere la posicion
*@return la posicion X del objeto
------------------------------------------------------------------*/
extern STATUS getColumnaObj(const OBJETO * obj,int* columna);

/*------------------------------------------------------------------
*@name setposXObj
*@brief CArga la posicion X del objeto
*@param (OBJETO * obj, char * posX) el objeto donde se carga y la 
*        posicion X a cargar
*@return STATUS OK si carga correctamente
*		ERROR si no carga correctamente
------------------------------------------------------------------*/
extern STATUS setColumnaObj(OBJETO * obj,const int posX);

/*------------------------------------------------------------------
*@name nombreObj
*@brief devuelve el nombre de un objeto
*@param (OBJETO * obj) objeto del que se quiere el nombre
*@return el nombre del objeto
------------------------------------------------------------------*/
extern STATUS getNombreObj(const OBJETO * obj,char* nombre);

/*------------------------------------------------------------------
*@name setNombreObj
*@brief Carga el nombre del objeto
*@param (OBJETO * obj, char * nombre) el objeto donde se carga y el
*       nombre a cargar
*@return STATUS OK si carga correctamente
*		ERROR si no carga correctamente
------------------------------------------------------------------*/
extern STATUS setNombreObj(OBJETO * obj,const char * nombre);

/*------------------------------------------------------------------
*@name descripcionObj
*@brief devuelve la descripcion de un objeto
*@param (OBJETO * obj) objeto del que se quiere la descripcion
*@return la descripcion del objeto
------------------------------------------------------------------*/
extern STATUS getDescObj(const OBJETO * obj,char* desc);

/*------------------------------------------------------------------
*@name setDescObj
*@brief Carga la descripccion del objeto
*@param (OBJETO * obj, char * descripcion) el objeto dond e se carga
*       y la descripcion a cargar
*@return STATUS OK si se carga correctamente
*		ERROR si no carga correctamente
------------------------------------------------------------------*/
extern STATUS setDescObj(OBJETO * obj,const char * descripcion);

/*------------------------------------------------------------------
*@name getGraphObj
*@brief devuelve el caracter que representa al objeto
*@param (OBJETO * obj) el objeto del que se quiere el caracter
*@return el caracter del objeto
------------------------------------------------------------------*/
extern STATUS getGraphObj(const OBJETO * obj, char* graph);

/*------------------------------------------------------------------
*@name setGraphObj
*@brief Carga el caracter que representa al objeto
*@param (OBJETO * obj, char graph) el objeto dond e se carga
*       y el caracter a cargar
*@return STATUS OK si se carga correctamente
*		ERROR si no carga correctamente
------------------------------------------------------------------*/
extern STATUS setGraphObj(OBJETO * obj,const char graph);

/* Funciones para acceder a las propiedades del objeto */

/*------------------------------------------------------------------
*@name getMovil_obj
*@brief nos dice si un objeto se puede mover
*@param (OBJETO * obj) objeto del que queremos saber si es movible
*@return BOOL TRUE si se puede mover
*		FALSE si no se puede mover
------------------------------------------------------------------*/
extern BOOL getMovilObj(const OBJETO * obj);

/*------------------------------------------------------------------
*@name setMovilObj
*@brief Cambia si el objeto es movible o no, TRUE si se puede mover 
*        FALSE si no
*@param (OBJETO * obj, BOOL movil) objeto a modificar y propiedad 
*       (movil) a modificar
*@return BOOL TRUE si se puede mover
*		FALSE si no se puede mover
------------------------------------------------------------------*/
extern STATUS setMovilObj(OBJETO * obj,const BOOL movil);

/*------------------------------------------------------------------
*@name getMovido_obj
*@brief nos dice si un objeto ha sido movido
*@param (OBJETO * obj) objeto del que queremos saber si se ha movido
*@return BOOL TRUE si se ha movido
*		FALSE si no se ha movido
------------------------------------------------------------------*/
extern BOOL getMovidoObj(const OBJETO * obj);

/*------------------------------------------------------------------
*@name setMovividoObj
*@brief Cambia si el objeto se ha movido o no, TRUE si se ha movido 
*        FALSE si no
*@param (OBJETO * obj, BOOL movil) objeto a modificar y propiedad 
*       (movido) a modificar
*@return BOOL TRUE si se ha movido 
*		FALSE si no se ha movido
------------------------------------------------------------------*/
extern STATUS setMovidoObj(OBJETO * obj,const BOOL movido);

/*------------------------------------------------------------------
*@name getIlumina_obj
*@brief nos dice si un objeto ilumina
*@param (OBJETO * obj) objeto del que queremos saber si ilumina
*@return BOOL TRUE si ilumina
*		FALSE si no ilumina
------------------------------------------------------------------*/
extern BOOL getIluminaObj(const OBJETO * obj);

/*------------------------------------------------------------------
*@name setIluminaObj
*@brief Cambia si el objeto ilumina o no, TRUE si ilumina 
*        FALSE si no
*@param (OBJETO * obj, BOOL ilumina) objeto a modificar y propiedad 
*       (ilumina) a modificar
*@return BOOL TRUE si ilumina 
*		FALSE si no ilumina
------------------------------------------------------------------*/
extern STATUS setIluminaObj(OBJETO * obj,const BOOL ilumina);

/*------------------------------------------------------------------
*@name getEncendido_obj
*@brief nos dice si un objeto esta encendido
*@param (OBJETO * obj) objeto del que queremos saber si esta encendido
*@return BOOL TRUE si esta encendido 
*		FALSE si no esta encendido
------------------------------------------------------------------*/
extern BOOL getEncendidoObj(const OBJETO * obj);

/*------------------------------------------------------------------
*@name setEncendidoObj
*@brief Cambia si el objeto se ha esncendido o no, TRUE si se ha encendido 
*        FALSE si no
*@param (OBJETO * obj, BOOL encendido) objeto a modificar y propiedad 
*       (encendido) a modificar
*@return BOOL TRUE si se ha encendido
*		FALSE si no se ha encendido
------------------------------------------------------------------*/
extern STATUS setEncendidoObj(OBJETO * obj,const BOOL encendido);

/*------------------------------------------------------------------
*@name getRompible_obj
*@brief nos dice si un objeto es rompible
*@param (OBJETO * obj) objeto del que queremos saber si es rompible
*@return BOOL TRUE si es rompible
*		FALSE si no es rompible
------------------------------------------------------------------*/
extern BOOL getRompibleObj(const OBJETO * obj);

/*------------------------------------------------------------------
*@name setRompibleObj
*@brief Cambia si el objeto se puede romper o no, TRUE si se puede romper 
*        FALSE si no
*@param (OBJETO * obj, BOOL rompible) objeto a modificar y propiedad 
*       (rompible) a modificar
*@return BOOL TRUE si se se puede romper 
*		FALSE si no se puede romper
------------------------------------------------------------------*/
extern STATUS setRompibleObj(OBJETO * obj,const BOOL rompible);

/*------------------------------------------------------------------
*@name getRoto_obj
*@brief nos dice si un objeto esta roto
*@param (OBJETO * obj) objeto del que queremos saber si esta roto
*@return BOOL TRUE si esta roto
*		FALSE si no esta roto
------------------------------------------------------------------*/
extern BOOL getRotoObj(const OBJETO * obj);

/*------------------------------------------------------------------
*@name setRotoObj
*@brief Cambia si el objeto se ha roto o no, TRUE si se ha roto 
*        FALSE si no
*@param (OBJETO * obj, BOOL roto) objeto a modificar y propiedad 
*       (roto) a modificar
*@return BOOL TRUE si se ha roto 
*		FALSE si no se ha roto
------------------------------------------------------------------*/
extern STATUS setRotoObj(OBJETO * obj,const BOOL roto);

/*------------------------------------------------------------------
*@name getTeleport_obj
*@brief nos dice si un objeto teletrasnporta
*@param (OBJETO * obj) objeto del que queremos saber si teletrasnporta
*@return BOOL TRUE si teletrasnporta
*		FALSE si no teletrasnporta
------------------------------------------------------------------*/
extern BOOL getTeleportObj(const OBJETO * obj);

/*------------------------------------------------------------------
*@name setTeleportObj
*@brief Cambia si el objeto te puede teletransportar o no, TRUE si puede
*        FALSE si no
*@param (OBJETO * obj, BOOL teleport) objeto a modificar y propiedad 
*       (teleport) a modificar
*@return BOOL TRUE si te puede teletransportar 
*		FALSE si no te puede teletransportar
------------------------------------------------------------------*/
extern STATUS setTeleportObj(OBJETO * obj,const BOOL teleport);

/*------------------------------------------------------------------
*@name getDest_teleport_obj
*@brief nos dice donde teletrasnporta un objeto 
*@param (OBJETO * obj) objeto del que queremos saberdonde teletrasnporta
*@return la ID de donde te teletransporta
------------------------------------------------------------------*/
extern STATUS getDestTeleportObj(const OBJETO * obj, ID id);

/*------------------------------------------------------------------
*@name setdest_TeleportObj
*@brief Cambia el luegar donde te teletransporta el objeto(ID)
*@param (OBJETO * obj, ID id) id del lugar donde te teletransporta
*@return STATUS OK si carga correctamente
*		ERROR si no carga correctamente
------------------------------------------------------------------*/
extern STATUS setDestTeleportObj(OBJETO * obj,const ID id);

/* Imprime objeto. Esta función se incluye por motivos de depuración*/

/*------------------------------------------------------------------
*@name imprime_obj
*@brief Inicializa un entorno, reservando memoria para este
*@param ()
*@return Un entorno nuevo,  si reserva correctamente
------------------------------------------------------------------*/
extern STATUS imprime_obj(const OBJETO * obj);

#endif	/* OBJETOS_H */

