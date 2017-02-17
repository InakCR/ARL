/******************************************************************************

Nombre del módulo: Lectorxml.c

Descripción:
 Funciones para leer el mundo de juego de archivos xml.

Autor: Miguel Gomez-Tavira

Modulos propios que necesita:
- Lectorxml.h

Modificaciones:
[02-05-2013] Creación de fichero y comienzo de implementación del pseudocódigo.
[02-05-2013] Terminadas las funciones:
 *           -procesaMundo
 *           -procesaNombreEntorno
 *           -procesaDescEntorno
 *           -procesaNumObjsEntorno
 *           -procesaNumPjsEntorno
 *           -procesaFilObjeto
 *           -procesaColObjeto
 *           -procesaNombreObjeto
 *           -procesaDescObjeto
 *           -procesaGraphObjeto
 *           -procesaMovilObjeto
 *           -procesaMovidoObjeto
 *           -procesaIluminaObjeto
 *           -procesaEncendidoObjeto
 *           -procesaRompibleObjeto
 *           -procesaRotoObjeto
 *           -procesaTeleportObjeto
 *           -procesaDestTeleportObjeto
 *           -procesaFilPj
 *           -procesaColPj
 *           -procesaNombrePj
 *           -procesaDescPj
 *           -procesaGraphPj
 *           -procesaVitPj
 *           -procesaVitTotPj
 *           -procesaFzaPj
 *           -procesaDefPj
 *           -procesaIntPj
 *           -procesaAtkPj
 *           -procesaColMapa
 *           -procesaFilMapa
 *           -procesaSalCol
 *           -procesaSalFil
[03-05-2013] Terminadas las funciones:
 *           -procesaEntorno
 *           -procesaInvEntorno
 *           -procesaPjsEntorno
 *           -procesaMapaEntorno
 *           -procesaUnionesEntorno
 *           -procesaObjeto
 *           -procesaPersonaje
 *           -procesaInvPj
 *           -procesaMapa
 *           -procesaSalFil
[03-05-2013] Comentadas las funciones.
 *           Iñaki Cadalso inicializa correctamente los Entornos, Inventarios,
 *              Personajes y Objetos

Mejoras pendientes:
- Pruebas de funciones.

 ******************************************************************************/

/*=== Cabeceras =============================================================*/
#include "Lectorxml.h"
#include <string.h>
#include <stdlib.h>

/*=== Funciones =============================================================*/
/**********************************Mundo**************************************/

/*-----------------------------------------------------------------------------
Nombre: procesaMundo

Descripción:
        Lee el mundo de un fichero xml y lo carga en memoria.

Argumentos de entrada:
1. m, puntero al mundo.
2. nomfich, nombre del fichero xml donde están contenidos los datos del mundo.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaMundo(char* nomfich, MUNDO* m) {

    xmlDocPtr doc; /* Puntero a la estructura xmlDoc */
    xmlNodePtr cur; /* Puntero a la estructura xmlNode */
    NODO_MUNDO* aux = NULL;
    ENTORNO *ent = NULL;

    if ((!nomfich) || (!m))
        return ERRXML;

    doc = xmlParseFile(nomfich); /*Como fopen*/

    if (doc == NULL) {
        return ERRXML;
    }

    cur = xmlDocGetRootElement(doc);
    if (cur == NULL) {
        xmlFreeDoc(doc);
        return ERRXML;
    }

    if (xmlStrcmp(cur->name, (const xmlChar *) MUN)) {
        fprintf(stderr, "Etiqueta incorrecta %s: se esperaba <mundo>",
                cur->name);
        xmlFreeDoc(doc);
        return ERRXML;
    }

    cur = cur->xmlChildrenNode;

    while (cur != NULL && m->numEntornos < MAX_MUNDO) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *) ENT))) {
            ent = (ENTORNO*) malloc(sizeof (ENTORNO));
            iniEntorno(ent);
            if (procesaEntorno(doc, cur, ent) != OKXML) {
                destruirEntorno(ent);
                destruirMundo(m);
                xmlFreeDoc(doc);
                return ERRXML;
            }
            aux = (NODO_MUNDO*) malloc(sizeof (NODO_MUNDO));
            iniNodoMundo(aux, ent);
            pushNodoMundo(m, aux);
        }
        cur = cur->next;
    }

    /*xmlFreeDoc(doc);*/
    return OKXML;

}

