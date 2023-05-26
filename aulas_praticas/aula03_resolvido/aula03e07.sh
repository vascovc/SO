#!/bin/bash
# Calculate the sum of a series of numbers.
SCORE="0"
SUM="0"
I="0"
Media="0"
while true; do
	 echo -n "Enter your score [0-10] ('q' to quit): "
	 read SCORE;
	 if (("$SCORE" < "0")) || (("$SCORE" > "10")); then
	 	echo "Try again: "
	 elif [[ "$SCORE" == "q" ]]; then
	 	echo "Sum: $SUM."
	 	Media=$((SUM/I))
	 	echo "Media: $Media"
	 	break
	 elif [[ "$SCORE" == "r" ]] ; then
	 	echo "reset feito"
	 	I="0"
	 	SUM="0"
	 else
	 	SUM=$((SUM + SCORE))
	 	I=$((I+1))
	 fi
done
echo "Exiting."
