#!/bin/sh

# Ch4 - sub pump #4 (No pumps available at this time)
# F2  - reading water level

BROKER1="broker.hivemq.com"
TOPIC1="Darshana/Ch4F2"

sh ./SCADAtestbed1-out.sh "SW" "MOKA2" | awk '{printf "%s\n", $8; fflush();}' | mosquitto_pub -l -t $TOPIC1 -h $BROKER1

