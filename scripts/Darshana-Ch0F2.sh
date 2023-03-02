#!/bin/sh

BROKER1=broker.hivemq.com
TOPIC1=MYTechLab/Ch0F2

sh ./SCADAtestbed1-out2.sh | awk '{printf "%s\n", $12; fflush();}' | mosquitto_pub -l -t $TOPIC1 -h $BROKER1

