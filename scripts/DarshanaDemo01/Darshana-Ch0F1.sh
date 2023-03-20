#!/bin/sh

BROKER1="broker.hivemq.com"
TOPIC1="Darshana/Ch0F1"

mosquitto_sub -t $TOPIC1 -h $BROKER1 \
| awk '{
    if ($1 == "0") { printf "echo 0 0 0 | ./SCADAtestbed1-in.sh\n"; fflush()}
    if ($1 == "1") { printf "echo 0 0 255 | ./SCADAtestbed1-in.sh\n"; fflush()}
  }' \
| sh -x
