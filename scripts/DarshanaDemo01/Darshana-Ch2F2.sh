#!/bin/sh

# Ch2 - sub pump #2
# F2  - reading water level

BROKER1="broker.hivemq.com"
TOPIC1="Darshana/Ch2F2"

sh ./SCADAtestbed1-out.sh "SW" "MOKA1" | awk '{printf "%s\n", $8; fflush();}' | mosquitto_pub -l -t $TOPIC1 -h $BROKER1

