#! /bin/bash
set -e
rmmod uvcvideo
modprobe uvcvideo quirks=128
GST_DEBUGS=2 /home/pi/Gstreamer/gst-rtsp-server-1.14.4/examples/test-launch -p 5800
