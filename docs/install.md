
## Setup

### 1. Install Raspbian
[Raspbian System Installation](https://www.raspberrypi.org/documentation/installation/installing-images/)

### 2. Install and Configure GStreamer (on both server and client)

#### Windows

Install the 2015, 2017, and 2019 Visual C++ runtimes: [Download Visual C++ Runtime Libraries -- BOTH x64 and x86 but not ARM64](https://support.microsoft.com/en-us/topic/the-latest-supported-visual-c-downloads-2647da03-1eea-4433-9aff-95f26a218cc0)

Install Chocolatey (https://community.chocolatey.org/courses/installation/installing?method=installing-chocolatey) *Select basic Chocolatey install*. After it's installed, type:

    choco install gstreamer

Follow the instructions to refresh your environment variables. Type gst-launch-1.0 --version. If you see a version number listed, it works!

#### macOS
You can install GStreamer using Homebrew.

#### Linux (Raspbian) - assuming a brand new installation
1. Change your default user password. Type passwd, and follow the prompts to change your password, then reboot.

2. Next, enable SSH (or VNC if using regular Raspbian) so you can access the pi from another system using a program like PuTTY. Type sudo raspi-config, and go to Interfacing Options, and enable SSH and/or VNC. Then, go to the network settings and input the WiFi network name you want to connect to.

Run ifconfig to check your IP address, and you can use PuTTY to connect to it via SSH or RealVNC to connect using VNC.

We need to make sure the version of Raspbian is completely up to date. Run:

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

    gst-launch-1.0 tcpclientsrc host=((SAME IP AS YOUR RASBERRY PI)) port=5000 ! decodebin ! autovideosink

If you see the test tones on your PC, that means that the videotestsrc is successfully being streamed from the Raspberry Pi to your Windows PC!

Now, insert your camera into the USB port, and then run the following command on your Pi:

    gst-launch-1.0 v4l2src device=/dev/video0 ! video/x-raw,width=640,height=480,framerate=30/1 ! videoconvert ! x264enc tune=zerolatency ! video/x-h264,profile=high ! mpegtsmux ! tcpserversink host=((INSERT YOUR IP ADDRESS HERE)) port=5000

And on your PC, run:

    gst-launch-1.0 tcpclientsrc host=((INSERT YOUR IP ADDRESS HERE)) port=5000 ! decodebin ! autovideosink

There will be some delay since it's are streaming over TCP, but it's good enough if you can see what your camera sees.
