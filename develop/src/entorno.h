/******************************************************************************
*
*  Nombre del fichero: entorno.h
*
*  Nombre del módulo correspondiente: entorno.c
*
*  Descripción: Estructuras del entorno
*
*  Realizado por: Diego Chicote
*
******************************************************************************/

#ifndef ENTORNO_H
#define	ENTORNO_H

/*=== Cabeceras =============================================================*/
#include "tipos.h"
#include "inventario.h"
#include "pjsEntorno.h"

/*=== Definiciones ==========================================================*/

#define MAX_NOM_ENT 30
#define MAX_DES_ENT 300
#define MAX_UNIONES 2

typedef struct{
    char**       mapa;
    int          columnas;   /*Número de columnas del mapa.*/
    int          filas;      /*Número de filas del mapa.*/
    int          salCol;     /*Columna en la que aparece el personaje, al avanzar entorno.*/
    int          salFil;     /*Fila en la que aparece el personaje, al avanzar entorno.*/
    int		 enCol;	     /*Columna en la que aparece el personaje, al retroceder entorno.*/
    int		 enFil;	     /*Fila en la que aparece el personaje, al retroceder entorno.*/
}MAPA;

/* La estructura ENTORNO lleva el control de los entornos en los que se
 * desarrolla el juego.
 */
typedef struct{

    ID           id;         /*Nombre que identifica el entorno.*/
    char*        nombre;     /*Nombre genérico del entorno.*/
    char*        descripcion;/*Descripción del entrono.*/
    INVENTARIO*  invEnt;     /*Objetos que se encuentran en el entrono.*/
    int          numObjEnt;  /*Número de objetos del entrono.*/
    PJSENTORNO*  pjsEnt;     /*Personajes del entorno.*/
    int          numPjsEnt;  /*Número de objetos del entorno.*/
    MAPA*        mapaEnt;    /*Mapa del entorno.*/
    /*ID*          uniones;    Conexiones del entorno con otros entornos.*/
}ENTORNO;

/***Entorno********************************************************/
/*------------------------------------------------------------------
*@name iniEntrono
*@brief Inicializa un entorno, reservando memoria para este
*@param ()
*@return Un entorno nuevo,  si reserva correctamente
------------------------------------------------------------------*/
extern STATUS iniEntorno(ENTORNO* ent);
/*------------------------------------------------------------------
*@name copiaEntorno
*@brief Copia el entorno origen en el entorno destino
*@param (ENTORNO * dst) el objeto donde se copiara
*@param (ENTORNO * orig) el objeto que se copiara
*@return STATUS OK si se copia el objeto correctamente
*@return STATUS ERROR si no se realiza la copia correctamente
------------------------------------------------------------------*/
extern STATUS copiaEntorno(ENTORNO* dst,const ENTORNO* org);
/*------------------------------------------------------------------
*@name destruirEntorno
*@brief Destruye un entorno, liberando  la memoria de este
*@param (ENTORNO * ent) el entrono a destruir
*@return STATUS OK si elimina el entorno correctamente
*		ERROR si no lo elimina correctamente
------------------------------------------------------------------*/
extern STATUS destruirEntorno(ENTORNO * ent);

/*------------------------------------------------------------------
*@name getIdEnt
*@brief Devuelve la ID de un entorno
*@param (ENTORNO * ent) entorno del que se quiere la ID
*@return Devuelve la ID del entorno
------------------------------------------------------------------*/
extern STATUS getIdEnt(const ENTORNO *ent,ID idEnt);

/*------------------------------------------------------------------
*@name setIdEnt
*@brief Modifica la ID de un entorno
*@param (ENTORNO * ent) entorno del que se le modifica la ID
*@param (ID * id) ID que recibira el entorno
*@return Devuelve si se realizo correctamente
------------------------------------------------------------------*/
extern STATUS setIdEnt(ENTORNO *ent,const ID id);

