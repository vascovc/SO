#!/bin/bash
# Exit status
ping -c 1 www.ua.pt
echo "Exit code: $?" # $? exit code of the last process terminated
ping -c 1 wwwww.ua.pt
echo "Exit code: $?"

