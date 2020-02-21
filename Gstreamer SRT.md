# Background

Currently our camera stream uses RTSP (Real Time Streaming Protocol), which is fast, well-documented, and low latency, however, there are still issues, especially when multiple camera streams run at the same time. 

# SRT (Secure Reliable Transport)
**Benefits:** Compared to RTSP, more reliable, more secure, and less latency, especially with congested networks (ie multiple cameras using the same network)

**Drawbacks:** Still experimental, for ex. the newest version of Raspbian does not natively contain the latest version of Gstreamer which supports SRT, and not as well documented

# How to Install
Must have the latest version of Gstreamer installed (1.16+). Most Linux distros atm only include v1.14, which does not include srt. To get the latest version of Gstreamer, you either need to upgrade to a newer Linux distribution (recommended) or build from source.

Also need to install the srt SDK: https://github.com/Haivision/srt

# How to Use in Gstreamer
**Commands:** https://www.collabora.com/news-and-blog/blog/2018/02/16/srt-in-gstreamer/

What will most likely happen the first time you try to run these commands is that it will not find srtsink or srtsrc. When installing Gstreamer, many plugins are not included by default. SRT is part of the gst-plugins-bad package, and, depending on your OS, most likely needs to be manually installed in addition to the Gstreamer base package.

For example, on Debian Linux based systems, you need to run the following command to get all of the packages:

'sudo apt-get install libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio'

On macOS, it is recommended that you use Homebrew, a third-party package manager to install Gstreamer:

**How to Install Homebrew:** '/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"'

**How to Install Gstreamer on Homebrew:** 'brew install gstreamer gst-plugins-base gst-plugins-good gst-plugins-bad gst-plugins-ugly gst-libav' 

Sender: `gst-launch-1.0 videotestsrc ! video/x-raw, height=1080, width=1920 ! videoconvert ! x264enc tune=zerolatency ! video/x-h264, profile=high ! mpegtsmux ! srtsink uri=srt://:8888/` (This is what is run on the Raspberry Pi)

* Replace videotestsrc with the video source that you want to receive from. For most USB webcams on Linux, you will be using v4l2src.
* Adjust the height and width to match the video specifications that you want. This command uses 1080p, which is high resolution, but takes more of a toll on the network / decoding performance.
* Make sure that you keep your firewall ports open.

Receiver: `gst-launch-1.0 srtsrc uri=srt://10.78.49.32:8888 ! decodebin ! autovideosink` (This is what is run on your viewer computer).

* If it doesn't work, try: Removing / adjusting some of the elements, updating Gstreamer, checking your network connection, & checking your port / IP address.

## NOTE: This method uses Gstreamer for **both** sender and receiver. However, you do not need to use Gstreamer to send, especially if you are testing.

# How to use gst-live-transmit
If you installed SRT using the GitHub link above, it also installed gst-live-transmit, which is a simplified version of the Gstreamer sender command.

How it works is that it takes in a UDP stream and spits out a SRT stream. For example, let's say you don't want to use videotestsrc, so you create a ffmpeg udp stream to display bars:

`ffmpeg -f lavfi -re -i smptebars=duration=300:size=1280x720:rate=30 -f lavfi -re -i sine=frequency=1000:duration=60:sample_rate=44100 -pix_fmt yuv420p -c:v libx264 -b:v 1000k -g 30 -keyint_min 120 -profile:v baseline -preset veryfast -f mpegts "udp://127.0.0.1:1234?pkt_size=1316"`

This command creates a 720p UDP stream with lines, bars, and a sound (although sound isn't used for our purposes) on the UDP port 1234.

Here is the syntax for the srt-live-transmit function:

`srt-live-transmit udp://:1234 srt://:4201 -v`

Notice that it is listening to the UDP port 1234, and transmitting on the SRT port 4201. The -v represents that it is in verbose mode, so it will display extra debug info.

You can use VLC or Gstreamer to pull up the srt stream, just as if you were using Gstreamer.

For more information about gst-live-transmit: https://github.com/Haivision/srt/blob/master/docs/srt-live-transmit.md

