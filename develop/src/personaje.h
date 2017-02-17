/******************************************************************************
 *
 *  Nombre del fichero: personaje.h
 *
 *  Nombre del módulo correspondiente: personaje
 *
 *  Descripción: 
 *
 *  Realizado por: Diego Chicote
 *
 ******************************************************************************/
#ifndef PERSONAJE_H
#define	PERSONAJE_H

/*=== Cabeceras =============================================================*/
#include "inventario.h"

/*=== Definiciones ==========================================================*/
#define MAX_NOM_PJ 30
#define MAX_DES_PJ 1000

typedef struct {
    ID id;
    int columna;
    int fila;
    char* nombre;
    char* descripcion;
    char graphPJ;
    INVENTARIO* inv;
    int vit;
    int vitTot;
    int fuerza;
    int defensa;

    BOOL interactuar; /*hablar*/
    BOOL atacable;

} PERSONAJE;

/*=== Prototipos de Funciones ===============================================*/
/*------------------------------------------------------------------
 *@name iniPj
 *@brief Inicializa un personaje, reservando memoria para este
 *@param (ID id) Id del personaje
 *@return Un personaje nuevo,  si reserva correctamente
------------------------------------------------------------------*/
extern STATUS iniPj(PERSONAJE* pj);

/*------------------------------------------------------------------
 *@name copiaPj
 *@brief Inicializa un personaje, reservando memoria para este
 *@param (ID id) Id del personaje
 *@return Un personaje nuevo,  si reserva correctamente
------------------------------------------------------------------*/
extern STATUS copiaPj(PERSONAJE* dst,const PERSONAJE* org);

/*------------------------------------------------------------------
 *@name destruyePj
 *@brief Destruye un personaje, liberando la memoria de este
 *@param (PERSONAJE * pj) el personaje a destruir
 *@return STATUS OK si elimina el personaje correctamente
 *		ERROR_LM si no lo elimina correctamente
------------------------------------------------------------------*/
extern STATUS destruyePj(PERSONAJE * pj);

/*------------------------------------------------------------------
 *@name setDescPj
 *@brief Carga la descripccion del objeto
 *@param (PERSONAJE * pj, char * descripcion) el personaje donde se carga
 *       y la descripcion a cargar
 *@return STATUS OK si se carga correctamente
 *		ERROR si no carga correctamente
------------------------------------------------------------------*/
extern STATUS setDescPj(PERSONAJE * pj, const char * descPj);

/*------------------------------------------------------------------
 *@name setGraphPj
 *@brief Carga el caracter que representa al personaje
 *@param (PERSONAJE * pj, char graph) el personaje dond e se carga
 *       y el caracter a cargar
 *@return STATUS OK si se carga correctamente
 *		ERROR si no carga correctamente
------------------------------------------------------------------*/
extern STATUS setGraphPj(PERSONAJE * pj, const char graphPj);

/*------------------------------------------------------------------
 *@name setposXPj
 *@brief CArga la posicion X del personaje
 *@param (PERSONAJE * pj, char * posX) el personaje donde se carga y la 
 *        posicion X a cargar
 *@return STATUS OK si carga correctamente
 *		ERROR si no carga correctamente
------------------------------------------------------------------*/
extern STATUS setColPj(PERSONAJE * pj, const int col);

/*------------------------------------------------------------------
 *@name setposYPj
 *@brief CArga la posicion Y del personaje
 *@param (PERSONAJE * pj, char * posY) el personaje donde se carga y la 
 *        posicion Y a cargar
 *@return STATUS OK si carga correctamente
 *		ERROR si no carga correctamente
------------------------------------------------------------------*/
extern STATUS setFilaPj(PERSONAJE * pj, const int fila);

/*------------------------------------------------------------------
 *@name setNombrePj
 *@brief Carga el nombre del personaje
 *@param (PERSONAJE * pj, char * nombre) el persoanje donde se carga y el
 *       nombre a cargar
 *@return STATUS OK si carga correctamente
 *		ERROR si no carga correctamente
------------------------------------------------------------------*/
extern STATUS setNombrePj(PERSONAJE * pj, const char * nombrePj);

