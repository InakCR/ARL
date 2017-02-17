/*Fichero principal de juego*/

/*Bibliotecas necesarias*/
#include <stdio.h>
#include <stdlib.h>
#include "mundo.h"
#include "mapa.h"
#include "consola.h"
#include "Lectorxml.h"
#include "seleccion.h"
#include "inventarioInterfaz.h"

/*Funcion main*/
int main(int argc, char** argv) {

    MUNDO m;                    /*Mundo de juego.*/
    INTERFAZ* inter = NULL;     /*Interfaz grafica.*/
    char* msg = NULL;           /*Cadena auxiliar.*/

    if (iniMundo(&m) == ERROR_RM)/*Se inicializa el mundo.*/
        return (EXIT_FAILURE);

    if (procesaMundo("DM.xml", &m) == ERRXML) {/*Se lee el mundo de un xml.*/
        destruirMundo(&m);                     /*En caso de producirse algun error se libera el mundo.*/
        return (EXIT_FAILURE);
    }

    msg = (char*) malloc(sizeof (char)*100);   /*Reservamos espacio para la cadena auxiliar.*/

    inter = iniciaInterfaz();                  /*Iniciamos la interfaz grafica.*/

    if (inter == NULL) {
        clear();
        terminaInterfaz(inter);
        free(msg);
        return (EXIT_FAILURE);
    }

    iniciaConsola(inter);                       /*Iniciamos la consola de juego*/

    pintaMapa(inter, m.primero->ent->mapaEnt);  /*Pintamos el primer entorno.*/

    pintaStats(inter, m.pj);                    /*Pintamos los stats del pj.*/

    pintaInventario(inter, m.primero, m.pj->inv);/*Pintamos los inventarios del pj, y entorno.*/

    capturaConsola(inter, m.primero, m.pj, msg);/*Iniciamos la captura de datos.*/

    terminaInterfaz(inter);/*Liberamos la memoria usada en la interfaz.*/

    free(msg);             /*Liberamos la cadena auxiliar.*/

    return (EXIT_SUCCESS);
}

