#!/bin/bash
# Conditional block if
if [ $1 = $2 ] ; then
 echo "O arg1 é igual ao arg2"
else
 echo "Os args são diferentes"
fi
# aqui com aspas e espaços não vai funcionar

#passa a estar correto se
if [ "$1" = "$2" ] ; then
 echo "O arg1 é igual ao arg2"
else
 echo "Os args são diferentes"
fi
