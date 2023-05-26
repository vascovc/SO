#!/bin/bash

#1
for (( a = 0 ; a < 4 ; a++)); do
	xterm &
	echo "valor de A $a"
done

#2
for b in 0 1 2 3 ; do
	#xterm &
	echo "valor de B $b"
done

#3
for c in {0..3} ; do
	#xterm &
	echo "valor de C $c"
done

#4
for d in {0..7..2} ; do
	#xterm &
	echo "valor de D $d"
done

#5 until
E="0"
until [[ E -gt 4 ]] ; do
	#xterm &
	echo "valor de E $E"
	E=$(($E+1))
done