/*------------------------------------------------------------------
*@name getNombreEnt
*@brief Da el nombre de un entorno
*@param (ENTORNO * ent) entorno del que se quiere el nombre
*@return Devuelve el nombre del entorno
------------------------------------------------------------------*/
extern STATUS getNombreEnt(const ENTORNO *ent,char * nombreEnt);

/*------------------------------------------------------------------
*@name setNombreEnt
*@brief Cambia el nombre del entorno
*@param (ENTORNO * ent) entorno al que se cambiara el nombre
*@param (cont char* nombre) nombre que recibira el entorno
*@return Devuelve si se realizo correctamente
------------------------------------------------------------------*/
extern STATUS setNombreEnt(ENTORNO* ent, const char* nombreEnt);

/*------------------------------------------------------------------
*@name getDescripcionEnt
*@brief Da la descripción del entorno
*@param (ENTORNO * ent) entorno del que se quiere la descripcion
*@return Devuelve la descripción del entorno
------------------------------------------------------------------*/
extern STATUS getDescripcionEnt(const ENTORNO *ent,char * descEnt);

/*------------------------------------------------------------------
*@name setDescripcionEnt
*@brief Cambia la descripción del entorno
*@param (ENTORNO * ent) entorno al que se cambiara la descripcion
*@param (char * desc) descripción que se asigna al entorno
*@return Devuelve si se realizo correctamente
------------------------------------------------------------------*/
extern STATUS setDescripcionEnt(ENTORNO* ent,const char* descEnt);

/*------------------------------------------------------------------
*@name getMapaEnt
*@brief Da la el mapa de caracteres de un entorno
*@param (ENTORNO * ent) entorno del que se quiere el mapa de caracteres
*@return STATUS OK si elimina el entorno correctamente
*		ERROR si no lo elimina correctamente
------------------------------------------------------------------*/
extern STATUS getMapaEnt(const ENTORNO *ent,MAPA** mapaEnt);
/*------------------------------------------------------------------
*@name setMapaEnt
*@brief Cargan el mapa de caracteres de un entorno
*@param (ENTORNO * ent) entorno del que se carga el mapa de caracteres
*@return STATUS OK si elimina el entorno correctamente
*		ERROR si no lo elimina correctamente
------------------------------------------------------------------*/
extern STATUS setMapaEnt(ENTORNO*ent,MAPA* mapaEnt);
/*------------------------------------------------------------------
*@name getObjetoEnt
*@brief Da el objeto buscado por nombre
*@param (ENTORNO * ent , char * nom) entorno del que se quiere el objeto
*@return OBJETO * buscado
*		NULL si no lo encuentra.
------------------------------------------------------------------*/
OBJETO * getObjetoEnt(ENTORNO *ent,const char * nom);
/*------------------------------------------------------------------
*@name getPersonajeEnt
*@brief Da el personaje buscado por nombre
*@param (ENTORNO * ent, char * nom) entorno del que se quiere el personaje
*@return PERSONAJE * buscado
*		NULL si no lo encuentra.
------------------------------------------------------------------*/
PERSONAJE * getPersonajeEnt(ENTORNO *ent, const char * nom);
/*------------------------------------------------------------------
*@name annadirInventario
*@brief Añade el inventario al entorno
*@param (ENTORNO * ent INVENTARIO *inv) entorno donde cargar el inventario de objeto.
*@return STATUS OK si elimina el entorno correctamente
*		ERROR si no lo elimina correctamente
------------------------------------------------------------------*/
extern STATUS annadirInventario(ENTORNO *ent,INVENTARIO *inv);
/*------------------------------------------------------------------
*@name annadirPjsEnt
*@brief Añade los personajes al entorno
*@param (ENTORNO * ent ,PJSENTORNO *pj) entorno donde cargar los personajes.
*@return OBJETO * buscado
*		NULL si no lo encuentra.
------------------------------------------------------------------*/
extern STATUS annadirPjsEnt(ENTORNO *ent,PJSENTORNO *pj);

