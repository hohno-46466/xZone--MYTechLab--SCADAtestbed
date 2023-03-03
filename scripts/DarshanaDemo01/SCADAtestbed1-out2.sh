#!/bin/sh

# Last update: Fri Mar  3 04:05:40 AST 2023

BROKER1=broker.hivemq.com
TOPIC1=MYTechLab/STBout1

(which -a mosquitto_sub > /dev/null 2>&1 || (echo "# Error: install mosquitto_sub"; exit 1)) && exit 1

set -x
mosquitto_sub -t $TOPIC1 -h $BROKER1 | sed -u -n '/^SW/p'
