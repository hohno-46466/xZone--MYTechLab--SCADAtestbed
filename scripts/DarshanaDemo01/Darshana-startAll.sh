#!/bin/sh

# before staring this script, you should start the following two commands:

# (1) sh ./SCADAtestbed1-main.sh /dev/TTY_name MOKA1
# ex: sh ./SCADAtestbed1-main.sh /dev/cu.usbmodem-14101 MOKA1

# (2) sh ./SCADAtestbed1-main.sh /dev/TTY_name MOKA2
# ex: sh ./SCADAtestbed1-main.sh /dev/cu.usbmodem-14201 MOKA2


./Darshana-Ch0F1.sh &
./Darshana-Ch0F2.sh &
./Darshana-Ch0F3.sh &

./Darshana-Ch1F1.sh &
./Darshana-Ch1F2.sh &
./Darshana-Ch1F3.sh &

./Darshana-Ch2F1.sh &
./Darshana-Ch2F2.sh &
./Darshana-Ch2F3.sh &

./Darshana-Ch3F2.sh &
./Darshana-Ch3F3.sh &

./Darshana-Ch4F2.sh &
./Darshana-Ch4F3.sh &
