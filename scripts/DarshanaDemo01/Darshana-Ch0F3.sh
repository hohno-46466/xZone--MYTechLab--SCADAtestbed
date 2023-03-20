#!/bin/sh

BROKER1="broker.hivemq.com"
TOPIC1="Darshana/Ch0F3"

sh ./SCADAtestbed1-out.sh "SW" | awk '{printf "%s\n", $13; fflush();}' | mosquitto_pub -l -t $TOPIC1 -h $BROKER1

