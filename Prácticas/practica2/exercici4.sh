#!/bin/bash

#Comprobamos que se han pasado el número correcto de parámetros
if [ $# -ne 1 ]
then 
    echo "Número incorrecto de parámetros."
    exit 1
fi


# Comprobamos que el usuario pasado por parámetro existe:
#   userExiste = 0 implica que el usuario SI existe
#   userExiste = 1 implica que el usuario NO existe y
#   salta una excepcion
cat /etc/passwd | grep "$1" > /dev/null && userExiste=0 || userExiste=1


# Si no existe el usuario
if [ $userExiste -ne 0 ]
then
    # Salta una excepción
    echo "El usuario $1 no existe en este ordenador."
    exit 1
fi


# Variables
grupos=""


# Si existe extraemos de los 2 ficheros la información
nombreUser=$(grep $1 /etc/passwd | awk -v OFS=", " 'BEGIN {FS=":"}; {print $5}')

idUsuario=$(grep $1 /etc/passwd | awk -v OFS=", " 'BEGIN {FS=":"}; {print $3}')

users=$(grep $1 /etc/passwd | awk -v OFS=", " 'BEGIN {FS=":"}; {print $4"\n(users), "}')

directorioActual=$(grep $1 /etc/passwd | awk -v OFS=", " 'BEGIN {FS=":"}; {print $6}')

interprete=$(grep $1 /etc/passwd | awk -v OFS=", " 'BEGIN {FS=":"}; {print $7}')


grupos="$grupos$(grep $1 /etc/group | awk -v OFS=", " 'BEGIN {FS=":"}; {print $3"\n" "("$1")" ","}')"


# Imprimimos los resultados 
echo "Nombre del usuario: " $nombreUser

echo "Identificador de usuario: " $idUsuario

echo "Grupos a los que pertenece: " $users $grupos
 
echo "Directorio actual del usuario: " $directorioActual

echo "Interprete por defecto:" $interprete

exit 0
