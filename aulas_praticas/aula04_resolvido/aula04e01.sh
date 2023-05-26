#!/bin/bash
function imprime_msg()
{
	echo "A minha primeira funcao"
	#b
	echo "$(date | cut -d " " -f 1-5)"
	echo "$(hostname)"
	echo "$PATH"
	echo "$USER" #pode ser a de baixo
	echo $(who | cut -d " " -f 1)
	
	return 0
}
#imprime_msg 