/*------------------------------------------------------------------
*@name cargarEntorno
*@brief Cargar un entorno de un fichero
*@param (FILE*file,ENTORNO *ent) el entorno a cargar y el fichero
*@return STATUS OKE si carga el entorno correctamente
*		ERROR si no lo carga correctamente
------------------------------------------------------------------*/
extern STATUS cargarEntorno(ENTORNO *ent,FILE* f);

/*------------------------------------------------------------------
 *@name guardarEntorno
 *@brief Guardar un entorno en un fichero. 
 *@param (FILE*file,ENTORNO *ent) el entorno a guardar
 *        y el fichero donde guardarlo
 *@return STATUS OKE si guarda el entorno correctamente
 *		ERROR si no lo guarda correctamente
------------------------------------------------------------------*/
extern STATUS guardarEntorno(FILE * file,ENTORNO * ent);

/****Mapa**********************************************************/
/*------------------------------------------------------------------
 *@name getColMap
 *@brief Devuelve el número de columnas de un mapa.
 *@param (const MAPA * map) puntero al mapa.
 *@param (int * col) puntero al número de columnas del mapa.
 *@return STATUS -  OKE, si devuelve el número de columnas.
 *               -ERROR, si no completa la operación.
------------------------------------------------------------------*/
extern STATUS getColMap(const MAPA *map,int* col);

/*------------------------------------------------------------------
 *@name setColMap
 *@brief Establece el número de columnas de un mapa.
 *@param (MAPA * map) puntero al mapa.
 *@param (const int * col) puntero al número de columnas del mapa.
 *@return STATUS -  OKE, si cambia el número de columnas.
 *               -ERROR, si no completa la operación.
------------------------------------------------------------------*/
extern STATUS setColMap(MAPA *map,const int col);

/*------------------------------------------------------------------
 *@name getFilMap
 *@brief Devuelve el número de filas de un mapa.
 *@param (const MAPA * map) puntero al mapa.
 *@param (int * fil) puntero al número de filas del mapa.
 *@return STATUS -  OKE, si devuelve el número de filas.
 *               -ERROR, si no completa la operación.
------------------------------------------------------------------*/
extern STATUS getFilMap(const MAPA *map,int* fil);

/*------------------------------------------------------------------
 *@name setFilMap
 *@brief Establece el número de filas de un mapa.
 *@param (MAPA * map) puntero al mapa.
 *@param (const int * fil) puntero al número de filas del mapa.
 *@return STATUS -  OKE, si cambia el número de filas.
 *               -ERROR, si no completa la operación.
------------------------------------------------------------------*/
extern STATUS setFilMap(MAPA *map,const int fil);

/*------------------------------------------------------------------
 *@name getSalCol
 *@brief Devuelve la columna en la se pinta el jugador de un mapa.
 *@param (const MAPA * map) puntero al mapa.
 *@param (int * col) puntero la columna.
 *@return STATUS -  OKE, si devuelve la columna.
 *               -ERROR, si no completa la operación.
------------------------------------------------------------------*/
extern STATUS getSalCol(const MAPA *map,int *col);

/*------------------------------------------------------------------
 *@name setSalCol
 *@brief Establece la columna en la se pinta el jugador de un mapa.
 *@param (MAPA * map) puntero al mapa.
 *@param (const int * col) puntero a la columna.
 *@return STATUS -  OKE, si cambia la columna.
 *               -ERROR, si no completa la operación.
------------------------------------------------------------------*/
extern STATUS setSalCol(MAPA *map,const int col);

/*------------------------------------------------------------------
 *@name getSalFil
 *@brief Devuelve la fila en la se pinta el jugador de un mapa.
 *@param (const MAPA * map) puntero al mapa.
 *@param (int * fil) puntero a la fila.
 *@return STATUS -  OKE, si devuelve la fila.
 *               -ERROR, si no completa la operación.
------------------------------------------------------------------*/
extern STATUS getSalFil(const MAPA *map,int* fil);

