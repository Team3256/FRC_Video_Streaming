## Setup
This guides you through setting up the pi for GStreamer and installing GStreamer on your viewer PC.

### 1. Install Raspbian
[Raspbian System Installation](https://www.raspberrypi.org/documentation/installation/installing-images/)

IMPORTANT: If using the GUI version, make sure that it is configured to run headless or else it won't boot correctly w/out a display attached ([HDMI hotplug](https://www.shellhacks.com/raspberry-pi-force-hdmi-hotplug/)).

### 2. Install and Configure GStreamer (on both server and client)

#### Windows

Install the 2015, 2017, and 2019 Visual C++ runtimes: [Download Visual C++ Runtime Libraries -- BOTH x64 and x86 but not ARM64](https://support.microsoft.com/en-us/topic/the-latest-supported-visual-c-downloads-2647da03-1eea-4433-9aff-95f26a218cc0)

Install Chocolatey (https://community.chocolatey.org/courses/installation/installing?method=installing-chocolatey) *Select basic Chocolatey install*. After it's installed, type:

    choco install gstreamer

Follow the instructions to refresh your environment variables. Type gst-launch-1.0 --version. If you see a version number listed, it works!

#### macOS
You can install GStreamer using Homebrew similarly to Chocolatey.

#### Linux (Raspbian) - assuming a brand new installation
1. Change your default user password. (IF LITE) Type passwd, and follow the prompts to change your password, then reboot. If

2. Next, enable SSH (or VNC if using Raspbian w/ GUI) so you can access the pi w/out a display using PuTTY or RealVNC. Type sudo raspi-config, and go to Interfacing Options, and enable SSH and/or VNC. Then, go to the network settings and input the WiFi network name you want to connect to.

IMPORTANT: For initial setup, it's recommended to create your own WiFi hotspot to connect to the pi to. It cannot connect to the main VCS network, and using VCS Guest can be cumbersome since it forces you to log in every so often. Once you have finished setting up, you should disable the hotspot and connect the pi to the robot's WiFi.

Run ifconfig to check your IP address, and you can use PuTTY to connect to it via SSH or RealVNC to connect using VNC. If you're on Windows, you can also use [Angry IP Scanner](https://angryip.org) to scan for specific open ports (such as 22 for SSH).

Update Raspbian:

     sudo apt update

     sudo apt full-upgrade

After that, type:

     sudo apt install libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-pulseaudio libgstreamer-plugins-base1.0-dev libglib2.0-dev

Use

     gst-inspect-1.0 --version

to check the GStreamer version.

GStreamer is now installed!

## Testing
To verify that Gstreamer is working, type:
    gst-launch-1.0 videotestsrc ! videoconvert ! autovideosink
If you see some test tones, it works!

Next, you should test streaming the videotestsrc over the network. On your pi, type:

    gst-launch-1.0 videotestsrc ! video/x-raw, height=480,width=640 ! videoconvert ! x264enc tune=zerolatency ! video/x-h264,profile=high ! mpegtsmux ! tcpserversink host=((INSERT YOUR IP ADDRESS HERE)) port=5000

On your viewer PC type:

    gst-launch-1.0 tcpclientsrc host=((SAME IP AS YOUR PI)) port=5000 ! decodebin ! autovideosink

If you see the test tones on your PC, that means that the videotestsrc is successfully being streamed from the Raspberry Pi to your Windows PC!

Now, insert your camera into the USB port, and then run the following command on your Pi:

    gst-launch-1.0 v4l2src device=/dev/video0 ! video/x-raw,width=640,height=480,framerate=30/1 ! videoconvert ! x264enc tune=zerolatency ! video/x-h264,profile=high ! mpegtsmux ! tcpserversink host=((INSERT YOUR IP ADDRESS HERE)) port=5000

You may need to change the number next to video (video0, video1, video2) until you get the correct number for the camera.

And on your PC, run:

    gst-launch-1.0 tcpclientsrc host=((INSERT YOUR IP ADDRESS HERE)) port=5000 ! decodebin ! autovideosink

There will be some delay since it's streaming over TCP, which is why we are using RTSP.
