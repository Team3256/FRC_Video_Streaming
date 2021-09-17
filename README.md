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

* 480P and 30 FPS live streaming from **Three** (this can change in the future) different raspberry pi
* Low latency
* Sustainability

## Some information about the hardware

* 3 raspberry pi 4 [Raspberry Pi 4](https://www.amazon.com/Raspberry-Model-2019-Quad-Bluetooth/dp/B07TD42S27/ref=sr_1_3?crid=314J4PUEPI6ZV&keywords=raspberry+pi+4&qid=1581813926&s=electronics&sprefix=rasp%2Celectronics%2C194&sr=1-3)
* 3 Logitech C920 webcam (It supports 1080P, 30 FPS maximum) [Newer Model: C922x Pro](https://www.amazon.com/Logitech-C922x-Pro-Stream-Webcam/dp/B01LXCDPPK/ref=sr_1_1_sspa?keywords=c920s&qid=1581813651&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUFGNzg5VTNRR09PT1omZW5jcnlwdGVkSWQ9QTA1OTcyOTQySTQ2OVJGTVg1UEdEJmVuY3J5cHRlZEFkSWQ9QTA4MTQxOTIxTEMzNk1LUUY3U0U0JndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==)
* 3 Micro-SD cards to install Raspbian [Recommendation: Samsung 64GB Version](https://www.amazon.com/dp/B06XX29S9Q?aaxitk=cbwfyKhuwZuc09zBCGigew&pd_rd_i=B06XX29S9Q&pf_rd_p=591760d1-6468-480f-9b10-0ee9c85706fd&hsa_cr_id=4976542660401&sb-ci-n=asinImage&sb-ci-v=https%3A%2F%2Fm.media-amazon.com%2Fimages%2FI%2F81rpcHc0XzL.jpg&sb-ci-a=B06XX29S9Q)

## Setup

### Raspbian System

Before starting setup, we need to write Raspbian system into raspberry pi MicroSD card. It is recommended to install Raspbian Lite to reduce the resource usage that is taken up by the normal Raspbian desktop. The easiest way to do this is by using the Raspberry Pi Imager.
[Raspbian System Installation](https://www.raspberrypi.org/documentation/installation/installing-images/)

### Gstreamer Installation & Configuration

#### Windows

[Gstreamer Installation (Windows)](https://gstreamer.freedesktop.org/documentation/installing/on-windows.html?gi-language=c)

Make sure that the 2015, 2017, and 2019 Visual C++ runtimes are installed PRIOR to installation!  https://support.microsoft.com/en-us/topic/the-latest-supported-visual-c-downloads-2647da03-1eea-4433-9aff-95f26a218cc0\

The best way I have found so far is to use Chocolatey, which works similar to a package manager on Linux. Use this guide (https://community.chocolatey.org/courses/installation/installing?method=installing-chocolatey) *Select basic Chocolatey install* to install Chocolatey using cmd.exe, and then type:

    choco install gstreamer
    
After it's done, reboot your system. You should be able to type both gst-launch-1.0 and gst-inspect-1.0 into cmd and they should both work.

#### macOS
Even though macOS isn't a priority, you can install Gstreamer using Homebrew.

#### Linux (Raspbian)

This guide assumes you have just installed Raspbian Lite. First, change your default user password. Type passwd, and follow the prompts to change your password, then reboot.

Next, enable SSH so you can access the pi from another system using a program like PuTTY. Type sudo raspi-config, and go to Interfacing Options, and enable SSH. Then, go to the network settings and input the WiFi network name you want to connect to:

NOTE: If you have an ethernet cable plugged into the Pi (like for your FRC router), it will automatically default to it, EVEN if you have specified a working WiFi network. Make sure to disconnect it if you want to connect to the internet. The Pi can NOT connect to the main VCS network due to it not supporting the username/password login method, and will struggle to connect to VCS Guest because it has a captive page. The best method for installing the packages you need is to have another computer as a hotspot connected to the VCS network that can output a new WiFi network. You can also edit the wpa_supplicant file if you have multiple WiFi networks that you need to adjust the priority of (use nano to accomplish this: https://raspberrypi.stackexchange.com/questions/58304/how-to-set-wifi-network-priority)

Run the ifconfig command to check the IP address of your Pi, and you can use PuTTY to connect to it via SSH.

We need to make sure the version of Raspbian is completely up to date. Run:

     sudo apt update

     sudo apt full-upgrade

After that, type:

     sudo apt install libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-pulseaudio libgstreamer-plugins-base1.0-dev libglib2.0-dev

Use 

     gst-inspect-1.0 --version

To check the GStreamer version.

GStreamer is now installed! You can now start doing streams, but only over TCP, which isn't an efficient live streaming transportation method. RTSP is an efficient video streaming protocol that we are currently using to transport the video over the network.


##### Installing RTSP

What is RTSP? [RTSP, Wikipedia](https://en.wikipedia.org/wiki/Real_Time_Streaming_Protocol)

Download and configure the RTSP Server
1. Go to (https://gstreamer.freedesktop.org/src/gst-rtsp-server/), select the Gstreamer version you are using. Copy the URL (it should end in .tar.xz). Use the wget command to download it into your home folder.
2. Extract the file using tar -xz FILENAME.tar.xz.
3. In terminal, go to the folder you have extracted (use "cd" command)
4. Type ./configure
5. Once you are finished, type make

## Testing
A lot of this is based upon the guide from the first link above, so you can read that while you are reading through this.

First, you can do a basic test on your Windows system to verify that Gstreamer is working. Type
    gst-launch-1.0 videotestsrc ! videoconvert ! autovideosink
If you see some test tones, it works!

Next, you should test streaming the videotestsrc over the network. On your pi, type:

    gst-launch-1.0 videotestsrc ! video/x-raw, height=480,width=640 ! videoconvert ! x264enc tune=zerolatency ! video/x-h264,profile=high ! mpegtsmux ! tcpserversink host=((INSERT YOUR IP ADDRESS HERE)) port=5000
    
On your viewer PC type:

    gst-launch-1.0 tcpclientsrc host=((SAME IP AS YOUR RASBERRY PI)) port=5000 ! decodebin ! autovideosink

If you see the test tones on your PC, that means that the videotestsrc is successfully being streamed from the Raspberry Pi to your Windows PC!

Now, the ultimate test: outputting your camera feed over the network. Insert your camera into the USB port, and then run the below command on your Pi:

    gst-launch-1.0 v4l2src device=/dev/video0 ! video/x-raw,width=640,height=480,framerate=30/1 ! videoconvert ! x264enc tune=zerolatency ! video/x-h264,profile=high ! mpegtsmux ! tcpserversink host=((INSERT YOUR IP ADDRESS HERE)) port=5000
    
And on your PC, run:

    gst-launch-1.0 tcpclientsrc host=((INSERT YOUR IP ADDRESS HERE)) port=5000 ! decodebin ! autovideosink
    
If you see what your camera sees, it works! It is expected that there will be some delay since we are streaming over TCP, but if you can see your stream it is considered successful.

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

