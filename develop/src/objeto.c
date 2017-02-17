
/******************************************************************************

Nombre del módulo: objeto.c

Descripción: 
        Funciones para el manejo de los objetos.

Autor: Diego Chicote

Fecha: 19-03-2013

Modulos propios que necesita: 
- objeto.h

Notas: Faltan revisar los comentarios, y hacer pruebas de campo de las distintas
funciones.

Modificaciones: 
[19-03-2013] Creación de fichero y comienzo de implementación del pseudocódigo.
[19-03-2013] Terminadas las funciones:
 *           -iniObj
 *           -destruyeObj
 *           -setDescObj
 *           -setGraphObj
 *           -setPosXObj
 *           -setPosYObj
 *           -setNombreObj
 *           -setMovilObj
 *           -setMovidoObj
 *           -setIluminaObj
 *           -setEncendidoObj
 *           -setRompibleObj
 *           -setRotoObj
 *           -setTeleportObj
 *           -setdest_TeleportObj
 *           -getIDObj
 *           -descripcionObj
 *           -getGraphObj
 *           -posicionXObj
 *           -posicionYObj
 *           -getMovil_obj
 *           -getMovido_obj
 *           -getIlumina_obj
 *           -getEncendido_obj
 *           -getRompible_obj
 *           -getRoto_obj 
 *           -getTeleport_obj  
 *           -getDest_teleport_obj 
 *           -imprime_obj 
 [13-04-2013]Miguel Gomez-Tavira, revisa y modifica parte del código. 
 [13-04-2013]Se cambian y amplian los comentarios de las funciones:
 *           setPosXObj           :pasa a ser setFilaObj
 *           setPosYObj           :pasa a ser setColumnaObj
 *           setdest_TeleportObj  :pasa a ser setDestTeleportObj
 *           descripcionObj       :pasa a ser getDescripcionObj
 *           posicionXObj         :pasa a ser getFilaObj
 *           posicionYObj         :pasa a ser getColumnaObj
 *           getMovil_obj         :pasa a ser getMovilObj
 *           getMovido_obj        :pasa a ser getMovidoObj
 *           getIlumina_obj       :pasa a ser getIluminaObj
 *           getEncendido_obj     :pasa a ser getEncendidoObj
 *           getRompible_obj      :pasa a ser getRompibleObj
 *           getRoto_obj          :pasa a ser getRotoObj
 *           getTeleport_obj      :pasa a ser getTeleportObj
 *           getDest_teleport_obj :pasa a ser getDestTeleportObj
 [13-04-2013]Se añade la función:
 *           -copiaObjeto
 [01-05-2013] Iñaki Cadalso corrige comentarios de funciones
 * 
 
Mejoras pendientes: 
- Pruebas de funciones.
- Repaso de comentarios.

 ******************************************************************************/

/*=== Cabeceras =============================================================*/
#include "objeto.h"

