/******************************************************************************
*
*  Nombre del fichero: Lectorxml.h
*
*  Nombre del módulo correspondiente: Lectorxml.c
*
*  Descripción: Modulo para leer el mundo de los archivos xml.
*
*  Realizado por: Miguel Angel Gomez-Tavira
* (Basado en el módulo facilitado en moodle)
*
******************************************************************************/

#ifndef LECTOR_XML_H
#define LECTOR_XML_H

/*=== Cabeceras =============================================================*/
#include "mundo.h"
#include "entorno.h"
#include "inventario.h"
#include "objeto.h"
#include "pjsEntorno.h"
#include "personaje.h"
#include "tipos.h"
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

/*=== Definiciones ==========================================================*/
/* Máximo tamaño definido para un texto como valor de una etiqueta */
#define TAMANO_PAL 1024

/*******Etiquetas mundo********************/
#define MUN     	"mundo"
/*******Etiquetas entorno******************/
#define ENT     	"entorno"
#define NOM_ENT         "nombreEntorno"
#define DESC_ENT        "descEntorno"
#define INV_ENT         "invEntorno"
#define NOBJS_ENT       "numObjetosEntorno"
#define PJS_ENT         "pjsEntorno"
#define NPJS_ENT        "numPjsEntorno"
#define MAP_ENT         "mapaEntorno"
#define GRAPH_MAPA      "mapa"
#define COL_MAP         "colMapa"
#define FIL_MAP         "filMapa"
#define SALCOL          "salCol"
#define SALFIL          "salFil"
#define ENCOL		"enCol"
#define ENFIL		"enFil"
#define U_ENT           "unionesEntorno"
#define UNION           "union"
/*******Etiquetas objeto******************/
#define OBJ             "objeto"
#define FIL_OBJ         "filObjeto"
#define COL_OBJ         "colObjeto"
#define NOM_OBJ         "nombreObj"
#define DESC_OBJ        "descObj"
#define GRA_OBJ         "graphObj"
#define MOVIL           "movil"
#define MOVIDO          "movido"
#define ILUMINA         "ilumina"
#define ENCENDIDO       "encendido"
#define ROMPIBLE        "rompible"
#define ROTO            "roto"
#define TELE            "teleport"
#define DEST_TELE       "destTeleport"
/*******Etiquetas personaje**************/
#define PJ              "personaje"
#define FIL_PJ          "filPj"
#define COL_PJ          "colPj"
#define NOM_PJ          "nombrePj"
#define DES_PJ          "descPj"
#define GRA_PJ          "graphPj"
#define INV_PJ          "invPj"
#define VIT             "vitalidad"
#define VIT_TOT         "vitTotal"
#define FZA             "fuerza"
#define DEF             "defensa"
#define INTER           "interactuar"
#define ATK             "atacable"

/*Definiciones para el control de errores*/
typedef enum _xml_RETURN {
    ERRXML = -1,
    OKXML = 0
} xml_RETURN;


