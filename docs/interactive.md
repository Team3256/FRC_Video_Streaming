GOAL: Make the Gstreamer settings (notably resolution and framerate) interactive through the SmartDashboard. While the default settings are 640x360 at 30fps, there may be instances where we may want to lower or raise the resolution and framerate due to varying network conditions during a match.

# Framework:
We will create a new systemd service that calls a Python script which continuously checks the SmartDashboard variable for resolution (width) and framerate to detect if they have changed. If they have, the Python script will call upon a bash script to change the resolution and framerate in the test-launch.c file. The script will then rebuild gstreamer, and reboot the pi. This whole process should take 1-2 minutes; it's not meant to be done in game but can be changed between games if there are any network changes that might necesitate it.

# Files:
**oneCheck.py -->** python script that will continuously check the SmartDashboard variables. edits the settings.txt file if parameters have changed.

**twoRebuild.sh -->** rebuilds gstreamer and reboots the pi