/*------------------------------------------------------------------
 *@name setInventarioPj
 *@brief Carga el inventario del personaje
 *@param (PERSONAJE * pj, INVENTARIO *inv ) el persoanje donde se carga y el
 *       inventario a cargar
 *@return STATUS OK si carga correctamente
 *		ERROR si no carga correctamente
------------------------------------------------------------------*/
extern STATUS setInventarioPj(PERSONAJE * pj, INVENTARIO * invPj);

/*------------------------------------------------------------------
 *@name setVitalidadPj
 *@brief Carga la vitalidad del personaje
 *@param (PERSONAJE * pj, unsigned int vitalidad) el persoanje donde se 
 *        carga la vitalidad a cargar
 *@return STATUS OK si carga correctamente
 *		ERROR si no carga correctamente
------------------------------------------------------------------*/
extern STATUS setVitPj(PERSONAJE * pj, const int vit);

/*------------------------------------------------------------------
 *@name setVitalidadPj
 *@brief Carga la vitalidad del personaje
 *@param (PERSONAJE * pj, unsigned int vitalidad) el persoanje donde se 
 *        carga la vitalidad a cargar
 *@return STATUS OK si carga correctamente
 *		ERROR si no carga correctamente
------------------------------------------------------------------*/
extern STATUS setVitTotPj(PERSONAJE * pj, const int vitTot);

/*------------------------------------------------------------------
 *@name setFuerzaPj
 *@brief Carga el nombre del personaje
 *@param (PERSONAJE * pj, unsigned int fuerza) el persoanje donde se 
 *        carga la fuerza a cargar
 *@return STATUS OK si carga correctamente
 *		ERROR si no carga correctamente
------------------------------------------------------------------*/
extern STATUS setFuerzaPj(PERSONAJE * pj, const int fza);

/*------------------------------------------------------------------
 *@name setDefensaPj
 *@brief Carga el nombre del personaje
 *@param (PERSONAJE * pj, unsigned int defensa) el persoanje donde se 
 *        carga la defensa a cargar
 *@return STATUS OK si carga correctamente
 *		ERROR si no carga correctamente
------------------------------------------------------------------*/
extern STATUS setDefensaPj(PERSONAJE * pj, const int def);

/*------------------------------------------------------------------
 *@name setInteractuarPj
 *@brief Carga el nombre del personaje
 *@param (PERSONAJE * pj, char * nombre) el persoanje donde se carga y el
 *       nombre a cargar
 *@return STATUS OK si carga correctamente
 *		ERROR si no carga correctamente
------------------------------------------------------------------*/
extern STATUS setInteractuarPj(PERSONAJE * pj, const BOOL interactuar);

/*------------------------------------------------------------------
 *@name setAtacablePj
 *@brief Carga el nombre del personaje
 *@param (PERSONAJE * pj, char * nombre) el persoanje donde se carga y el
 *       nombre a cargar
 *@return STATUS OK si carga correctamente
 *		ERROR si no carga correctamente
------------------------------------------------------------------*/
extern STATUS setAtacablePj(PERSONAJE * pj,const BOOL atacable);

/* Funciones para acceder a las propiedades del objeto */

/*------------------------------------------------------------------
 *@name getIDPj
 *@brief devuelve la ID personaje
 *@param (PERSONAJE * pj) el personaje del que se quiere la ID
 *@return la ID del personaje
------------------------------------------------------------------*/
extern STATUS getIDPj(const PERSONAJE * pj, ID id);

/*------------------------------------------------------------------
 *@name getIDPj
 *@brief devuelve la ID personaje
 *@param (PERSONAJE * pj) el personaje del que se quiere la ID
 *@return la ID del personaje
------------------------------------------------------------------*/
extern STATUS setIdPj(PERSONAJE* pj, const ID id);

/*------------------------------------------------------------------
 *@name descripcionPj
 *@brief devuelve la descripcion de un personaje
 *@param (PERSONAJE * pj) personaje del que se quiere la descripcion
 *@return la descripcion del personaje
------------------------------------------------------------------*/
extern STATUS getDescPj(const PERSONAJE * pj, char* descPj);

