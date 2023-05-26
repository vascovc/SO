#!/bin/bash
# For all the files in a folder, show their properties

if [[ "$#" -gt 2 ]] ; then
	echo "wrong number of inputs"
	exit 1
elif [[ -d $1/* ]] ; then
	echo "input not a directory"
	exit 2
fi

if [[ $2 == -r ]] ; then
	for f in $1/* ; do
		file_name=${f#"$1/*"}
		remove_file=${f%"$file_name"}
		#echo ${f##/ #"new_"}
		file_name_new=${file_name#"new_"}
		mv -v "$f" "$remove_file$file_name_new"
	done 
else
	for f in $1/* ; do
		#echo "${f##*/}"
		mv "$f" "${f%/*}/new_${f##*/}"
	done
fi
