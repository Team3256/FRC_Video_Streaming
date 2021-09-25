#! /bin/bash
set -e # Exit if any of the commands below error

# Reload the uvcvideo driver with a specific quirks option
# quirks=128 enables a fix for fixing bandwidth issues with the type of cameras we use.
# Basically, it allows us to use multiple cameras on the same usb port.
rmmod uvcvideo
modprobe uvcvideo quirks=128

# Run the test-launch script with gstreamer debugging turned on
GST_DEBUGS=2 /home/pi/gst-rtsp-server-1.14.4/examples/test-launch -p 5800
