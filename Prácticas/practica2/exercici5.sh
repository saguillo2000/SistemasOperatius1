#!/bin/bash

#Comprobamos que se han pasado el número correcto de parámetros
if [ $# -ne 2 ]
then 
    echo "Número incorrecto de parámetros."
    exit 1
fi

col=4

# Comprobamos que el segundo parametro es VSZ o RSS
if [ $2 != "RSS" ]
then
    col=5
    if [ $2 != "VSZ" ]
    then
        echo "Error en el segundo parámetro: ha de ser VSZ o RSS."
        exit 1
    fi

fi

# Comprobamos que el usuario pasado por parámetro existe 
cat /etc/passwd | grep "$1" > /dev/null && userExiste=0 || userExiste=1

# Si existe el usuario
if [ $userExiste -eq 0 ]
then
    # Obetenemos los procesos
    procesos=$(ps aux | grep "^$1" | sort -nk$col -r | head -10 | awk 'BEGIN {print "VSZ       RSS       Proces "}  {print $5,$6,$11 }' )
    echo "$procesos"

else
    # Si no existe, salta un excepción
    echo "El usuario $1 no tiene ningún proceso asociado."
    exit 1
fi

exit 0


