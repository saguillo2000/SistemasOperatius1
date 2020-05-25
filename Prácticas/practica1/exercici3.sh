#!/bin/bash

#Comprobamos que se han pasado el número correcto de parámetros
if [ $# -ne 3 ]
then 
    echo "Número incorrecto de parámetros."
    exit 1
fi

# Comprobamos que el parametro es un directorio y contiene ficheros

if [ ! -d $1  -o ! "$( ls $1 )" ]
then
    echo "Error en el directorio especificado."
    exit 1
fi

# Variables
directorio=$1
inicio=$2
fin=$3
len_incio=${#inicio}
len_fin=${#fin}
coinciden=0


# En caso de que no haya errores, miraremos cada fichero dentro del directorio
for fichero in $( ls $directorio )
do
    # Si es un fichero buscamos las palabras que contengan las cadenas de inicio y fin
    if [ -f $directorio/$fichero ]
    then
        palabras=$( cat $directorio/$fichero )
        
        for elem in $palabras
        do
            
            len_elem=${#elem}-$len_fin
            
            # Cogemos, del elemento a estudiar, los primeros y ultimos caracteres según
            # la longitud de las cadenas introducidas por teclado
            
            inicio_elem=${elem:0:len_incio}
            fin_elem=${elem:len_elem}
            fin_elem1=${elem:len_elem-1}

        
            # Comprobaremos si coinciden o no las cadenas 
            if [ "$inicio_elem" = $inicio ]
            then 
                
                if [ "$fin_elem" = $fin ]
                then
                    # En caso de coincidir, aumentadamos el contador de coincidencias e
                    # imprimimos por pantalla el fichero junto con la palabra
                    coinciden=$(($coinciden+1))
                    echo "-> Fichero: $fichero"
                    echo "-> Palabra: $elem"
                    echo "---------------------------------------------"
                fi
            fi
        done
    fi
done

# Impimimos el contador final
echo " Total de coincidencias: $coinciden"

exit 0
            
