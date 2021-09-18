
## Setup

### Raspbian System

Before starting setup, we need to write Raspbian system into raspberry pi MicroSD card. It is recommended to install Raspbian Lite to reduce the resource usage that is taken up by the normal Raspbian desktop. The easiest way to do this is by using the Raspberry Pi Imager.
[Raspbian System Installation](https://www.raspberrypi.org/documentation/installation/installing-images/)

### Gstreamer Installation & Configuration

#### Windows

[Gstreamer Installation (Windows)](https://gstreamer.freedesktop.org/documentation/installing/on-windows.html?gi-language=c)

Make sure that the 2015, 2017, and 2019 Visual C++ runtimes are installed PRIOR to installation! [Download Visual C++ Runtime Libraries](https://support.microsoft.com/en-us/topic/the-latest-supported-visual-c-downloads-2647da03-1eea-4433-9aff-95f26a218cc0)

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
