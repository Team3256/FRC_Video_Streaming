##### Installing RTSP

What is RTSP? [RTSP, Wikipedia](https://en.wikipedia.org/wiki/Real_Time_Streaming_Protocol)

Download and configure the RTSP Server (you can also use the gst-rtsp-server-1.14.4 folder located in this repo)
1. Go to (https://gstreamer.freedesktop.org/src/gst-rtsp-server/), select the Gstreamer version you are using. Copy the URL (it should end in .tar.xz). Use the wget command to download it into your home folder.
2. Extract the file using tar -xz FILENAME.tar.xz.
3. In terminal, go to the folder you have extracted (use "cd" command)
4. Type ./configure
5. Once you are finished, type make


### Adding RTSP
Next, we can try streaming over RTSP. Navigate (cd) over to the gst-rtsp-server-1.14.4/examples folder. In it should be a test-launch executable. On your Pi, run this command:

    ./test-launch -p 5800 "( v4l2src device=/dev/video0 ! video/x-raw,width=640,height=480,framerate=30/1 ! queue ! videoconvert ! video/x-raw,format=I420 ! x264enc tune=zerolatency bitrate=1000 ! rtph264pay config-interval=1 name=pay0 pt=96 )"

And on your PC, run this:

    gst-launch-1.0 rtspsrc location=rtsp://(YOUR PI's IP ADDRESS):5800/test latency=0 ! rtph264depay ! decodebin ! autovideosink

If you see your camera stream on your PC it works! It should be smooth and have very little latency.

#### Checking temperature
An important point before you start adding more cameras is to check the temperature of your pi. You can use the following command to check its temperature:

    /opt/vc/bin/vcgencmd measure_temp | awk -F "[=\']" '{print($2)}'

In order to be able to execute this command while test-launch is running, add  & to the end of the test-launch command. To quit it, type ps, see what the process ID is, and then run kill (PROCESS ID). 

### Modifiying the test-launch.c file
To use more than one camera, we need to modify the test-launch.c file. Download the test-launch.c file from this GitHub repo and replace the default test-launch.c file with the new file. Then recompile using the same steps from above. To run it, type

    ./test-launch -p 5800

What this modified test-launch.c file does is create two separate streams, both on port 5800. You can use the same command from the Adding RTSP section above, but you can replace the test with either front or top. For more info about how this modified file works, look at the Guide to H.264 Streaming on the main readme.md under the 'Some fries on the side' section.

You can access the streams on your viewer computer by opening up two cmd windows and typing in:

    gst-launch-1.0 rtspsrc location=rtsp://(YOUR PI's IP ADDRESS):5800/front latency=0 ! rtph264depay ! decodebin ! autovideosink

and

    gst-launch-1.0 rtspsrc location=rtsp://(YOUR PI's IP ADDRESS):5800/top latency=0 ! rtph264depay ! decodebin ! autovideosink