/**********************************Entorno**************************************/

/*-----------------------------------------------------------------------------
Nombre: procesaEntorno

Descripción:
        Lee de las etiquetas de entorno contenidas en el
 xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. ent, puntero al entorno en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaEntorno(xmlDocPtr doc, xmlNodePtr cur, ENTORNO * ent) {

    xmlChar * id = NULL;

    if ((!doc) || (!cur) || (!ent))
        return ERRXML;

    id = xmlGetProp(cur, (const xmlChar *) "id");
    if (id != NULL) {
        setIdEnt(ent, (char *) id);
        xmlFree(id);
    }
    cur = cur->xmlChildrenNode; /* Primer nodo */
    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *) NOM_ENT))) {
            if (procesaNombreEntorno(doc, cur, ent) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) DESC_ENT))) {
            if (procesaDescEntorno(doc, cur, ent) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) INV_ENT))) {
            if (procesaInvEntorno(doc, cur, ent) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) NOBJS_ENT))) {
            if (procesaNumObjsEntorno(doc, cur, ent) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) PJS_ENT))) {
            if (procesaPjsEntorno(doc, cur, ent) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) NPJS_ENT))) {
            if (procesaNumPjsEntorno(doc, cur, ent) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) MAP_ENT))) {
            if (procesaMapaEntorno(doc, cur, ent) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) U_ENT))) {
            if (procesaUnionesEntorno(doc, cur, ent) != OKXML)
                return ERRXML;
        }
        cur = cur->next;
    }

    return OKXML;

}

/*-----------------------------------------------------------------------------
Nombre: procesaNombreEntorno

Descripción:
        Lee de la etiqueta que contiene el nombre del entorno en el
 xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. ent, puntero al entorno en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaNombreEntorno(xmlDocPtr doc, xmlNodePtr cur, ENTORNO * ent) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!ent))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setNombreEnt(ent, (char*) valor);

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaDescEntorno

Descripción:
        Lee de la etiqueta que contiene la descripción del entorno en el
 xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. ent, puntero al entorno en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaDescEntorno(xmlDocPtr doc, xmlNodePtr cur, ENTORNO * ent) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!ent))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setDescripcionEnt(ent, (char*) valor);

    xmlFree(valor);

    return OKXML;

}

/*-----------------------------------------------------------------------------
Nombre: procesaInvEntorno

Descripción:
        Lee de la etiqueta que contiene el inventario del entorno en el
 xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. ent, puntero al entorno en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaInvEntorno(xmlDocPtr doc, xmlNodePtr cur, ENTORNO * ent) {

    OBJETO* obj = NULL;

    NODO_INV* nInv = NULL;

    if ((!doc) || (!cur) || (!ent))
        return ERRXML;
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *) OBJ))) {

            obj = (OBJETO*) malloc(sizeof (OBJETO));
            iniObj(obj);
            if (procesaObjeto(doc, cur, obj) != OKXML) {
                destruirInventario(ent->invEnt);
                destruyeObj(obj);
                return ERRXML;
            }
            nInv = (NODO_INV*) malloc(sizeof (NODO_INV));
            iniNodoInv(nInv, obj);
            pushNodoInv(ent->invEnt, nInv);

        }
        cur = cur->next;

    }

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaNumObjsEntorno

Descripción:
        Lee de la etiqueta que contiene el número de objetos del entorno en el
 xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. ent, puntero al entorno en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaNumObjsEntorno(xmlDocPtr doc, xmlNodePtr cur, ENTORNO * ent) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!ent))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    sscanf((char*) valor, "%d", &ent->numObjEnt);

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaPjsEntorno

Descripción:
        Lee de la etiqueta que contiene los pjs del entorno en el
 xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. ent, puntero al entorno en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaPjsEntorno(xmlDocPtr doc, xmlNodePtr cur, ENTORNO * ent) {

    PERSONAJE* pj = NULL;
    NODO_PJ* nPj = NULL;

    if ((!doc) || (!cur) || (!ent))
        return ERRXML;

    cur = cur->xmlChildrenNode; /* Primer nodo */
    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *) PJ))) {
            pj = (PERSONAJE*) malloc(sizeof (PERSONAJE));
            iniPj(pj);
            if (procesaPersonaje(doc, cur, pj) != OKXML) {
                destruirPjsEnt(ent->pjsEnt);
                destruyePj(pj);
                return ERRXML;
            }
            nPj = (NODO_PJ*) malloc(sizeof (NODO_PJ));
            iniNodoPj(nPj, pj);
            pushNodoPj(ent->pjsEnt, nPj);
        }
        cur = cur->next;
    }

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaNumPjsEntorno

