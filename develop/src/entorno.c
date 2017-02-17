/******************************************************************************

Nombre del módulo: entorno.c

Descripción:
        Funciones para el manejo de datos del entorno. Con estas funciones
  manejamos los datos de los elementos que componen cada entorno, así como
  las interacciones del jugador con el entorno.

Autor: Diego Chicote

Fecha: 19-02-2013

Módulos propios que necesita:
- entorno.h

Notas: Faltan funciones por revisar, como la carga del entorno a partir de fichero.

Modificaciones:
[19-02-2013] Creación de fichero y comienzo de implementación del pseudocódigo.
[19-02-2013] Terminadas las funciones:
 *           -iniEntorno
 *           -destruirEntorno
 *           -getNombreEnt
 *           -getDescripcionEnt
 *           -getPersonajeEnt
 *           -getObjetoEnt
 *           -getMapaEnt
 *           -pushObjetoEnt
 *           -annadirPj
 *           -cargarEntorno
 *           -guardarEntorno
[12-04-2013]Miguel Gomez-Tavira añade las funciones.
 *           -setNombreEnt
 *           -setIdEnt
 *           -setDescripcionEnt
[14-04-2013]Eliminadas las funciones:
 *           -pushObjetoEnt
 *           -annadirPj
[22-04-2013] Iñaki Cadalso añadidas Funciones:
 *           -getPersonajeEnt
 *           -getObjetoEnt
[22-04-2013] Diego Chicote Añadidas las funciones:
 *           -copiaEntorno
[22-04-2013] Miguel Gomez-Tavira añade la reserva de memoria para uniones.
 *
[23-04-2013] Iñaki Cadalso añadidas Funciones:
 *           -annadirInventario
 *           -annadirPjsEnt
[01-05-2013] Miguel Gomez-Tavira módifica la función setMapaEnt.
 *           Iñaki Cadalso corrige comentarios de funciones
 * 
Mejoras pendientes:
- Pruebas de funciones.
- Implementación de las funciones con código más eficiente.

 ******************************************************************************/

/*=== Cabeceras =============================================================*/
#include "entorno.h"
#include "entorno.h"


/*=== Funciones =============================================================*/

/*-----------------------------------------------------------------------------

Nombre: iniEntorno

Descripción:
        Inicia el entorno, reservando memoria para el mismo, dinámicamente.

Argumentos de entrada:


Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR_RM, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS iniEntorno(ENTORNO* ent) {


    if (ent == NULL)
        return ERROR_RM;
    ent->id = (char*) malloc(sizeof (MAX_ID));
    if (ent->id == NULL) {
        free(ent);
        return ERROR_RM;
    }
    ent->nombre = (char*) malloc(sizeof (MAX_NOM_ENT));
    if (ent->nombre == NULL) {
        free(ent->id);
        free(ent);
        return ERROR_RM;
    }
    ent->descripcion = (char*) malloc(sizeof (MAX_DES_ENT));
    if (ent->descripcion == NULL) {
        free(ent->nombre);
        free(ent->id);
        free(ent);
        return ERROR_RM;
    }
    ent->invEnt = (INVENTARIO*) malloc(sizeof (INVENTARIO));
    if (iniInventario(ent->invEnt) == ERROR_RM) {
        free(ent->descripcion);
        free(ent->nombre);
        free(ent->id);
        free(ent);
        return ERROR_RM;
    }
    ent->pjsEnt = (PJSENTORNO*) malloc(sizeof (PJSENTORNO));
    if (iniPjsEnt(ent->pjsEnt) == ERROR_RM) {
        destruirInventario(ent->invEnt);
        free(ent->descripcion);
        free(ent->nombre);
        free(ent->id);
        free(ent);
    }
    ent->mapaEnt = (MAPA*) malloc(sizeof (MAPA));
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: copiaEntorno

Descripción:
  Copia el entorno orig en el entorno dst.

Argumentos de entrada:
1. dst, el entorno donde se realiza la copia.
2. orig, el entorno del que se realiza la copia.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS copiaEntorno(ENTORNO* dst, const ENTORNO* org) {

    if (dst == NULL || org == NULL)
        return ERROR;
    strcpy(dst->id, org->id);
    strcpy(dst->nombre, org->nombre);
    strcpy(dst->descripcion, org->descripcion);
    copiaInventario(dst->invEnt, org->invEnt);
    dst->numObjEnt = org->numObjEnt;
    dst->numPjsEnt = org->numPjsEnt;


    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: destruirEntorno

Descripción:
        Libera la memoria reservada para entorno.

Argumentos de entrada:
1. ent, recibe un entorno por puntero.


Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR_LM, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS destruirEntorno(ENTORNO * ent) {

    if (ent == NULL) {
        return ERROR_LM;
    }
    if (&ent->mapaEnt == NULL) {
        /*Libera mapa*/
    }
    /*
        if (ent->uniones != NULL) {
       
        }
     */
    destruirPjsEnt(ent->pjsEnt);
    destruirInventario(ent->invEnt);
    free(ent->descripcion);
    free(ent->nombre);
    free(ent->id);
    free(ent);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getIdEnt

