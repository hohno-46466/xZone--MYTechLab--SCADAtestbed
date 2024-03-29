#!/bin/sh

# Prev update: Fri Mar  3 04:05:40 AST 2023
# Last update: Mon Mar 20 21:21:30 JST 2023

KEY1=${1:-"LED"}

TOPICx=${2:-"MOKA1"}
TOPIC1="MYTechLab/${TOPICx}-out"

BROKER1=${3:-"broker.hivemq.com"}

(which -a mosquitto_sub > /dev/null 2>&1 || (echo "# Error: install mosquitto_sub"; exit 1)) || exit 1

set -x
mosquitto_sub -t $TOPIC1 -h $BROKER1 | sed -u -n "/^$KEY1/p"
