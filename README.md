# FRC Video Streaming

**This is the live video streaming project based on Gstreamer. We connect our webcams to different Raspberry Pi 4's and they will send the streaming video to the Windows cilent.**

Some useful links:
* [Guide to H264 Streaming in FRC](https://rianadon.github.io/blog/2019/04/04/guide-to-h264-streaming-frc.html)
* [OpenCV and Gstreamer (C++)](https://github.com/tik0/mat2gstreamer)
* [Shared memory](https://github.com/tik0/mat2gstreamer)

GStreamer is a pipeline-based multimedia framework and software that links together a wide variety of media processing systems to complete complex workflows. It contains enormous useful commends to decode, encode, and transport your live video. 

[Gstreamer Introduction](https://gstreamer.freedesktop.org/)

For OpenCV, it is a library of programming functions mainly aimed at real-time computer vision. We will use OpenCV to integrate different pipelines from different raspberry pi.

[OpenCV Official Website](https://opencv.org/)
  
## Our Goals

* 480p and 30 FPS live streaming from one Raspberry Pi
* Low latency
* Sustainability

## Some information about the hardware

* 1 Raspberry Pi 4 [Raspberry Pi 4](https://www.amazon.com/Raspberry-Model-2019-Quad-Bluetooth/dp/B07TD42S27/ref=sr_1_3?crid=314J4PUEPI6ZV&keywords=raspberry+pi+4&qid=1581813926&s=electronics&sprefix=rasp%2Celectronics%2C194&sr=1-3)
* 2 Logitech C920 webcam (It supports 1080P, 30 FPS maximum) [Newer Model: C922x Pro](https://www.amazon.com/Logitech-C922x-Pro-Stream-Webcam/dp/B01LXCDPPK/ref=sr_1_1_sspa?keywords=c920s&qid=1581813651&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUFGNzg5VTNRR09PT1omZW5jcnlwdGVkSWQ9QTA1OTcyOTQySTQ2OVJGTVg1UEdEJmVuY3J5cHRlZEFkSWQ9QTA4MTQxOTIxTEMzNk1LUUY3U0U0JndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==)
* 1 Micro-SD card to install Raspbian or Ubuntu Server [Recommendation: Samsung 64GB Version](https://www.amazon.com/dp/B06XX29S9Q?aaxitk=cbwfyKhuwZuc09zBCGigew&pd_rd_i=B06XX29S9Q&pf_rd_p=591760d1-6468-480f-9b10-0ee9c85706fd&hsa_cr_id=4976542660401&sb-ci-n=asinImage&sb-ci-v=https%3A%2F%2Fm.media-amazon.com%2Fimages%2FI%2F81rpcHc0XzL.jpg&sb-ci-a=B06XX29S9Q)

## Guides:
- Installing and Setting Up GStreamer [InstallSetup.md](https://github.com/Team3256/FRC_Video_Streaming_2020/blob/master/InstallSetup.md)

##### Installing RTSP

What is RTSP? [RTSP, Wikipedia](https://en.wikipedia.org/wiki/Real_Time_Streaming_Protocol)

Download and configure the RTSP Server
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

