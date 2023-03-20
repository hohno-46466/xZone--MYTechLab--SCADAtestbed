#!/bin/sh

# Ch2 - sub pump #2
# F3  - cheking overflow

BROKER1="broker.hivemq.com"
TOPIC1="Darshana/Ch2F3"

sh ./SCADAtestbed1-out.sh "SW" "MOKA1" | awk '{printf "%s\n", 1-$9; fflush();}' | mosquitto_pub -l -t $TOPIC1 -h $BROKER1

