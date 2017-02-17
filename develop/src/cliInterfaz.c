/* 
 * File:   cliInterfaz.c
 * Author: tabirra
 *
 * Created on 12 de abril de 2013, 10:43
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Lectorxml.h"
#include "mundo.h"
#include "interface.h"
#include "consola.h"
#include "mapa.h"
#include "inventarioInterfaz.h"
#include "seleccion.h"


/*
 * 
 */
int cliInterfaz() {

    INTERFAZ* inter = NULL;
    MUNDO m;
    char* msg=NULL;

    if (iniMundo(&m) == ERROR_RM)
        return (EXIT_FAILURE);

    if (procesaMundo("DM.xml", &m) == ERRXML) {
        destruirMundo(&m);
        return (EXIT_FAILURE);
    }
    



/*
    msg = (char*) malloc(sizeof (char)*100);
    msg="atacar alpha";
    
    seleccionAccion(m.primero,m.pj,inter,msg);
*/



    /*Pintarlo temporalmente a lo bruto*/
    m.primero->ent->mapaEnt->mapa[2][5] = '8';
/*
    m.primero->ent->mapaEnt->mapa[3][42] = '/';
    m.primero->ent->mapaEnt->mapa[4][21] = 'F';
*/
   

    msg = (char*) malloc(sizeof (char)*100);

    inter = iniciaInterfaz();

    if (inter == NULL) {
        clear();
        terminaInterfaz(inter);
        free(msg);
        return (EXIT_FAILURE);
    }



    iniciaConsola(inter);
    
    pintaMapa(inter,m.primero->ent->mapaEnt);
    
    pintaStats(inter,m.pj);
    
    pintaInventario(inter,m.primero,m.pj->inv);
    
    capturaConsola(inter, m.primero, m.pj, msg);

    terminaInterfaz(inter);

    free(msg);

    return (EXIT_SUCCESS);
}

