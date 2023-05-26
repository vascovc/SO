#!/bin/bash
function equal_greater() {
	if [[ "$1" -eq "$2" ]] ; then
		Mesg="numeros iguais"
	elif [[ "$1" -gt "$2" ]] ; then
		Mesg="$1 é maior que $2"
	else
		Mesg="$1 é menor que $2"
	fi
	return Mesg
}
#equal_greater $1 $2

function alinea_e() {
	echo "Introduza o primeiro valor"
	read a
	echo "Introduza o segundo valor"
	read b
	equal_greater $a $b 
	echo $Mesg
	return 0
}
alinea_e
