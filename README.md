# FRC Video Streaming

**This is the live video streaming project based on Gstreamer and OpenCV. We connect our webcams to different raspberry pi 4 and raspberry pi will send the streaming video to the Windows cilent.**

GStreamer is a pipeline-based multimedia framework and software that links together a wide variety of media processing systems to complete complex workflows. It contains enormous useful commends to decode, encode, and transport your live video. 
  
For OpenCV, it is a library of programming functions mainly aimed at real-time computer vision. We will use OpenCV to integrate different pipelines from different raspberry pi.
  
## Our Goals:

* 480P and 30 FPS live streaming from **Three** different raspberry pi
* Low latency
* Sustainability
* Recording streaming video (Optional)

## Setup

Before starting setup, we need to write raspbian system into raspberry pi MicroSD card.
[Raspbian System Installation](https://www.raspberrypi.org/documentation/installation/installing-images/)

### Gstreamer Installation & Configuration
#### Windows
[Gstreamer Installation (Windows)](https://gstreamer.freedesktop.org/documentation/installing/on-windows.html?gi-language=c)
#### Linux (Raspbian)

