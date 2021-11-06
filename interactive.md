One of our next goals was to make the Gstreamer instance interactive based on the input from our SmartDashboard. While the default resolution and framerate is 640x360 at 30fps, there may be instances where we may want to lower or raise the resolution and framerate due to network conditions during a match. 

# Framework:
We will create a new systemd service that continuously checks the SmartDashboard variable for resolution (width) and framerate to detect if they have changed. If they have, we run one of our preset scripts to change the resolution and framerate through copying the test-launch.c file, rebuilding gstreamer, and rebooting the pi.

# Files:
**checkinput.py -->** python script that will continuously check the SmartDashboard variables

**rebuildreboot.sh -->** bash script that will be called upon AFTER the test-launch.c file is changed to rebuild gstreamer and reboot the pi

**presets folder -->** folder that contains different scripts and test-launch.c files to change the resolution and framerate based on the inputs
