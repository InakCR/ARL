/******************************************************************************
*
*  Nombre del fichero: tipos.h
*
*  Nombre del módulo correspondiente:
*
*  Descripción: Tipos generales 
*
*  Realizado por: Diego Chicote
*
******************************************************************************/

#ifndef TIPOS_H
#define	TIPOS_H

/*=== Cabeceras =============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*=== Definiciones ==========================================================*/

typedef char* ID;
#define MAX_ID 10

/*El tipo BOOL se usa principalmente, para obetener una respuesta rápida
 al requerir a través de una función un tipo de dato booleano:
 -FALSO: false
 -VERDADERO: true
 -ERRB: se produce cuando la funcion recibe un ptr a NULL*/
typedef enum {FALSO = 0, VERDADERO = 1, ERRB = -1}BOOL;
/*El tipo STATUS se usa para llevar un control de errores sobre las funciones:
 -ERROR: Fallo por que el ptr. apunta a NULL o el objeto está vacío.
 -OKE: Todo correcto.
 -ERROR_RM/LM: Errores al reservar o liberar memoria.
 -ERROR_FMT: Errores de incompatibilidad de formato, o por ser las cadenas mayores
 del máximo definido.*/
typedef enum {ERROR = 0, OKE = 1, ERROR_RM = 2, ERROR_LM = 3,ERROR_FMT}STATUS;

#endif	/* TIPOS_H */

