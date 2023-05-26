#!/bin/bash
# Agrupamento de comandos na Bash
{
 i=0
 while read line; do # teste feito com um comando
 echo $i: $line
 i=$(($i+1)) #incrementar i
 done
} < $1 #e para fazer o redirecionamento do ficheiro 

#o comando read le a variavel associada