/***Funciones para Mundo*******************************************************/
/*------------------------------------------------------------------
 *@name procesaMundo
 *@brief Procesa el archivo xml iniciando mundo.
 *@param (char * nomfich)
 *@param (MUNDO* m)
 *@return -  OKXML, si se ha terminado sin problemas.
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaMundo(char* nomfich, MUNDO* m);

/***Funciones para Entorno*****************************************************/
/*------------------------------------------------------------------
 *@name procesaEntorno
 *@brief Lee de un fichero xml los datos de un entorno y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (ENTORNO    * ent)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaEntorno(xmlDocPtr doc, xmlNodePtr cur, ENTORNO * ent);

/*------------------------------------------------------------------
 *@name procesaNombreEntorno
 *@brief Lee de un fichero xml el nombre de un entorno y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (ENTORNO    * ent)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaNombreEntorno(xmlDocPtr doc, xmlNodePtr cur, ENTORNO * ent);

/*------------------------------------------------------------------
 *@name procesaDescEntorno
 *@brief Lee de un fichero xml la descripción de un entorno y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (ENTORNO    * ent)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaDescEntorno(xmlDocPtr doc, xmlNodePtr cur, ENTORNO * ent);

/*------------------------------------------------------------------
 *@name procesaInvEntorno
 *@brief Lee de un fichero xml el inv de un entorno y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (ENTORNO    * ent)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaInvEntorno(xmlDocPtr doc, xmlNodePtr cur, ENTORNO * ent);

/*------------------------------------------------------------------
 *@name procesaNumObjsEntorno
 *@brief Lee de un fichero xml el número de objetos de un entorno y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (ENTORNO    * ent)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaNumObjsEntorno(xmlDocPtr doc, xmlNodePtr cur, ENTORNO * ent);

/*------------------------------------------------------------------
 *@name procesaPjsEntorno
 *@brief Lee de un fichero xml los PjsEntorno de un entorno y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (ENTORNO    * ent)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaPjsEntorno(xmlDocPtr doc, xmlNodePtr cur, ENTORNO * ent);

/*------------------------------------------------------------------
 *@name procesaNumPjsEntorno
 *@brief Lee de un fichero xml el número de pjs de un entorno y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (ENTORNO    * ent)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaNumPjsEntorno(xmlDocPtr doc, xmlNodePtr cur, ENTORNO * ent);

/*------------------------------------------------------------------
 *@name procesaMapaEntorno
 *@brief Lee de un fichero xml el mapa de un entorno y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (ENTORNO    * ent)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaMapaEntorno(xmlDocPtr doc, xmlNodePtr cur, ENTORNO * ent);

/*------------------------------------------------------------------
 *@name procesaUnionesEntorno
 *@brief Lee de un fichero xml las uniones de un entorno y las carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (ENTORNO    * ent)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaUnionesEntorno(xmlDocPtr doc, xmlNodePtr cur, ENTORNO * ent);

/***Funciones para Objetos*****************************************************/
/*------------------------------------------------------------------
 *@name procesaObjeto
 *@brief Lee de un fichero xml los datos de un objeto y los carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (OBJETO    * obj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj);

/*------------------------------------------------------------------
 *@name procesaFilObjeto
 *@brief Lee de un fichero xml la fila de un objeto y la carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (OBJETO    * obj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaFilObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj);

/*------------------------------------------------------------------
 *@name procesaObjeto
 *@brief Lee de un fichero xml la columna de un objeto y la carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (OBJETO    * obj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaColObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj);

/*------------------------------------------------------------------
 *@name procesaObjeto
 *@brief Lee de un fichero xml el nombre de un objeto y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (OBJETO    * obj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaNombreObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj);

/*------------------------------------------------------------------
 *@name procesaObjeto
 *@brief Lee de un fichero xml la descripción de un objeto y la carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (OBJETO    * obj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaDescObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj);

/*------------------------------------------------------------------
 *@name procesaGraphObjeto
 *@brief Lee de un fichero xml el gráfico de un objeto y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (OBJETO    * obj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaGraphObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj);

/*------------------------------------------------------------------
 *@name procesaMovilObjeto
 *@brief Lee de un fichero xml si un objeto es movil y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (OBJETO    * obj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaMovilObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj);

/*------------------------------------------------------------------
 *@name procesaMovidoObjeto
 *@brief Lee de un fichero xml si un objeto se ha movido y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (OBJETO    * obj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaMovidoObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj);

/*------------------------------------------------------------------
 *@name procesaIluminaObjeto
 *@brief Lee de un fichero xml si un objeto se ilumina y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (OBJETO    * obj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaIluminaObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj);

/*------------------------------------------------------------------
 *@name procesaEncendidoObjeto
 *@brief Lee de un fichero xml si un objeto está encendido y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (OBJETO    * obj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaEncendidoObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj);

/*------------------------------------------------------------------
 *@name procesaRompibleObjeto
 *@brief Lee de un fichero xml si un objeto se puede romper y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (OBJETO    * obj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaRompibleObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj);

/*------------------------------------------------------------------
 *@name procesaRotoObjeto
 *@brief Lee de un fichero xml si un objeto está roto y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (OBJETO    * obj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaRotoObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj);

/*------------------------------------------------------------------
 *@name procesaTeleportObjeto
 *@brief Lee de un fichero xml si un objeto teletransporta y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (OBJETO    * obj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaTeleportObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj);

/*------------------------------------------------------------------
 *@name procesaDestTeleportObjeto
 *@brief Lee de un fichero xml el destino de un objeto con teletransporte y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (OBJETO    * obj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaDestTeleportObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj);

/***Funciones para Personajes**************************************************/
/*------------------------------------------------------------------
 *@name procesaPersonaje
 *@brief Lee de un fichero xml los datos de un pj y los carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (PERSONAJE  * pj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaPersonaje(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj);

/*------------------------------------------------------------------
 *@name procesaFilPj
 *@brief Lee de un fichero xml la fila de un pj y la carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (PERSONAJE  * pj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaFilPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj);

/*------------------------------------------------------------------
 *@name procesaColPj
 *@brief Lee de un fichero xml la columna de un pj y la carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (PERSONAJE  * pj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaColPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj);

/*------------------------------------------------------------------
 *@name procesaNombrePj
 *@brief Lee de un fichero xml el nombre de un pj y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (PERSONAJE  * pj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaNombrePj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj);

/*------------------------------------------------------------------
 *@name procesaDescPj
 *@brief Lee de un fichero xml la descripción de un pj y la carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (PERSONAJE  * pj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaDescPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj);

/*------------------------------------------------------------------
 *@name procesaGraphPj
 *@brief Lee de un fichero xml el gráfico de un pj y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (PERSONAJE  * pj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaGraphPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj);

/*------------------------------------------------------------------
 *@name procesaInvPj
 *@brief Lee de un fichero xml el inventario de un pj y lo carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (PERSONAJE  * pj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaInvPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj);

/*------------------------------------------------------------------
 *@name procesaVitPj
 *@brief Lee de un fichero xml la vitalidad de un pj y la carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (PERSONAJE  * pj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaVitPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj);

/*------------------------------------------------------------------
 *@name procesaVitTotPj
 *@brief Lee de un fichero xml la vitalidad total de un pj y la carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (PERSONAJE  * pj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaVitTotPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj);

/*------------------------------------------------------------------
 *@name procesaFzaPj
 *@brief Lee de un fichero xml la fuerza de un pj y la carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (PERSONAJE  * pj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaFzaPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj);

/*------------------------------------------------------------------
 *@name procesaDefPj
 *@brief Lee de un fichero xml la defensa de un pj y la carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (PERSONAJE  * pj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaDefPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj);

/*------------------------------------------------------------------
 *@name procesaIntPj
 *@brief Lee de un fichero xml la capacidad para interactuar de un pj y la carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (PERSONAJE  * pj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaIntPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj);

/*------------------------------------------------------------------
 *@name procesaAtkPj
 *@brief Lee de un fichero xml la capacidad para atacar a un pj y la carga en memoria.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (PERSONAJE  * pj)
 *@return -  OKXML, si se ha terminado sin problemas
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaAtkPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj);

/*Funciones para Mapa**********************************************************/
/*------------------------------------------------------------------
 *@name procesaMapa
 *@brief Lee de un fichero xml los datos de el mapa del entorno.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (MAPA  * map)
 *@return -  OKXML, si se ha terminado sin problemas.
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaMapa(xmlDocPtr doc, xmlNodePtr cur, MAPA * map);

/*------------------------------------------------------------------
 *@name procesaColMapa
 *@brief Lee de un fichero xml las columnas del mapa del entorno.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (MAPA  * map)
 *@return -  OKXML, si se ha terminado sin problemas.
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaColMapa(xmlDocPtr doc, xmlNodePtr cur, MAPA * map);

/*------------------------------------------------------------------
 *@name procesaFilMapa
 *@brief Lee de un fichero xml las filas del mapa del entorno.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (MAPA  * map)
 *@return -  OKXML, si se ha terminado sin problemas.
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaFilMapa(xmlDocPtr doc, xmlNodePtr cur, MAPA * map);

/*------------------------------------------------------------------
 *@name procesaSalCol
 *@brief Lee de un fichero xml la columna de salida del pj en el mapa del entorno.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (MAPA  * map)
 *@return -  OKXML, si se ha terminado sin problemas.
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaSalCol(xmlDocPtr doc, xmlNodePtr cur, MAPA * map);

/*------------------------------------------------------------------
 *@name procesaSalFil
 *@brief Lee de un fichero xml la fila de salida del pj en el mapa del entorno.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (MAPA  * map)
 *@return -  OKXML, si se ha terminado sin problemas.
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaSalFil(xmlDocPtr doc, xmlNodePtr cur, MAPA * map);

/*------------------------------------------------------------------
 *@name procesaEnCol
 *@brief Lee de un fichero xml la columna de salida del pj en el mapa del entorno.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (MAPA  * map)
 *@return -  OKXML, si se ha terminado sin problemas.
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaEnCol(xmlDocPtr doc, xmlNodePtr cur, MAPA * map);

/*------------------------------------------------------------------
 *@name procesaEnFil
 *@brief Lee de un fichero xml la fila de salida del pj en el mapa del entorno.
 *@param (xmlDocPtr  * doc)
 *@param (xmlNodePtr * cur) 
 *@param (MAPA  * map)
 *@return -  OKXML, si se ha terminado sin problemas.
          - ERRXML, si se ha producido algún tipo de error.
------------------------------------------------------------------*/
extern xml_RETURN procesaEnFil(xmlDocPtr doc, xmlNodePtr cur, MAPA * map);

#endif /*LECTOR_XML_H*/
