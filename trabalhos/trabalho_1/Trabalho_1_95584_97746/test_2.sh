#!/bin/bash
ifconfig
timeout 11 ./netifstat.sh -l -k -v 5
ifconfig
