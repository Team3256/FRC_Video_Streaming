GOAL: Make the Gstreamer settings (notably resolution and framerate) interactive through the SmartDashboard. While the default settings are 640x360 at 30fps, there may be instances where we may want to lower or raise the resolution and framerate due to varying network conditions during a match.

# Framework:
We will create a new systemd service that calls a Python script which continuously checks the SmartDashboard variable for resolution (width) and framerate to detect if they have changed.

 The script will then restart gstreamer.

# Files (leave all of these EXCEPT for interactive.service in /home/pi/interactive)
**oneCheck.py -->** python script that will continuously check the SmartDashboard variables. edits the settings.txt file if parameters have changed.

**twoRestart.sh -->** restarts gstreamer process with new config data

**settings.txt -->** stores the current resolution and framerate of the cameras on the pi

**startinteractive.sh -->** starts oneCheck.py on pi boot

**interactive.service -->** place this in the same systemd services folder as streaming.service (see Systemd.md)

# Steps:
Make sure you install pip and then pynetworktables!

pip install pynetworktables

Make sure to also make the .sh files executable using chmod