Descripción:
        Devuelve la id del entorno.

Argumentos de entrada:
1. ent, recibe un entorno por puntero.


Retorno:
-  ent->id, si se ha terminado sin problemas
-  NULL, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getIdEnt(const ENTORNO *ent, ID idEnt) {

    if (ent == NULL)
        return ERROR;
    strcpy(idEnt, ent->id);
    return OKE;

}

/*-----------------------------------------------------------------------------

Nombre: setIdEnt

Descripción:
        Modifica la id del entorno.

Argumentos de entrada:
1. ent, recibe un entorno por puntero.
2. id, la id que tomara el entorno.


Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setIdEnt(ENTORNO *ent, const ID id) {

    if (ent == NULL || id == NULL)
        return ERROR;
    if (strlen(id) + 1 > MAX_ID)
        return ERROR_FMT;
    strcpy(ent->id, id);
    return OKE;

}

/*-----------------------------------------------------------------------------

Nombre: getNombreEnt

Descripción:
        Devuelve el nombre del entorno.

Argumentos de entrada:
1. ent, recibe un entorno por puntero.


Retorno:
-  ent->nombre, si se ha terminado sin problemas
-  NULL, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getNombreEnt(const ENTORNO *ent, char * nombreEnt) {

    if (ent == NULL)
        return ERROR;
    strcpy(nombreEnt, ent->nombre);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setNombreEnt

Descripción:
        Cambia el nombre del entorno.

Argumentos de entrada:
1. ent, recibe un entorno por puntero.
2. nombre, recibe por puntero el nombre que tomara el objeto.


Retorno:
-  ent->nombre, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setNombreEnt(ENTORNO* ent, const char* nombreEnt) {

    if (ent == NULL)
        return ERROR;
    if (strlen(nombreEnt) + 1 > MAX_NOM_ENT)
        return ERROR_FMT;
    strcpy(ent->nombre, nombreEnt);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getDescripcionEnt

Descripción:
        Devuelve la descripción del entorno.

Argumentos de entrada:
1. ent, recibe un entorno por puntero.


Retorno:
-  ent->descripcion, si se ha terminado sin problemas
-  NULL, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getDescripcionEnt(const ENTORNO *ent, char * descEnt) {

    if (ent == NULL)
        return ERROR;
    strcpy(descEnt, ent->descripcion);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setDescripcionEnt

Descripción:
        Modifica la descripción del entorno.

Argumentos de entrada:
1. ent, recibe un entorno por puntero.
2. desc,descripción que tomara el entorno.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setDescripcionEnt(ENTORNO* ent, const char* descEnt) {

    if (ent == NULL || descEnt == NULL)
        return ERROR;
    if (strlen(descEnt) + 1 > MAX_DES_ENT)
        return ERROR_FMT;
    ent->descripcion = strdup(descEnt);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getMapaEnt

Descripción:
        Modifica la descripción del entorno.

Argumentos de entrada:
1. ent, recibe un entorno por puntero.
2. desc,descripción que tomara el entorno.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getMapaEnt(const ENTORNO *ent, MAPA** mapaEnt) {

    if (ent == NULL)
        return ERROR;
    *mapaEnt = ent->mapaEnt;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setMapaEnt

Descripción:
        Modifica la descripción del entorno.

Argumentos de entrada:
1. ent, recibe un entorno por puntero.
2. desc,descripción que tomara el entorno.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setMapaEnt(ENTORNO *ent, MAPA* mapaEnt) {

    if (ent == NULL || mapaEnt == NULL)
        return ERROR;

    if (setFilMap(ent->mapaEnt, mapaEnt->filas) != OKE)
        return ERROR;
    if (setColMap(ent->mapaEnt, mapaEnt->columnas) != OKE)
        return ERROR;
    if (setSalFil(ent->mapaEnt, mapaEnt->salFil) != OKE)
        return ERROR;
    if (setSalCol(ent->mapaEnt, mapaEnt->salCol) != OKE)
        return ERROR;
    if (setGraphMap(ent->mapaEnt, mapaEnt->mapa) != OKE)
        return ERROR;

    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getPersonajeEnt

Descripción:
        Encuentra el personaje nombrado.

Argumentos de entrada:
1. ent, recibe un entorno por puntero.
2. nom, nombre de lo buscado.

Retorno:
-  PERSONAJE *, si se ha terminado sin problemas
-  NULL, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
PERSONAJE * getPersonajeEnt(ENTORNO *ent, const char * nom) {
    NODO_PJ* nodoPJ = NULL;

    if (ent != NULL) {
        if (buscarPjsEnt(ent->pjsEnt, &nodoPJ, nom) == ERROR)
            return NULL;
        return nodoPJ->pj;
    }
    return NULL;
}

/*-----------------------------------------------------------------------------

Nombre: getObjetoEnt

Descripción:
        Encuentra el objeto nombrado

Argumentos de entrada:
1. ent, recibe un entorno por puntero.
2. nom, nombre de lo buscado.

Retorno:
-  OBJETO *, si se ha terminado sin problemas
-  NULL, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
OBJETO * getObjetoEnt(ENTORNO *ent, const char * nom) {
    NODO_INV* nodoINV = NULL;

    if (ent != NULL) {
        if (buscarEnInventario(ent->invEnt, &nodoINV, nom) == ERROR)
            return NULL;
        return nodoINV->obj;
    }
    return NULL;
}

/*-----------------------------------------------------------------------------

Nombre: annadirInventario

Descripción:
        Annade Inventario al entorno..

Argumentos de entrada:
1. ent, recibe un entorno por puntero.
2. inv,inventario a annadir al entorno.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS annadirInventario(ENTORNO *ent, INVENTARIO *inv) {

    if (ent == NULL)
        return ERROR;
    ent->invEnt = inv;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: annadirPjsEnt

Descripción:
        Annade PersonajesEntorno al entorno.

Argumentos de entrada:
1. ent, recibe un entorno por puntero.
2. pj,personajes del entorno a annadir.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS annadirPjsEnt(ENTORNO *ent, PJSENTORNO *pj) {

    if (ent == NULL)
        return ERROR;
    ent->pjsEnt = pj;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: cargarEntorno

Descripción:
        Cargar de un entorno de fichero.

Argumentos de entrada:
1. ent, recibe un entorno por puntero.
2. f,fichero donde lee.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/

extern STATUS cargarEntorno(ENTORNO *ent, FILE* f) {

    if (ent == NULL || f == NULL)
        return ERROR;
    /*Lee el fichero e inicia los valores del mapa.*/
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: cguardarEntorno

