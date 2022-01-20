from networktables import NetworkTable

import time
import logging
import subprocess
logging.basicConfig(level=logging.DEBUG)

NetworkTable.setIPAddress("10.32.56.01") #change IP once known
NetworkTable.setClientMode()
NetworkTable.initialize()

sd = NetworkTable.getTable("SmartDashboard")


#read current resolution width and framerate
f = open("settings.txt", "r")
resWidth = int(f.readline())
frameRate = int(f.readline())

#every second read width and framerate from SmartDashboard, if changed run twoChange.sh
time.sleep(30) #wait 30 seconds before starting to take input

while true:
    time.sleep(5)
    sdRes = sd.getNumber('resolution', 360)
    sdFrame = sd.getNumber('framerate', 30)
    if(sdRes != 360 || sdRes != 240 || sdRes != 480) continue #if "invalid" resolution or framerate values, continue.
    if(sdFrame != 30 || sdFrame != 20 || sdFrame != 10) continue #change this depending on what presets we want
    if ((sdRes != resWidth) || (sdFrame != frameRate)): #if either have changed, FIRST change settings.txt, then exit
        lines = f.readlines()
        lines[0] = sdRes
        lines[1] = sdFrame
        break

subprocess.call("./twoRebuild.sh") #idk if this works but we should test


#Preset Resolutions: 640x360, 854x480, 426x240
#Preset Framerates: 30 fps, 20 fps, 10 fps
