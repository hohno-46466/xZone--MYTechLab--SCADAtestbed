#!/bin/sh

SERIAL=${1:-/dev/cu.usbmodem21301}

BROKER1=broker.hivemq.com
BROKER2=broker.hivemq.com

TOPIC1=MYTechLab/STBin1
TOPIC2=MYTechLab/STBout1

set -x
mosquitto_sub -t $TOPIC1 -h $BROKER1 \
| (cat -u | sudo cu -s 57600 -l $SERIAL | nkf -u -Lu) \
| mosquitto_pub -l -t $TOPIC2 -h $BROKER2 \

# | sed -u -n '/^LED/p' \