/*-----------------------------------------------------------------------------

Nombre: iniObj

Descripción:
  Reserva espacio de memoria para un objeto.

Argumentos de entrada: 
1. obj, recibe el objeto a inicializar por puntero.
 
Retorno: 
-  OKE     , si se ha terminado sin problemas
-  ERROR_RM, si se ha producido algún error reservando memoria.

-----------------------------------------------------------------------------*/
extern STATUS iniObj(OBJETO* obj) {

    
    if (obj == NULL)
        return ERROR_RM;
    obj->id = (char*) malloc(sizeof (char)*MAX_ID);
    if (obj->id == NULL) {
        free(obj);
        return ERROR_RM;
    }
    obj->nombre = (char*) malloc(sizeof (char)*MAX_NOM_OBJ);
    if (obj->nombre == NULL) {
        free(obj->id);
        free(obj);
        return ERROR_RM;
    }
    obj->descripcion = (char*) malloc(sizeof (char)*MAX_DES_OBJ);
    if (obj->descripcion == NULL) {
        free(obj->nombre);
        free(obj->id);
        free(obj);
        return ERROR_RM;
    }
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: copiaObjeto

Descripción:
  Copia el objeto orig en el objeto dst.

Argumentos de entrada: 
1. dst, el objeto donde se realiza la copia.
2. orig, el objeto del que se realiza la copia.
 
Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS copiaObjeto(OBJETO* dst, const OBJETO* org) {

    if (dst == NULL || org == NULL)
        return ERROR;
    strcpy(dst->id, org->id);
    dst->fila = org->fila;
    dst->columna = org->columna;
    strcpy(dst->nombre, org->nombre);
    strcpy(dst->descripcion, org->descripcion);
    dst->graph = org->graph;
    dst->movil = org->movil;
    dst->movido = org->movido;
    dst->ilumina = org->ilumina;
    dst-> encendido = org->encendido;
    dst->rompible = org->rompible;
    dst->roto = org->roto;
    dst->teleport = org->teleport;
    
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: destruyeObj

Descripción:
  Libera espacio de memoria de un objeto.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
 
Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR_LM, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS destruyeObj(OBJETO * obj) {

    if (obj == NULL)
        return ERROR_LM;
    free(obj->descripcion);
    free(obj->nombre);
    free(obj->id);
    free(obj);
    return OKE;
}

/*************************Atributos del objeto********************************/

/*-----------------------------------------------------------------------------

Nombre: getIDObj

Descripción:
  Devuelve la ID del objeto.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. id, la id del objeto.

Retorno: 
-  obj->id, si se ha terminado sin problemas
-  NULL, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getIDObj(const OBJETO * obj, ID id) {

    if (obj == NULL)
        return ERROR;
    strcpy(id, obj->id);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setIDObj

Descripción:
  Modifica la ID del objeto.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. id, la ID que tendrá el objeto.

Retorno: 
-  obj->id, si se ha terminado sin problemas
-  NULL, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setIDObj(OBJETO * obj, const ID id) {

    if (obj == NULL || id == NULL)
        return ERROR;
    if (strlen(id) + 1 > MAX_ID)
        return ERROR_FMT;
    strcpy(obj->id, id);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getFilaObj

Descripción:
  Devuelve la fila en la que se encuentra el objeto, en el mapa.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. fila, la fila en la que se encuentra el objeto.

Retorno: 
-  obj->fila, si se ha terminado sin problemas
-  -1, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getFilaObj(const OBJETO * obj, int* fila) {

    if (obj == NULL)
        return ERROR;
    *fila = obj->fila;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setFilaObj

Descripción:
  Modifica la fila en la que se encuentra el objeto, en el mapa.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. fila, la fila a la que se movera el objeto.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setFilaObj(OBJETO * obj, const int fila) {

    if (obj == NULL)
        return ERROR;
    obj->fila = fila;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setFilaObj

Descripción:
  Devuelve la columna en la que se encuentra el objeto, en el mapa.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. columna, columna en que se sitúa el objeto.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getColumnaObj(const OBJETO * obj, int* columna) {

    if (obj == NULL)
        return ERROR;
    *columna = obj->columna;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setColumnaObj

Descripción:
  Modifica la columna en la que se encuentra el objeto, en el mapa.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. columna, la columna a la que se movera el objeto.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setColumnaObj(OBJETO * obj, const int columna) {

    if (obj == NULL)
        return ERROR;
    obj->columna = columna;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getNombreObj

Descripción:
  Obtiene el nombre del objeto.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. nombre, la variable que recibe el nombre.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getNombreObj(const OBJETO * obj, char* nombre) {

    if (obj == NULL)
        return ERROR;
    strcpy(nombre, obj->nombre);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setNombreObj

Descripción:
  Modifica el nombre del objeto.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. nombre, el nombre que recibira objeto.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún error.
-  ERROR_FMT, si se ha producido algun error por formatos.

-----------------------------------------------------------------------------*/
extern STATUS setNombreObj(OBJETO * obj, const char * nombre) {

    if (obj == NULL)
        return ERROR;
    if (strlen(nombre) + 1 > MAX_NOM_OBJ)
        return ERROR_FMT;
    strcpy(obj->nombre, nombre);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getDescObj

Descripción:
  Devuelve la descripción del objeto.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. desc, la descripción que tiene objeto.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getDescObj(const OBJETO * obj, char* desc) {

    if (obj == NULL)
        return ERROR;
    strcpy(desc, obj->descripcion);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setDescObj

Descripción:
  Modifica la descripción del objeto.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. desc, la descripción que tendra objeto.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setDescObj(OBJETO * obj, const char * descripcion) {

    if (obj == NULL || descripcion == NULL)
        return ERROR;
    strcpy(obj->descripcion, descripcion);
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getGraphObj

Descripción:
  Devuelve el carácter que representa al objeto.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. graph, el gráfico que representa al objeto en el mapa.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS getGraphObj(const OBJETO * obj, char* graph) {

    if (obj == NULL)
        return ERROR;
    *graph = obj->graph;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: setGraphObj

Descripción:
  Modifica el carácter que representa al objeto.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. graph, el gráfico que representa al objeto en el mapa.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setGraphObj(OBJETO * obj, const char graph) {

    if (obj == NULL)
        return ERROR;
    obj->graph = graph;
    return OKE;
}

/*************************Atributos booleanos del objeto**********************/

/*-----------------------------------------------------------------------------

Nombre: getMovilObj

Descripción:
  Devuelve si el objeto se puede mover.

Argumentos de entrada: 

Retorno: 
-  obj->movil, si se ha terminado sin problemas
-  ERRORB, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern BOOL getMovilObj(const OBJETO * obj) {

    if (obj == NULL)
        return ERRB;
    return obj->movil;
}

/*-----------------------------------------------------------------------------

Nombre: setMovilObj

Descripción:
  Modifica el atributo movil del objeto.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. movil, dice si se puede o no moveer el objeto.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERRORB, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setMovilObj(OBJETO * obj, const BOOL movil) {

    if (obj == NULL)
        return ERROR;
    obj->movil = movil;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getMovidoObj

Descripción:
  Devuelve si el objeto se ha movido del mapa.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.

Retorno: 
-  obj->movido, si se ha terminado sin problemas
-  ERRORB, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern BOOL getMovidoObj(const OBJETO * obj) {

    if (obj == NULL)
        return ERRB;
    return obj->movido;
}

/*-----------------------------------------------------------------------------

Nombre: setMovidoObj

Descripción:
  Modifica el atributo del objeto, que indica si este se ha movido del mapa.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. movido, indica si se ha movido o no el objeto.

Retorno: 
-  OKE,    si se ha terminado sin problemas
-  ERRORB, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setMovidoObj(OBJETO * obj, const BOOL movido) {

    if (obj == NULL)
        return ERROR;
    obj->movido = movido;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getIluminaObj

Descripción:
  Devuelve si el objeto tiene la capacidad de iluminar.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.

Retorno: 
-  obj->ilumina, si se ha terminado sin problemas
-  ERRORB, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern BOOL getIluminaObj(const OBJETO * obj) {

    if (obj == NULL)
        return ERRB;
    return obj->ilumina;
}

/*-----------------------------------------------------------------------------

Nombre: setIluminaObj

Descripción:
  Modifica la capacidad del objeto para iluminar.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. ilumina, indica si el objeto puede iluminar o no.

Retorno: 
-  OKE,    si se ha terminado sin problemas
-  ERRORB, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setIluminaObj(OBJETO * obj, const BOOL ilumina) {

    if (obj == NULL)
        return ERROR;
    obj->ilumina = ilumina;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getEncendidoObj

Descripción:
  Devuelve si el objeto con la capacidad de iluminar está encendido.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.

Retorno: 
-  obj->encendido, si se ha terminado sin problemas
-  ERRB, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern BOOL getEncendidoObj(const OBJETO * obj) {

    if (obj == NULL)
        return ERRB;
    return obj->encendido;
}

/*-----------------------------------------------------------------------------

Nombre: setEncendidoObj

Descripción:
  Modifica el estado de encendido/apagado del objeto.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. encendido, estado del objeto.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERRORR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setEncendidoObj(OBJETO * obj, const BOOL encendido) {

    if (obj == NULL)
        return ERRB;
    obj->encendido = encendido;
    return VERDADERO;
}

/*-----------------------------------------------------------------------------

Nombre: getRompibleObj

Descripción:
  Devuelve si se puede romper el objeto.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.

Retorno: 
-  obj->rompible, si se ha terminado sin problemas
-  ERRB, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern BOOL getRompibleObj(const OBJETO * obj) {

    if (obj == NULL)
        return ERRB;
    return obj->rompible;
}

/*-----------------------------------------------------------------------------

Nombre: setRompibleObj

Descripción:
  Modifica el atributo rompible del objeto.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. rompible, atributo que determina si se puede romper el objeto.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setRompibleObj(OBJETO * obj, const BOOL rompible) {

    if (obj != NULL)
        return ERROR;
    obj->rompible = rompible;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getRotoObj

Descripción:
  Devuelve si esta roto el objeto.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.

Retorno: 
-  obj->roto, si se ha terminado sin problemas
-  ERRB, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern BOOL getRotoObj(const OBJETO * obj) {

    if (obj == NULL)
        return ERRB;
    return obj->roto;
}

/*-----------------------------------------------------------------------------

Nombre: setRotoObj

Descripción:
  Modifica si el objeto se ha roto.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. roto, atributo que determina si el objeto esta roto.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setRotoObj(OBJETO * obj, const BOOL roto) {

    if (obj == NULL)
        return ERROR;
    obj->roto = roto;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getTeleportObj

Descripción:
  Devuelve si el objeto, tiene la capacidad de teletransportar al jugador.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.

Retorno: 
-  obj->teleport, si se ha terminado sin problemas
-  ERRB, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern BOOL getTeleportObj(const OBJETO * obj) {

    if (obj == NULL)
        return ERRB;
    return obj->teleport;
}

/*-----------------------------------------------------------------------------

Nombre: setTeleportObj

Descripción:
  Modifica la capacidad de teletransportar al jugador del objeto.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. teleport, atributo que determina la capacidad de teletransporte.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
extern STATUS setTeleportObj(OBJETO * obj, const BOOL teleport) {

    if (obj == NULL)
        return ERROR;
    obj->teleport = teleport;
    return OKE;
}

/*-----------------------------------------------------------------------------

Nombre: getDestTeleportObj

Descripción:
  Devuelve el destino al que teletrasporta el objeto, al jugador.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. id, identificador del destino del teletransporte.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
/*
extern STATUS getDestTeleportObj(const OBJETO * obj, ID id) {

    if (obj == NULL)
        return ERROR;
    strcpy(id, obj->dest_teleport);
    return OKE;
}
*/

/*-----------------------------------------------------------------------------

Nombre: setDestTeleportObj

Descripción:
  Modifica el destino al que el objeto teletransporta al jugador.

Argumentos de entrada: 
1. obj, el objeto pasado por puntero.
2. id, identificador del destino de teletrasnporte.

Retorno: 
-  OKE, si se ha terminado sin problemas
-  ERROR, si se ha producido algún tipo de error.

-----------------------------------------------------------------------------*/
/*
extern STATUS setDestTeleportObj(OBJETO * obj, const ID id) {

    if (obj == NULL)
        return ERROR;
    if (strlen(id) + 1 > MAX_ID)
        return ERROR_FMT;
    strcpy(obj->dest_teleport, id);
    return OKE;
}
*/

/* Imprime objeto. Esta función se incluye por motivos de depuración*/

/*------------------------------------------------------------------
 *@name imprime_obj
 *@brief Inicializa un entorno, reservando memoria para este
 *@param ()
 *@return Un entorno nuevo,  si reserva correctamente
------------------------------------------------------------------*/
extern STATUS imprime_obj(const OBJETO * obj) {

    if (obj == NULL)
        return ERROR;

    printf("\nID Objeto = %s\n", obj->id);
    printf("localizacion= %d\n", obj->columna);
    printf("localizacion= %d\n", obj->fila);
    printf("nombre= %s\n", obj->nombre);
    printf("descripcion= %s\n", obj->descripcion);
    printf("movil= %d\n", obj->movil);
    printf("movido= %d\n", obj->movido);
    printf("ilumina= %d\n", obj->ilumina);
    printf("encendido= %d\n", obj->encendido);
    printf("rompible= %d\n", obj->rompible);
    printf("roto= %d\n", obj->roto);
    printf("teleport= %d\n", obj->teleport);
    

    return OKE;
}
