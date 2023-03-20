#!/bin/sh

# Ch0 - main pump
# F3  - cheking overflow

BROKER1="broker.hivemq.com"
TOPIC1="Darshana/Ch0F3"

sh ./SCADAtestbed1-out.sh "SW" "MOKA1" | awk '{printf "%s\n", 1-$13; fflush();}' | mosquitto_pub -l -t $TOPIC1 -h $BROKER1

