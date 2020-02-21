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
Sender: gst-launch-1.0 -v videotestsrc ! video/x-raw, height=1080, width=1920
! videoconvert ! x264enc tune=zerolatency ! video/x-h264, profile=high
! mpegtsmux ! srtsink uri=srt://:8888/

Receiver: gst-launch-1.0 srtsrc uri=srt://192.168.1.55:8888 ! decodebin !
autovideosink

Replace videotestsrc with your video source (most likely will be v4l2src if using a USB webcam on Linux)
Adjust height, width to match video specifications
If doesn’t work, try removing some of the elements
Make sure firewall ports open

# Conclusion
SRT is still experimental, especially for the Raspberry Pi. But I have tried using it from Mac to Linux using the videotestsrc, and it appears to be working correctly. 