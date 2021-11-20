#! /bin/bash

killall -9 gst-launch-1.0
killall -9 test-launch

#reconfigure and rebuild gstreamer
cd /home/pi/gst-rtsp-server-1.14.4/
./configure
make
reboot
