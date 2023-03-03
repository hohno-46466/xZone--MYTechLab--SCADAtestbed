#!/bin/sh

# Last update: Fri Mar  3 04:05:40 AST 2023

KEY1=${1:-LED}
BROKER1=${2:-broker.hivemq.com}
TOPIC1=${3:-MYTechLab/STBout1}

(which -a mosquitto_sub > /dev/null 2>&1 || (echo "# Error: install mosquitto_sub"; exit 1)) && exit 1

set -x
mosquitto_sub -t $TOPIC1 -h $BROKER1 | sed -u -n "/^$KEY1/p"