Descripción:
        Guardar un entorno en un fichero.

Argumentos de entrada:
1. ent, recibe un entorno por puntero.
2. f,fichero donde escribir.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS guardarEntorno(FILE* file, ENTORNO *ent) {

    if (ent != NULL) {

        file = fopen("saveEntorno.txt", "w");
        fprintf(file, "%s\n", ent->id);
        fprintf(file, "%s\n", ent->nombre);
        fprintf(file, "%s\n", ent->descripcion);

        fprintf(file, "%d\n", ent->numObjEnt);

        fprintf(file, "%d\n", ent->numPjsEnt);
        return OKE;
    }
    return ERROR;
}

/****Mapa**********************************************************/

/*-----------------------------------------------------------------------------
Nombre: getColMapa

Descripción:
        Devuelve el número de columnas del mapa.

Argumentos de entrada:
1. map, recibe un mapa por puntero.
2. col, número de columnas del mapa.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getColMap(const MAPA *map, int* col) {

    if (map == NULL)
        return ERROR;
    *col = map->columnas;
    return OKE;
}

/*-----------------------------------------------------------------------------
Nombre: setColMap

Descripción:
        Establece el número de columnas del mapa.

Argumentos de entrada:
1. map, recibe un mapa por puntero.
2. col, número de columnas del mapa.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setColMap(MAPA *map, const int col) {

    if (map == NULL)
        return ERROR;

    map->columnas = col;
    return OKE;
}

/*-----------------------------------------------------------------------------
Nombre: getFilMap

Descripción:
        Devuelve el número de filas del mapa.

Argumentos de entrada:
1. map, recibe un mapa por puntero.
2. fil, número de filas del mapa.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getFilMap(const MAPA* map, int* fil) {

    if (map == NULL)
        return ERROR;

    *fil = map->filas;
    return OKE;
}

/*-----------------------------------------------------------------------------
Nombre: setFilMap

Descripción:
        Establece el número de filas del mapa.

Argumentos de entrada:
1. map, recibe un mapa por puntero.
2. fil, número de filas del mapa.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setFilMap(MAPA *map, const int fil) {

    if (map == NULL)
        return ERROR;

    map->filas = fil;
    return OKE;
}

/*-----------------------------------------------------------------------------
Nombre: getSalCol

Descripción:
        Devuelve la columna en la que se pinta el personaje en el mapa
 por primera vez.

Argumentos de entrada:
1. map, recibe un mapa por puntero.
2. col, columna del mapa.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getSalCol(const MAPA *map, int *col) {

    if (map == NULL)
        return ERROR;

    *col = map->salCol;
    return OKE;
}

/*-----------------------------------------------------------------------------
Nombre: setSalCol

Descripción:
        Establece la columna en la que se pinta el personaje en el mapa
 por primera vez.

Argumentos de entrada:
1. map, recibe un mapa por puntero.
2. col, columna del mapa.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setSalCol(MAPA *map, const int col) {

    if (map == NULL)
        return ERROR;

    map->salCol = col;
    return OKE;
}

/*-----------------------------------------------------------------------------
Nombre: getSalFil

Descripción:
        Devuelve la fila en la que se pinta el personaje en el mapa
 por primera vez.

Argumentos de entrada:
1. map, recibe un mapa por puntero.
2. fil, fila del mapa.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getSalFil(const MAPA *map, int* fil) {

    if (map == NULL)
        return ERROR;

    *fil = map->salFil;
    return OKE;
}

/*-----------------------------------------------------------------------------
Nombre: setSalFil

Descripción:
        Establece la fila en la que se pinta el personaje en el mapa
 por primera vez.

Argumentos de entrada:
1. map, recibe un mapa por puntero.
2. fil, fila del mapa.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setSalFil(MAPA *map, const int fil) {

    if (map == NULL)
        return ERROR;

    map->salFil = fil;
    return OKE;
}

/*-----------------------------------------------------------------------------
Nombre: getEnCol

Descripción:
        Devuelve la columna en la que se pinta el personaje en el mapa
 al retroceder de entorno.

Argumentos de entrada:
1. map, recibe un mapa por puntero.
2. col, columna del mapa.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getEnCol(const MAPA *map, int *col) {

    if (map == NULL)
        return ERROR;

    *col = map->enCol;
    return OKE;
}

/*-----------------------------------------------------------------------------
Nombre: setEnCol

Descripción:
        Establece la columna en la que se pinta el personaje en el mapa
 al retroceder de entorno.

Argumentos de entrada:
1. map, recibe un mapa por puntero.
2. col, columna del mapa.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setEnCol(MAPA *map, const int col) {

    if (map == NULL)
        return ERROR;

    map->enCol = col;
    return OKE;
}

/*-----------------------------------------------------------------------------
Nombre: getEnFil

Descripción:
        Devuelve la fila en la que se pinta el personaje en el mapa
 al retroceder de entorno.

Argumentos de entrada:
1. map, recibe un mapa por puntero.
2. fil, fila del mapa.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getEnFil(const MAPA *map, int* fil) {

    if (map == NULL)
        return ERROR;

    *fil = map->enFil;
    return OKE;
}

/*-----------------------------------------------------------------------------
Nombre: setEnFil

Descripción:
        Establece la fila en la que se pinta el personaje en el mapa
 al retroceder de entorno.

Argumentos de entrada:
1. map, recibe un mapa por puntero.
2. fil, fila del mapa.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setEnFil(MAPA *map, const int fil) {

    if (map == NULL)
        return ERROR;

    map->enFil = fil;
    return OKE;
}

/*-----------------------------------------------------------------------------
Nombre: getGraphMap

Descripción:
        Devuelve un puntero a la representación gráfica mapa.

Argumentos de entrada:
1. map, recibe un mapa por puntero.
2. gMap, representación gráfica mapa.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getGraphMap(const MAPA *map, char** gMap) {

    if (map == NULL)
        return ERROR;

    gMap = map->mapa;
    return OKE;
}

/*-----------------------------------------------------------------------------
Nombre: setGraphMap

Descripción:
        Establece la representación gráfica mapa.

Argumentos de entrada:
1. map, recibe un mapa por puntero.
2. gMap, representación gráfica mapa.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setGraphMap(MAPA *map, char** gMap) {

    int i = 0, j = 0;

    if (map == NULL || gMap == NULL)
        return ERROR;

    map->mapa = (char**) malloc(sizeof (char*) * map->columnas);
    if (map == NULL)
        return ERROR;

    for (i = 0; i < map->filas; i++) {
        map->mapa[i] = (char*) malloc(sizeof (char)*map->columnas);
        if (map->mapa[i] == NULL) {
            for (j = i; j >= 0; j--) {
                free(map->mapa[i]);
            }
            return ERROR;
        }
    }

    for (i = 0; i < map->columnas; i++) {
        for (j = 0; j < map->filas; j++)
            map->mapa[i][j] = gMap[i][j];
    }

    return OKE;

}
/*-----------------------------------------------------------------------------
Nombre: modGraphMap

Descripción:
        Modifica el grafo de una posicion del mapa.

Argumentos de entrada:
1. map, recibe un mapa por puntero.
2. gh,grafo x el que se sustituye la posicion.
3. x, coordenada.
4. y, coordenada.

Retorno:
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS modGrahMap(MAPA* mapa, char gh, int x, int y) {
    if(mapa==NULL)
        return ERROR;
    mapa->mapa[y][x] = gh;
    return OKE;
      
}
/*-----------------------------------------------------------------------------
Nombre: compareGraphMap

Descripción:
        Compara el grafo de una posicion del mapa con el dado.

Argumentos de entrada:
1. map, recibe un mapa por puntero.
2. gh,grafo a comparar.
3. x, coordenada.
4. y, coordenada.

Retorno:
-  VERDADERO, si es el mismo.
-  FALSO, si no es el mismo.

-----------------------------------------------------------------------------*/
BOOL compareGrahMap(MAPA* map, char gh, int x, int y) {
    
    if(map->mapa[y][x] == gh)
        return VERDADERO;
    return FALSO;
}
    /*****************************************************************************/
