#!/bin/sh

# Ch1 - sub pump #1
# F3  - cheking overflow

BROKER1="broker.hivemq.com"
TOPIC1="Darshana/Ch1F3"

sh ./SCADAtestbed1-out.sh "SW" "MOKA1" | awk '{printf "%s\n", 1-$5; fflush();}' | mosquitto_pub -l -t $TOPIC1 -h $BROKER1

