#!/bin/sh

# Prev update: Fri Mar  3 04:05:40 AST 2023
# Last update: Mon Mar 20 21:22:08 JST 2023

BROKER1="broker.hivemq.com"
TOPIC1="MYTechLab/STBin1"

(which -a mosquitto_pub > /dev/null 2>&1 || (echo "# Error: install mosquitto_pub"; exit 1)) || exit 1

set -x
cat -u | mosquitto_pub -l -t $TOPIC1 -h $BROKER1

