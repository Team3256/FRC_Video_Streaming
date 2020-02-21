# Background

Currently our camera stream uses RTSP, the real time streaming protocol, which is fast and low latency, however, there are still issues, especially with multiple camera streams running at the same time. It is often inconsistent if others are using the network at the same time.

# SRT (Secure Reliable Transport)
**Benefits:** Compared to RTSP, more reliable, more secure, and less latency, especially with congested networks (ie multiple cameras using the same network)
**Drawbacks:** Still experimental, for ex. the newest version of Raspbian does not natively contain the latest version of Gstreamer which supports SRT

# How to Install
Must have the latest version of Gstreamer installed. Most Linux distros atm only include v1.14, which does not include srt. v1.16 does, which must be built from source (or use a different os)

Also need to install the srt SDK: https://github.com/Haivision/srt

# How to Use in Gstreamer
**Commands:** https://www.collabora.com/news-and-blog/blog/2018/02/16/srt-in-gstreamer/
Sender: `gst-launch-1.0 videotestsrc ! video/x-raw, height=1080, width=1920 ! videoconvert ! x264enc tune=zerolatency ! video/x-h264, profile=high ! mpegtsmux ! srtsink uri=srt://:8888/`

Receiver: `gst-launch-1.0 srtsrc uri=srt://10.78.49.32:8888 ! decodebin ! autovideosink`

Replace videotestsrc with your video source (most likely will be v4l2src if using a USB webcam on Linux)
Adjust height, width to match video specifications
If doesn’t work, try removing some of the elements
Make sure firewall ports open

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

# Conclusion
SRT is still experimental, especially for the Raspberry Pi. But I have tried using it from Mac to Linux using the videotestsrc, and it appears to be working correctly. 