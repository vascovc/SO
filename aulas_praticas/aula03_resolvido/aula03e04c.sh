#!/bin/bash

case $1 in
	[0-99])	
		Message="number in the interval"
		;;
	*)
	 	Message="numero fora do intervalo 0 e 99"
esac
case $2 in
	"sec"*)
		q="sec na palavra"
		;;
	*)
		q="not in there"
esac	
	
echo $Message
echo $q
