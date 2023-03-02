#!/bin/sh

BROKER1=broker.hivemq.com
TOPIC1=MYTechLab/Ch1F2

sh ./SCADAtestbed1-out2.sh | awk '{printf "%s\n", $4; fflush();}' | mosquitto_pub -l -t $TOPIC1 -h $BROKER1
