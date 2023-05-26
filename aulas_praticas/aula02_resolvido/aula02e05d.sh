#!/bin/bash
echo using '$*:' $*
for i in $*; do echo "$i"; done
echo using '$@:' $@
for i in $@; do echo "$i"; done
echo using '"$*":' "$*"
for i in "$*"; do echo "$i"; done
echo using '"$@":' "$@"
for i in "$@"; do echo "$i"; done

# o @ respeita as coisas dentro de plicas
