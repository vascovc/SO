#!/bin/bash
if test "$#" -ne 1 ; then
	echo "demasiados argumentos"
fi

if (( (($1 < 10)) && (($1 > 5)) )) ;then
	echo "número maior que 5 e menor do que 10"
else
	echo "menor ou igual a 5 ou maior ou igual a 10"
fi

#como é aritmetico tem que ser com dois parenteses
