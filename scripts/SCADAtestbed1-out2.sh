#!/bin/sh

BROKER1=broker.hivemq.com
TOPIC1=MYTechLab/STBout1

set -x
mosquitto_sub -t $TOPIC1 -h $BROKER1 | sed -u -n '/^SW/p'
