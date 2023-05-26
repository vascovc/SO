#!/bin/bash
function read_array() {
r=0
declare lista
while true
do
	echo "Introduza um valor, prima q para parar"
	read a
	if [[ $a == q ]] ; then
		break
	fi
	r=$(($r+1))
	lista[$r]=$a
done
echo "Lista inicial: "
for i in ${!lista[@]}; do
	echo -e -n "${lista[i]} "
done
echo
#sort
for ((i=0; i < ${#lista[@]}; i++)); do
	min=${lista[i]}
	for (( j=$i; j < ${#lista[@]}; j++)) ; do
		if [[ ${lista[j]} -lt $min ]] ; then
			min=${lista[j]}
			lista[j]=${lista[i]}
			lista[i]=$min
		fi
	done
done
#print sorted
echo 'Lista ordenada: '
for i in ${!lista[@]}; do
	echo -e -n "${lista[i]} "
done
echo
}
#read_array
# ficou estranho não ordena os valores pedidos mas cagativo

function read_file() {
IFS=$' \n' read -d '' -a lista < $1
echo "Lista inicial: "
for i in ${!lista[@]}; do
	echo -e -n "${lista[i]} "
done
echo
for ((i = 0; i < ${#lista[@]}; i++)); do
	min=${lista[i]}
	for (( j = $i; j < ${#lista[@]}; j++)) ; do
		if [[ ${lista[j]} -lt $min ]] ; then
			min=${lista[j]}
			lista[j]=${lista[i]}
			lista[i]=$min
		fi
	done
done
echo 'Lista ordenada: '
for i in ${!lista[@]}; do
	echo -e -n "${lista[i]} "
done
echo
}
#read_file $1
