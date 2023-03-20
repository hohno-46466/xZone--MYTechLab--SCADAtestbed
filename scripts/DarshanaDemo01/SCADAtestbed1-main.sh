#!/bin/sh

# Prev update: Fri Mar  3 04:05:40 AST 2023
# Last update: Mon Mar 20 21:22:44 JST 2023

SERIAL=${1:-"/dev/cu.usbmodem21301"}

BROKER1="broker.hivemq.com"
BROKER2="broker.hivemq.com"

TOPIC1="MYTechLab/STBin1"
TOPIC2="MYTechLab/STBout1"

# Verify that the necessary commands are available
(which -a cu > /dev/null 2>&1 || (echo "# Error: install cu"; exit 1)) || exit 1
(which -a nkf > /dev/null 2>&1 || (echo "# Error: install nkf"; exit 1)) || exit 1
(which -a mosquitto_sub > /dev/null 2>&1 || (echo "# Error: install mosquitto_sub"; exit 1)) || exit 1
(which -a mosquitto_pub > /dev/null 2>&1 || (echo "# Error: install mosquitto_pub"; exit 1)) || exit 1

# Check to see if you have administrative privileges
sudo date || exit 1

set -x
mosquitto_sub -t $TOPIC1 -h $BROKER1 \
| (cat -u | sudo cu -s 57600 -l $SERIAL | nkf -u -Lu) \
| mosquitto_pub -l -t $TOPIC2 -h $BROKER2 \

