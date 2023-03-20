#!/bin/sh

# Ch3 - sub pump #3 (No pumps available at this time)
# F3  - cheking overflow

BROKER1="broker.hivemq.com"
TOPIC1="Darshana/Ch3F3"

sh ./SCADAtestbed1-out.sh "SW" "MOKA2" | awk '{printf "%s\n", $5; fflush();}' | mosquitto_pub -l -t $TOPIC1 -h $BROKER1

