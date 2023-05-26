#!/bin/bash
# For all the files in a folder, show their properties

if [[ "$#" -gt 1 ]] ; then
	echo "wrong number of files"
elif [[ -d $1/* ]] ; then
	echo "input not a directory"
fi

for f in $1/*; do
	file "$f"
done 
