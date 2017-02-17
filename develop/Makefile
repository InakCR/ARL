#=============================================================
# Construccion de los ejecutables
#=============================================================
## 
## 

# Compilador
CC= gcc
FLAGS= -lncurses -lpanel -g
CFLAGS=`xml2-config --cflags`
LIBS=`xml2-config --libs` -lxml2

#Directorios
PROJECT_HOME=..
DEVELOP_DIR=$(PROJECT_HOME)/develop
SRC_DIR=$(DEVELOP_DIR)/src
DOCS_DIR=$(DEVELOP_DIR)/docs
INSTALL_DIR=$(PROJECT_HOME)/install
TEST_DIR=$(PROJECT_HOME)/test


#=============================================================
# Construccion del ejecutable
#=============================================================
juego: copiaArchivos mundo.o entorno.o inventario.o pjsEntorno.o objeto.o personaje.o acciones.o seleccion.o consola.o interface.o inventarioInterfaz.o mapa.o Lectorxml.o main.o 
	@ echo ""
	@ echo "Generando ejecutable..."
	$(CC) -o $(INSTALL_DIR)/juego mundo.o entorno.o inventario.o pjsEntorno.o objeto.o personaje.o acciones.o seleccion.o consola.o interface.o inventarioInterfaz.o mapa.o Lectorxml.o main.o $(CFLAGS) $(LIBS) $(FLAGS)
	@ echo ""
	@ echo "Compilacion finalizada!!"
	@ echo ""
	@ echo "========================================================================================="
	@ echo "====                            PROYECTO REALIZADO POR:                              ===="
	@ echo "====                                                                                 ===="
	@ echo "==== ** Iñaki Cadalso Reymundo, Diego Chicote González, Miguel Angel Gómez-Tavira ** ===="
	@ echo "====                                                                                 ===="
	@ echo "========================================================================================="
	@ echo ""
#=============================================================
# Generacion .o
#=============================================================
## Por cada archivo .c se genera un .o
## Un archivo .o depende del archivo .c y de todos los .h propios 
## que se incluyan en el .c

copiaArchivos:
	@ echo ""
	cp $(DOCS_DIR)/*\.txt $(INSTALL_DIR)
	cp $(DOCS_DIR)/*\.xml $(INSTALL_DIR)

mundo.o: $(SRC_DIR)/mundo.c
	@ echo ""
	@ echo "Proyecto de Programacion 2013"
	@ echo "" 
	@ echo "Generando mundo..."
	$(CC) -c $(SRC_DIR)/mundo.c $(FLAGS)

entorno.o: $(SRC_DIR)/entorno.c 
	@ echo "" 
	@ echo "Generando entorno..."
	$(CC) -c $(SRC_DIR)/entorno.c $(FLAGS)

inventario.o: $(SRC_DIR)/inventario.c
	@ echo ""
	@ echo "Generando inventario..."
	$(CC) -c $(SRC_DIR)/inventario.c $(FLAGS)

pjsEntorno.o: $(SRC_DIR)/pjsEntorno.c 
	@ echo ""
	@ echo "Generando pjsEntorno..."
	$(CC) -c $(SRC_DIR)/pjsEntorno.c $(FLAGS)

objeto.o: $(SRC_DIR)/objeto.c
	@ echo ""
	@ echo "Generando objeto..."
	$(CC) -c $(SRC_DIR)/objeto.c $(FLAGS)

personaje.o: $(SRC_DIR)/personaje.c 
	@ echo ""
	@ echo "Generando personaje..."
	$(CC) -c $(SRC_DIR)/personaje.c $(FLAGS)

acciones.o: $(SRC_DIR)/acciones.c
	@ echo ""
	@ echo "Generando acciones..."
	$(CC) -c $(SRC_DIR)/acciones.c $(FLAGS)

seleccion.o: $(SRC_DIR)/seleccion.c 
	@ echo ""
	@ echo "Generando seleccion..."
	$(CC) -c $(SRC_DIR)/seleccion.c $(FLAGS)

consola.o: $(SRC_DIR)/consola.c
	@ echo ""
	@ echo "Generando consola..."
	$(CC) -c $(SRC_DIR)/consola.c $(FLAGS)

interface.o: $(SRC_DIR)/interface.c
	@ echo ""
	@ echo "Generando interface..."
	$(CC) -c $(SRC_DIR)/interface.c $(FLAGS)
 
inventarioInterfaz.o: $(SRC_DIR)/inventarioInterfaz.c
	@ echo ""
	@ echo "Generando invetarioInterfaz..."
	$(CC) -c $(SRC_DIR)/inventarioInterfaz.c $(FLAGS)

mapa.o: $(SRC_DIR)/mapa.c
	@ echo ""
	@ echo "Generando mapa..."
	$(CC) -c $(SRC_DIR)/mapa.c $(FLAGS)

Lectorxml.o: $(SRC_DIR)/Lectorxml.c 
	@ echo ""
	@ echo "Generando Lectorxml..."
	$(CC) -c $(SRC_DIR)/Lectorxml.c  $(CFLAGS) $(LIBS) $(FLAGS)

main.o: $(SRC_DIR)/main.c
	@ echo ""
	@ echo "Generando main..."
	$(CC) -c $(SRC_DIR)/main.c $(FLAGS) $(CFLAGS) $(LIBS)

ejecutar: 
	cd ..; cd install; \
	./juego DM

	  
#=============================================================
# 
# AUTORES
# 
#=============================================================
autores:
	@ echo ""
	@ echo "========================================================================================="
	@ echo "====                            PROYECTO REALIZADO POR:                              ===="
	@ echo "====                                                                                 ===="
	@ echo "==== ** Iñaki Cadalso Reymundo, Diego Chicote González, Miguel Angel Gómez-Tavira ** ===="
	@ echo "====                                                                                 ===="
	@ echo "========================================================================================="

#=============================================================
# Limpia todos los .o
#=============================================================
limpiar :
	@ echo "Limpiando..."
	rm -rf *\.o $(INSTALL_DIR)/juego $(INSTALL_DIR)/*\.txt $(INSTALL_DIR)/*\.xml

#=============================================================
# Ayuda
#=============================================================
ayuda:	
	@ echo Uso: make [Objetivo]
	@ echo "make ejecutar \t Ejecuta el proyecto"
	@ echo "make autores \t Muestra los autores del proyecto"
	@ echo "make \t Crea el ejecutable del proyecto"
	@ echo "make limpiar \t Limpia la carpeta install"