Descripción:
        Lee de la etiqueta que contiene el número de pjs del entorno en el
 xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. ent, puntero al entorno en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaNumPjsEntorno(xmlDocPtr doc, xmlNodePtr cur, ENTORNO * ent) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!ent))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    sscanf((char*) valor, "%d", &ent->numPjsEnt);

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaMapaEntorno

Descripción:
        Lee de la etiqueta que contiene el mapa del entorno en el
 xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. ent, puntero al entorno en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaMapaEntorno(xmlDocPtr doc, xmlNodePtr cur, ENTORNO * ent) {


    if ((!doc) || (!cur) || (!ent))
        return ERRXML;

    cur = cur->xmlChildrenNode; /* Primer nodo */
    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *) COL_MAP))) {
            if (procesaColMapa(doc, cur, ent->mapaEnt) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) FIL_MAP))) {
            if (procesaFilMapa(doc, cur, ent->mapaEnt) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) SALCOL))) {
            if (procesaSalCol(doc, cur, ent->mapaEnt) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) SALFIL))) {
            if (procesaSalFil(doc, cur, ent->mapaEnt) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) ENCOL))) {
            if (procesaEnCol(doc, cur, ent->mapaEnt) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) ENFIL))) {
            if (procesaEnFil(doc, cur, ent->mapaEnt) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) GRAPH_MAPA))) {
            if (procesaMapa(doc, cur, ent->mapaEnt) != OKXML)
                return ERRXML;
        }
        cur = cur->next;
    }

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaUnionesEntorno

Descripción:
        Lee de la etiqueta que contiene las uniones del entorno en el
 xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. ent, puntero al entorno en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaUnionesEntorno(xmlDocPtr doc, xmlNodePtr cur, ENTORNO * ent) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!ent))
        return ERRXML;

    cur = cur->xmlChildrenNode; /* Primer nodo */
    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *) UNION))) {

            valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

            if (valor == NULL)
                return ERRXML;

            /*
                        sscanf((char*) valor, "%s", *ent->uniones);
             */

        }
        cur = cur->next;
    }

    xmlFree(valor);

    return OKXML;
}

/************************************Objetos************************************/