/*------------------------------------------------------------------
 *@name setSalFil
 *@brief Establece la fila en la se pinta el jugador de un mapa.
 *@param (MAPA * map) puntero al mapa.
 *@param (const int * fil) puntero a la fila.
 *@return STATUS -  OKE, si cambia la columna.
 *               -ERROR, si no completa la operación.
------------------------------------------------------------------*/
extern STATUS setSalFil(MAPA *map,const int fil);

/*------------------------------------------------------------------
 *@name getEnCol
 *@brief Devuelve la columna en la se pinta el jugador de un mapa.
 *@param (const MAPA * map) puntero al mapa.
 *@param (int * col) puntero la columna.
 *@return STATUS -  OKE, si devuelve la columna.
 *               -ERROR, si no completa la operación.
------------------------------------------------------------------*/
extern STATUS getEnCol(const MAPA *map,int *col);

/*------------------------------------------------------------------
 *@name setEnCol
 *@brief Establece la columna en la se pinta el jugador de un mapa.
 *@param (MAPA * map) puntero al mapa.
 *@param (const int * col) puntero a la columna.
 *@return STATUS -  OKE, si cambia la columna.
 *               -ERROR, si no completa la operación.
------------------------------------------------------------------*/
extern STATUS setEnCol(MAPA *map,const int col);

/*------------------------------------------------------------------
 *@name getEnFil
 *@brief Devuelve la fila en la se pinta el jugador de un mapa.
 *@param (const MAPA * map) puntero al mapa.
 *@param (int * fil) puntero a la fila.
 *@return STATUS -  OKE, si devuelve la fila.
 *               -ERROR, si no completa la operación.
------------------------------------------------------------------*/
extern STATUS getEnFil(const MAPA *map,int* fil);

/*------------------------------------------------------------------
 *@name setEnFil
 *@brief Establece la fila en la se pinta el jugador de un mapa.
 *@param (MAPA * map) puntero al mapa.
 *@param (const int * fil) puntero a la fila.
 *@return STATUS -  OKE, si cambia la columna.
 *               -ERROR, si no completa la operación.
------------------------------------------------------------------*/
extern STATUS setEnFil(MAPA *map,const int fil);

/*------------------------------------------------------------------
 *@name getGraphMap
 *@brief Devuelve un puntero al inicio del mapa.
 *@param (const MAPA * map) puntero al mapa.
 *@param (char ** map) puntero al dibujo del mapa.
 *@return STATUS -  OKE, si devuelve el dibujo del mapa.
 *               -ERROR, si no completa la operación.
------------------------------------------------------------------*/
extern STATUS getGraphMap(const MAPA *map,char** gMap);

/*------------------------------------------------------------------
 *@name setGraphMap
 *@brief Establece el dibujo del mapa.
 *@param (const MAPA * map) puntero al mapa.
 *@param (char ** map) puntero al dibujo del mapa.
 *@return STATUS -  OKE, si devuelve el dibujo del mapa.
 *               -ERROR, si no completa la operación.
------------------------------------------------------------------*/
extern STATUS setGraphMap(MAPA *map, char** gMap);

/*------------------------------------------------------------------
 *@name modGraphMap
 *@brief Modifica el mapa.
 *@param (const MAPA * map,char gh, int x, int y) puntero al mapa, grafo y coordenadas.
 *@return STATUS -  OKE, si devuelve el dibujo del mapa.
 *               -ERROR, si no completa la operación.
------------------------------------------------------------------*/
extern STATUS modGrahMap(MAPA* mapa, char gh, int x, int y);

/*------------------------------------------------------------------
 *@name compareGraphMap
 *@brief Compara el grafo de una posicion con el dado.
 *@param (const MAPA * map,char gh, int x, int y) puntero al mapa, grafo y coordenadas.
 *@return BOOL -  VERDADERO, si es igual el grafo.
 *               -FALSO, si no es igual el grafo.
------------------------------------------------------------------*/
BOOL compareGrahMap(MAPA* map, char gh, int x, int y);

#endif	/* ENTORNO_H */
