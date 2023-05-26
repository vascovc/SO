#!/bin/bash
# This script checks the existence of a file

if [ "$#" -ne 1 ]; then #ne = not equal to one
    echo "Illegal number of parameters"
fi
#para se verificar o numero de parametros

echo "Checking..."
if [[ -f $1 ]] ; then
	echo "$1 existe."
else
	echo "$1 não existe"
fi
echo "...done."

