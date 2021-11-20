from networktables import NetworkTable

import time
import logging
logging.basicConfig(level=logging.DEBUG)

NetworkTable.setIPAddress("10.32.56.01") #change IP once known
NetworkTable.setClientMode()
NetworkTable.initialize()

sd = NetworkTable.getTable("SmartDashboard")

#read current resolution width and framerate
resWidth = 
frameRate =

#every second read width and framerate from SmartDashboard, if changed run bash script to switch test-launch.c with a new preset


#Presets: 640x360, 854x480, 426x240
#Framerates: 30 fps, 20 fps, 10 fps
