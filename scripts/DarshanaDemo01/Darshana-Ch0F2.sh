#!/bin/sh

# Ch0 - main pump
# F2  - reading water level

BROKER1="broker.hivemq.com"
TOPIC1="Darshana/Ch0F2"

sh ./SCADAtestbed1-out.sh "SW" | awk '{printf "%s\n", $12; fflush();}' | mosquitto_pub -l -t $TOPIC1 -h $BROKER1