/*-----------------------------------------------------------------------------
Nombre: procesaObjeto

Descripción:
  Lee de las etiqueta que contienen los valores de un objeto en el xml
y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. obj, puntero al obj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj) {
    xmlChar * id = NULL;

    if ((!doc) || (!cur) || (!obj))
        return ERRXML;


    id = xmlGetProp(cur, (const xmlChar *) "id");
    if (id != NULL) {
        setIDObj(obj, (char *) id);
        xmlFree(id);
    }
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *) FIL_OBJ))) {
            if (procesaFilObjeto(doc, cur, obj) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) COL_OBJ))) {
            if (procesaColObjeto(doc, cur, obj) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) NOM_OBJ))) {
            if (procesaNombreObjeto(doc, cur, obj) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) DESC_OBJ))) {
            if (procesaDescObjeto(doc, cur, obj) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) GRA_OBJ))) {
            if (procesaGraphObjeto(doc, cur, obj) != OKXML)
                return ERRXML;
        }
        cur = cur->next;
    }

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaFilObjeto

Descripción:
  Lee de la etiqueta que contiene la fila del mapa en la que se ubica un objeto
en el xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. obj, puntero al obj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaFilObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj) {
    int x;
    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!obj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;
    x=atoi((char*)valor);


    setFilaObj(obj,x);

     xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaColObjeto

Descripción:
  Lee de la etiqueta que contiene la columna del mapa en la que se ubica un
objeto en el xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. obj, puntero al obj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaColObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!obj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setColumnaObj(obj, atoi((char*)valor));

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaNombreObjeto

Descripción:
  Lee de la etiqueta que contiene el nombre de un objeto en el xml
y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. obj, puntero al obj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaNombreObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!obj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setNombreObj(obj, (char *) valor);

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaDescObjeto

Descripción:
  Lee de la etiqueta que contiene la descripción de un objeto en el xml
y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. obj, puntero al obj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaDescObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!obj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setDescObj(obj, (char *) valor);

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaGraphObjeto

Descripción:
  Lee de la etiqueta que contiene el carácter que identifica a un
objeto en el xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. obj, puntero al obj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaGraphObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!obj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;
    setGraphObj(obj, valor[0]);


    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaMovilObjeto

Descripción:
  Lee de la etiqueta que determina si el objeto se puede mover en el xml
y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. obj, puntero al obj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaMovilObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!obj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setMovilObj(obj, (BOOL) valor);

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaMovidoObjeto

Descripción:
  Lee de la etiqueta que determina si el objeto se ha movido en el xml
y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. obj, puntero al obj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaMovidoObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!obj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setMovidoObj(obj, (BOOL) valor);

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaIluminaObjeto

Descripción:
  Lee de la etiqueta que determina si el objeto puede iluminar en el xml
y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. obj, puntero al obj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaIluminaObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!obj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setIluminaObj(obj, (BOOL) valor);

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaEncendidoObjeto

Descripción:
  Lee de la etiqueta que determina si el objeto está encendido en el xml
y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. obj, puntero al obj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaEncendidoObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!obj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setEncendidoObj(obj, (BOOL) valor);

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaRompibleObjeto

Descripción:
  Lee de la etiqueta que determina si el objeto se puede romper en el xml
y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. obj, puntero al obj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaRompibleObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!obj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setRompibleObj(obj, (BOOL) valor);

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaRotoObjeto

Descripción:
  Lee de la etiqueta que determina si el objeto está roto en el xml
y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. obj, puntero al obj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaRotoObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!obj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setRotoObj(obj, (BOOL) valor);

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaTeleportObjeto

Descripción:
  Lee de la etiqueta que determina si el objeto es un teleport en el xml
y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. obj, puntero al obj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaTeleportObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!obj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setTeleportObj(obj, (BOOL) valor);

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaDestTeleportObjeto

Descripción:
  Lee de la etiqueta que determina el destino del teleport del objeto en el xml
y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. obj, puntero al obj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaDestTeleportObjeto(xmlDocPtr doc, xmlNodePtr cur, OBJETO * obj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!obj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    /*
        setDestTeleportObj(obj, (ID) valor);
     */

    xmlFree(valor);

    return OKXML;
}

/*******************************Personajes**************************************/

/*-----------------------------------------------------------------------------
Nombre: procesaPersonaje

Descripción:
  Lee de las etiquetas que contienen la información del personaje en el xml
y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. pj, puntero al pj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaPersonaje(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj) {

    xmlChar * id = NULL;

    if ((!doc) || (!cur) || (!pj))
        return ERRXML;

    id = xmlGetProp(cur, (const xmlChar *) "id");
    if (id != NULL) {
        setIdPj(pj, (char *) id);
        xmlFree(id);
    }

    cur = cur->xmlChildrenNode; /* Primer nodo */
    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *) FIL_PJ))) {
            if (procesaFilPj(doc, cur, pj) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) COL_PJ))) {
            if (procesaColPj(doc, cur, pj) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) NOM_PJ))) {
            if (procesaNombrePj(doc, cur, pj) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) DES_PJ))) {
            if (procesaDescPj(doc, cur, pj) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) GRA_PJ))) {
            if (procesaGraphPj(doc, cur, pj) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) INV_PJ))) {
            if (procesaInvPj(doc, cur, pj) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) VIT))) {
            if (procesaVitPj(doc, cur, pj) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) VIT_TOT))) {
            if (procesaVitTotPj(doc, cur, pj) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) FZA))) {
            if (procesaFzaPj(doc, cur, pj) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) DEF))) {
            if (procesaDefPj(doc, cur, pj) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) INTER))) {
            if (procesaIntPj(doc, cur, pj) != OKXML)
                return ERRXML;
        } else if ((!xmlStrcmp(cur->name, (const xmlChar *) ATK))) {
            if (procesaAtkPj(doc, cur, pj) != OKXML)
                return ERRXML;
        }
        cur = cur->next;
    }

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaFilPj

Descripción:
  Lee de la etiqueta que contiene la fila en la que se sitúa el personaje
en el mapa del xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. pj, puntero al pj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaFilPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!pj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setFilaPj(pj, atoi((char*)valor));

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaColPj

Descripción:
  Lee de la etiqueta que contiene la columna en la que se sitúa el personaje
en el mapa del xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. pj, puntero al pj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaColPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!pj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setColPj(pj, atoi((char*)valor));

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaNombrePj

Descripción:
  Lee de la etiqueta que contiene el nombre del personaje en el xml
y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. pj, puntero al pj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaNombrePj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!pj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setNombrePj(pj, (char *) valor);

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaDescPj

Descripción:
  Lee de la etiqueta que contiene la descripción del personaje en el xml
y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. pj, puntero al pj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaDescPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!pj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setDescPj(pj, (char *) valor);

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaGraphPj

Descripción:
  Lee de la etiqueta que contiene el carácter que representa al personaje en
el mapa del xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. pj, puntero al pj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaGraphPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!pj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setGraphPj(pj, valor[0]);


    xmlFree(valor);


    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaInvPj

Descripción:
  Lee de las etiquetas que contienen el inventario del personaje en
el xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. pj, puntero al pj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaInvPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj) {

    OBJETO* obj = NULL;
    INVENTARIO* inv = NULL;
    NODO_INV* nInv = NULL;

    if ((!doc) || (!cur) || (!pj))
        return ERRXML;
    iniInventario(inv);
    cur = cur->xmlChildrenNode; /* Primer nodo */
    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *) OBJ))) {
            iniObj(obj);
            if (procesaObjeto(doc, cur, obj) != OKXML) {
                destruyeObj(obj);
                destruirInventario(inv);
                return ERRXML;
            }
            iniNodoInv(nInv, obj);
            pushNodoInv(inv, nInv);
        }
        cur = cur->next;
    }
    pj->inv = inv;
    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaVitPj

Descripción:
  Lee de las etiqueta que contiene la vitalidad actual del personaje en
el xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. pj, puntero al pj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaVitPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!pj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setVitPj(pj, atoi((char*)valor));

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaVitTotPj

Descripción:
  Lee de las etiqueta que contiene la vitalidad total del personaje en
el xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. pj, puntero al pj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaVitTotPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!pj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setVitTotPj(pj, atoi((char*)valor));

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaFzaPj

Descripción:
  Lee de las etiqueta que contiene la fuerza del personaje en
el xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. pj, puntero al pj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaFzaPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!pj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setFuerzaPj(pj, atoi((char*)valor));

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaDefPj

Descripción:
  Lee de las etiqueta que contiene la defensa del personaje en
el xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. pj, puntero al pj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaDefPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!pj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    setDefensaPj(pj, atoi((char*)valor));

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaIntPj

Descripción:
  Lee de las etiqueta que determina si se puede interactuar con el personaje
del xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. pj, puntero al pj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaIntPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!pj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    if(strcmp((char*)valor,"0")==0){
    setInteractuarPj(pj, FALSO);
    }else{
      setInteractuarPj(pj,VERDADERO);  
    }
    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaIntPj

Descripción:
  Lee de las etiqueta que determina si se puede atacar al personaje
del xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. pj, puntero al pj en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaAtkPj(xmlDocPtr doc, xmlNodePtr cur, PERSONAJE * pj) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!pj))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;
    if(strcmp((char*)valor,"0")==0){
    setAtacablePj(pj, FALSO);
    }else{
      setAtacablePj(pj,VERDADERO);  
    }
    xmlFree(valor);

    return OKXML;
}

/**********************************Mapa****************************************/

/*-----------------------------------------------------------------------------
Nombre: procesaMapa

Descripción:
  Lee de las etiqueta que contiene el dibujo del mapa
del xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. map, puntero al mapa en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaMapa(xmlDocPtr doc, xmlNodePtr cur, MAPA * map) {
    int i;
    char *pt1,*pt;
    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!map))
        return ERRXML;


    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    pt= (char*) valor;
    

    map->mapa = (char **) malloc(11 * sizeof (char *));
    
    for (i = 0; i < 11; i++) {
        pt1 = strchr(pt, '\n');

        if (pt1 == NULL) {
            map->mapa[i] = strdup(pt);
            break;
        }
        
        *pt1 = 0;

        map->mapa[i] = strdup(pt);
        pt = pt1 + 1;
        pt1 = strchr(pt, '-');
        pt = pt1;

    }


    if (valor == NULL)
        return ERRXML;
    
    xmlFree(valor);
    for (i = 0; i < 11; i++) {
        printf("%s \n",(*map).mapa[i]);
    }
    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaColMapa

Descripción:
  Lee de las etiqueta que contiene el número de columnas del mapa
del xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. map, puntero al mapa en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaColMapa(xmlDocPtr doc, xmlNodePtr cur, MAPA * map) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!map))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    sscanf((char*) valor, "%d", &map->columnas);

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaFilMapa

Descripción:
  Lee de las etiqueta que contiene el número de filas del mapa
del xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. map, puntero al mapa en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaFilMapa(xmlDocPtr doc, xmlNodePtr cur, MAPA * map) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!map))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    sscanf((char*) valor, "%d", &map->filas);

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaSalCol

Descripción:
  Lee de las etiqueta que contiene la columna en la que aparece el pj en el
mapa por primera vez del xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. map, puntero al mapa en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaSalCol(xmlDocPtr doc, xmlNodePtr cur, MAPA * map) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!map))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    sscanf((char*) valor, "%d", &map->salCol);

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaSalFil

Descripción:
  Lee de las etiqueta que contiene la fila en la que aparece el pj en el
mapa por primera vez del xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. map, puntero al mapa en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaSalFil(xmlDocPtr doc, xmlNodePtr cur, MAPA * map) {
    char* ptr;
    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!map))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;
    
    ptr = (char*) valor;
    setSalFil(map, atoi(ptr));

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaEnCol

Descripción:
  Lee de las etiqueta que contiene la columna en la que aparece el pj en el
mapa al retroceder un entorno del xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. map, puntero al mapa en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaEnCol(xmlDocPtr doc, xmlNodePtr cur, MAPA * map) {

    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!map))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;

    sscanf((char*) valor, "%d", &map->enCol);

    xmlFree(valor);

    return OKXML;
}

/*-----------------------------------------------------------------------------
Nombre: procesaEnFil

Descripción:
  Lee de las etiqueta que contiene la fila en la que aparece el pj en el
mapa al retroceder un entorno del xml y lo carga en memoria.

Argumentos de entrada:
1. doc, puntero a la estructura xmlDoc.
2. cur, puntero a la estructura xmlNode.
3. map, puntero al mapa en el que se cargarán los datos.

Retorno:
-  OKXML, si se ha terminado sin problemas
-  ERRXML, si se ha producido algún tipo de error.
-----------------------------------------------------------------------------*/
extern xml_RETURN procesaEnFil(xmlDocPtr doc, xmlNodePtr cur, MAPA * map) {
    
    char* ptr;
    xmlChar * valor = NULL;

    if ((!doc) || (!cur) || (!map))
        return ERRXML;

    valor = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);

    if (valor == NULL)
        return ERRXML;
    
    ptr = (char*) valor;
    setEnFil(map, atoi(ptr));

    xmlFree(valor);

    return OKXML;
}
/*****************************************************************************/
