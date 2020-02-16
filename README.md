# FRC Video Streaming

**This is the live video streaming project based on Gstreamer and OpenCV. We connect our webcams to different raspberry pi 4 and raspberry pi will send the streaming video to the Windows cilent.**

GStreamer is a pipeline-based multimedia framework and software that links together a wide variety of media processing systems to complete complex workflows. It contains enormous useful commends to decode, encode, and transport your live video. 

[Gstreamer Introduction](https://gstreamer.freedesktop.org/)

For OpenCV, it is a library of programming functions mainly aimed at real-time computer vision. We will use OpenCV to integrate different pipelines from different raspberry pi.

[OpenCV Official Website](https://opencv.org/)
  
## Our Goals:

* 480P and 30 FPS live streaming from **Three** different raspberry pi
* Low latency
* Sustainability
* Recording streaming video (Optional)

## Setup

### Raspbian System

Before starting setup, we need to write raspbian system into raspberry pi MicroSD card.
[Raspbian System Installation](https://www.raspberrypi.org/documentation/installation/installing-images/)

### Gstreamer Installation & Configuration

#### Windows

[Gstreamer Installation (Windows)](https://gstreamer.freedesktop.org/documentation/installing/on-windows.html?gi-language=c)

#### Linux (Raspbian)

We need to add Gstreamer's PPA (Personal Package Archive) before we download every packages and plugins:

    `sudo add-apt-repository ppa:gstreamer-developers/ppa`

After that, type:

    `apt-get install libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio`
    
 

