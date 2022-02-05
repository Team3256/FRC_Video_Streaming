from networktables import NetworkTable

import time
import logging
import subprocess
import threading
logging.basicConfig(level=logging.DEBUG)


# NetworkTable.setIPAddress("10.32.56.01") #change IP once known
# NetworkTable.setClientMode()
# NetworkTable.initialize()

# sd = NetworkTable.getTable("SmartDashboard")


# need to test to make sure it works

cond = threading.Condition()
notified = [False]

def connectionListener(connected, info):
    print(info, '; Connected=%s' % connected)
    with cond:
        notified[0] = True
        cond.notify()

NetworkTables.initialize(server='10.32.56.0') #change ip once known
NetworkTables.addConnectionListener(connectionListener, immediateNotify=True)

with cond:
    print("Waiting")
    if not notified[0]:
        cond.wait()

# connected
sd = NetworkTablesInstance.getTable('SmartDashboard')



#every second read width and framerate from SmartDashboard, if changed run twoChange.sh
time.sleep(15) #wait 30 seconds before starting to take input

while True:
    time.sleep(15)
    #read current resolution width and framerate
    f = open("settings.txt", "r+")
    lines = f.readlines()
    f.seek(0)

    # read smart dashboard values
    sdRes = sd.getNumber('resolution', 360)
    sdFrame = sd.getNumber('framerate', 30)

    if(sdRes != 360 and sdRes != 240 and sdRes != 480): continue #if "invalid" resolution or framerate values, continue.
    if(sdFrame != 30 and sdFrame != 20 and sdFrame != 10): continue #change this depending on what presets we want


    if (sdRes != int(lines[0])) or (sdFrame != int(lines[1])): #if either have changed, FIRST change settings.txt, then exit
        lines[0] = str(sdRes)
        lines[1] = str(sdFrame)
        merge = "\n".join(lines)
        f.truncate()
        f.write(merge)
        f.close()
        subprocess.call("sudo ./twoRestart.sh")


#Preset Resolutions: 640x360, 854x480, 426x240
#Preset Framerates: 30 fps, 20 fps, 10 fps
_
