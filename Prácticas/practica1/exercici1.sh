#!/bin/bash

#Comprobamos que se han pasado el número correcto de parámetros
if [ $# -ne 1 ]
then 
    echo "Número incorrecto de parámetros."
    exit 1
fi

# Variables
directorio=$1
fichero_mas_grande=
mida=0
contador=-2
secondconter=-1



# Comprobamos que el parámetro pasado es un directorio y que contenga ficheros 
if [ ! -d $1  -o ! "$(ls $1)" ]
then
    echo "Error en el directorio especificado."
    exit 1
fi

# En caso de que no haya errores, buscaremos el fichero más grande a partir del 
#comando ls -l 
for fichero in $( ls -l $directorio ) 
do
    
    # De todos los datos cogemos unicamente el tamaño del fichero
    if [ $(($contador%9)) -eq 4 ]
    then

        if [ $fichero -gt $mida ]
        then
            
            mida=$fichero
            secondconter=4
        fi
    fi
    
    
    if [ $secondconter -eq 0 ]
    then 
        fichero_mas_grande=$fichero
        secondconter=0
    
    fi
    
    contador=$(($contador+1))
    secondconter=$(($secondconter-1))
    
            
done


# Imprimimos los resultados
echo "Fichero más grande: $fichero_mas_grande, $mida bytes"
exit 0
    
