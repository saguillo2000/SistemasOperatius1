#!/bin/bash

#Comprobamos que se han pasado el número correcto de parámetros
if [ $# -ne 3 ]
then 
    echo "Número incorrecto de parámetros."
    exit 1
fi


# Comprobamos que el primer parametro es un directorio
if [ ! -d $1 ]
then
    echo "Error en el directorio especificado."
    exit 1
fi


# Creamos el directorio donde copiaremos los ficheros
mkdir fitxersEx3 

# Encontramos los ficheros con la extensión y medida especificados
# para copiarlos al directorio anterior
find $1 -type f -name "*.$2" -and -size +$3 -exec cp {} fitxersEx3 \;


# Si no hay nada en el directorio, salta un excepción
if [ ! "$( ls fitxersEx3 )" ]
then
    echo " No hay ningun fichero que cumpla las condiciones especificadas."
    rmdir fitxersEx3
    exit 1
else
    # Si hay ficheros, creamos el .tar.gz
    tar -czf fitxersEx3.tar.gz fitxersEx3
    echo "Se han comprimido todos los ficheros .$2 con medida superir a $3 en fitxersEx3.tar.gz"
    
fi

exit 0

