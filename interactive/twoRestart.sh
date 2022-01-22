#! /bin/bash

killall -9 startstreaming
killall -9 gst-launch-1.0
killall -9 test-launch


#reboot gstreamer
cd /home/pi/
./startstreaming.sh
#make
#reboot
