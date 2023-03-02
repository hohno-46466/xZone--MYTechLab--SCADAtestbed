#!/bin/sh

BROKER1=broker.hivemq.com
TOPIC1=MYTechLab/STBin1

set -x
cat -u | mosquitto_pub -l -t $TOPIC1 -h $BROKER1