/*------------------------------------------------------------------
 *@name nombrePj
 *@brief devuelve el nombre de un personaje
 *@param (PERSONAJE * pj) personaje del que se quiere el nombre
 *@return el nombre del personaje
------------------------------------------------------------------*/
extern STATUS getNombrePj(const PERSONAJE * pj, char* nombrePj);

/*------------------------------------------------------------------
 *@name getGraphPj
 *@brief devuelve el caracter que representa al personaje
 *@param (PERSONAJE * pj) el personaje del que se quiere el caracter
 *@return el caracter del personaje
------------------------------------------------------------------*/
extern STATUS getGraphPj(const PERSONAJE * pj, char* graphPj);

/*------------------------------------------------------------------
 *@name posicionXPj
 *@brief devuelve la posicion X de un personaje
 *@param (PERSONAJE * pj) personaje del que se quiere la posicion
 *@return la posicion X del personaje
------------------------------------------------------------------*/
extern STATUS getColPj(const PERSONAJE * pj, int* col);

/*------------------------------------------------------------------
 *@name posicionYPj
 *@brief devuelve la posicion Y de un personaje
 *@param (PERSONAJE * pj) personaje del que se quiere la posicion
 *@return la posicion Y del personaje
------------------------------------------------------------------*/
extern STATUS getFilaPj(const PERSONAJE * pj, int* fila);

/*------------------------------------------------------------------
 *@name getInventarioPj
 *@brief devuelve el inventario de un personaje
 *@param (PERSONAJE * pj) personaje del que queremos el inventario
 *@return el invenario del personaje
------------------------------------------------------------------*/
extern STATUS getInventarioPj(const PERSONAJE * pj, INVENTARIO** invPj);
/*------------------------------------------------------------------
 *@name getObjetoInv
 *@brief nos da el objeto buscado del inventario del pj
 *@param (PERSONAJE * pj) personaje donde buscar
 *@return objeto buscado 
------------------------------------------------------------------*/
OBJETO * getObjetoInv(const PERSONAJE * pj, char * nom);
/*------------------------------------------------------------------
 *@name getVitalidadPj
 *@brief nos dice la vitalidad de un personaje
 *@param (PERSONAJE * pj) personaje del que queremos saber su vitalidad
 *@return vitalidad del personaje
------------------------------------------------------------------*/

extern STATUS getVitPj(const PERSONAJE * pj, int* vit);

/*------------------------------------------------------------------
 *@name getVitalidadPj
 *@brief nos dice la vitalidad de un personaje
 *@param (PERSONAJE * pj) personaje del que queremos saber su vitalidad
 *@return vitalidad del personaje
------------------------------------------------------------------*/
extern STATUS getVitTotPj(const PERSONAJE * pj, int* vitTot);

/*------------------------------------------------------------------
 *@name getFuerzaPj
 *@brief nos dice la fuerza de un personaje
 *@param (PERSONAJE * pj) personaje del que queremos saber su fuerza
 *@return fuerza del personaje
------------------------------------------------------------------*/
extern STATUS getFuerzaPj(const PERSONAJE * pj, int* fza);

/*------------------------------------------------------------------
 *@name getDefensaPj
 *@brief nos dice la defensa de un personaje
 *@param (PERSONAJE * pj) personaje del que queremos saber su defensa
 *@return defensa del personaje
------------------------------------------------------------------*/
extern STATUS getDefensaPj(const PERSONAJE * pj, int* def);

/*------------------------------------------------------------------
 *@name getInteractuarPj
 *@brief nos dice si se puede hablar con el personaje
 *@param (PERSONAJE * pj) personaje del que queremos saber si podemos interactuar
 *@return BOOL VERDADERO si se puede interactuar
 *		FALSO si no se puede interactuar
------------------------------------------------------------------*/
extern STATUS getInteractuarPj(const PERSONAJE * pj, BOOL* interactuar);

/*------------------------------------------------------------------
 *@name getAtacablePj
 *@brief nos dice si un personaje se puede atacar
 *@param (PERSONAJE * pj) personaje del que queremos saber si es atacable
 *@return BOOL VERDADERO si se puede atacar
 *		FALSO si no se puede atacar
------------------------------------------------------------------*/
extern STATUS getAtacablePj(const PERSONAJE * pj, BOOL* atacable);

/*****************************************************************************/

#endif	/* PERSONAJE_H */

