#!/bin/bash
echo "O meu editor por omissão $BASH \$BASH"
echo 'O meu editor por omissão $BASH \$BASH'
echo $(( 5 + 5 ))
(( 5 > 0 )) && echo "cinco é maior do que zero"
today=$(date); echo $today

#alinea c
#i
echo
ls -l -d /etc/*
echo
#ii
echo
ls -l -d /etc/a*
echo
#iii
echo
ls -l -d /etc/a???*
echo
#iv
echo
ls -l -d /etc/*conf*
echo
