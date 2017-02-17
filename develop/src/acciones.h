/******************************************************************************
 *
 *  Nombre del fichero: acciones.h
 *
 *  Nombre del módulo correspondiente: Logica.
 *
 *  Descripción: Protipos de las funciones para la modificacion de las estructuras del modulo logica.
 *
 *  Realizado por: Iñaki Cadalso Reymundo.
 *
 ******************************************************************************/

#include "mundo.h"
#define  MAXFUERZA 40
#define  MAXDEFENSA 40
#define  DISTANCIA  6

/*------------------------------------------------------------------
 *@name hablar
 *@brief Inicia una conversacion con un personaje interectuable
 *@param (PERSONAJE *pj,INTERFAZ *inter,ENTORNO *ent,PERSONAJE *pnj)Personaje a conversar , interfaz a modificar y peronaje principal.
 *@return un char con el estado de la conversacion;
------------------------------------------------------------------*/
STATUS hablar(ENTORNO *ent, INTERFAZ *inter, PERSONAJE *pj, PERSONAJE *pnj);
/*------------------------------------------------------------------
 *@name tratamientoCadena
 *@brief Procede a poner en mayusculas cada caracter de la cadena introducida,
 * divide la cadena en 2 tokens ,uno de accion y otro del nombre del objeto/personaje.
 * El 1º token es la propia cadena y el 2º eñ devuelto.
 *@param (char *cad) cadena a tratar.
 *@return Devuelve el 2º token del nombre del objeto/personaje.
------------------------------------------------------------------*/
char* tratamientoCadena(char **cad);
/*------------------------------------------------------------------
 *@name combate
 *@brief calculos de atacar enemigo-personaje.
 *@param (ENTORNO *ent,PERSONAJE * pj,INTERFAZ *inter,PERSONAJE *ene)Personaje principal,Interfaz amodificar ,Personaje enemigo a atcar.
 *@return char con el estado del combate.
------------------------------------------------------------------*/
char* combate(ENTORNO* ent, PERSONAJE * pj, INTERFAZ *inter, PERSONAJE *ene);
/*------------------------------------------------------------------
 *@name coger.
 *@brief Comprueba la posicion del objeto respecto al personaje , y lo añade al inventario.
 *@param (ENTORNO *ent,PERSONAJE* pnj, OBJETO *obj) Entorno donde se encuentra todo, el jugador y el objeto añadir.
 *@return un char con el estado q se a conseguido en la accion.
------------------------------------------------------------------*/
char* coger(ENTORNO *ent, PERSONAJE* pnj, OBJETO *obj);
/*------------------------------------------------------------------
 *@name examinar.
 *@brief Consulta la descripcion de  un entorno, objeto o personaje.
 *@param (ENTORNO *ent, OBJETO *obj, PERSONAJE *pj) Entorno,objeto o personaje a dar descripcion.
 *@return un char con el estado que se a conseguido en la accion.
------------------------------------------------------------------*/
char* examinar(ENTORNO *ent, OBJETO *obj, PERSONAJE *pj);

/*------------------------------------------------------------------
 *@name atacar.
 *@brief Comprueba la correcta posicion del enemigo y según estadisticas del jugador y enemigo
 * se modifica según los resultados.
 *@param (ENTORNO *ent,INTERFAZ *inter,PERSONAJE* pnj,PERSONAJE* ene)Entorno, interfaz , tu personaje y el personaje a atacar.
 *@return un char con el estado q se a conseguido en la accion.
------------------------------------------------------------------*/
char* atacar(ENTORNO *ent, INTERFAZ *inter, PERSONAJE* pnj, PERSONAJE* ene);
/*------------------------------------------------------------------
 *@name usar.
 *@brief Busca el objeto en el invetario y aplica las estadisticas al jugador.
 *@param (ENTORNO *ent, OBJETO *obj,PERSONAJE* pnj)Entorno, objeto a usar y el jugador.
 *@return un char con el estado q se a conseguido en la accion.
------------------------------------------------------------------*/
char* usar(ENTORNO *ent, OBJETO *obj, PERSONAJE* pnj);
/*------------------------------------------------------------------
 *@name comprobarPos.
 *@brief Comprueba la posicion del personaje respecto enemigos/objetos.
 *@param (int x,int y,int z,int t)Posiciones.
 *@return VERDADERO o FALSO.
------------------------------------------------------------------*/
BOOL comprobarPos(int x, int y, int z, int t);

STATUS nivelFinal(ENTORNO* ent, INTERFAZ* inter);

BOOL compruebaNivel(PERSONAJE* pj);