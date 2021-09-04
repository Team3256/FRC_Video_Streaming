# FRC Video Streaming

**This is the live video streaming project based on Gstreamer and OpenCV. We connect our webcams to different raspberry pi 4 and raspberry pi will send the streaming video to the Windows cilent.**

Some useful links:
* [Guide to H264 Streaming in FRC](https://rianadon.github.io/blog/2019/04/04/guide-to-h264-streaming-frc.html)
* [OpenCV and Gstreamer (C++)](https://github.com/tik0/mat2gstreamer)
* [Shared memory](https://github.com/tik0/mat2gstreamer)

GStreamer is a pipeline-based multimedia framework and software that links together a wide variety of media processing systems to complete complex workflows. It contains enormous useful commends to decode, encode, and transport your live video. 

[Gstreamer Introduction](https://gstreamer.freedesktop.org/)

For OpenCV, it is a library of programming functions mainly aimed at real-time computer vision. We will use OpenCV to integrate different pipelines from different raspberry pi.

[OpenCV Official Website](https://opencv.org/)
  
## Our Goals

* 480P and 30 FPS live streaming from **Three** different raspberry pi
* Low latency
* Sustainability
* Recording streaming video (Optional)

## Some information about the hardware

* 3 raspberry pi 4 [Raspberry Pi 4](https://www.amazon.com/Raspberry-Model-2019-Quad-Bluetooth/dp/B07TD42S27/ref=sr_1_3?crid=314J4PUEPI6ZV&keywords=raspberry+pi+4&qid=1581813926&s=electronics&sprefix=rasp%2Celectronics%2C194&sr=1-3)
* 3 Logitech C920 webcam (It supports 1080P, 30 FPS maximum) [Newer Model: C922x Pro](https://www.amazon.com/Logitech-C922x-Pro-Stream-Webcam/dp/B01LXCDPPK/ref=sr_1_1_sspa?keywords=c920s&qid=1581813651&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUFGNzg5VTNRR09PT1omZW5jcnlwdGVkSWQ9QTA1OTcyOTQySTQ2OVJGTVg1UEdEJmVuY3J5cHRlZEFkSWQ9QTA4MTQxOTIxTEMzNk1LUUY3U0U0JndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==)
* 3 Micro-SD cards to install Raspbian [Recommendation: Samsung 64GB Version](https://www.amazon.com/dp/B06XX29S9Q?aaxitk=cbwfyKhuwZuc09zBCGigew&pd_rd_i=B06XX29S9Q&pf_rd_p=591760d1-6468-480f-9b10-0ee9c85706fd&hsa_cr_id=4976542660401&sb-ci-n=asinImage&sb-ci-v=https%3A%2F%2Fm.media-amazon.com%2Fimages%2FI%2F81rpcHc0XzL.jpg&sb-ci-a=B06XX29S9Q)

## Setup

### Raspbian System

Before starting setup, we need to write Raspbian system into raspberry pi MicroSD card.
[Raspbian System Installation](https://www.raspberrypi.org/documentation/installation/installing-images/)

### Gstreamer Installation & Configuration

#### Windows

[Gstreamer Installation (Windows)](https://gstreamer.freedesktop.org/documentation/installing/on-windows.html?gi-language=c)

#### Linux (Raspbian)

We need to make sure the version of Raspbian is completely up to date. Run:

     sudo apt full-upgrade

After that, type:

     sudo apt install libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio

Use 

     gst-inspect-1.0 --version

To check Gstreamer is successful downloaded or not.


##### RTSP Sever

What is RTSP? [RTSP, Wikipedia](https://en.wikipedia.org/wiki/Real_Time_Streaming_Protocol)

Download and configure the RTSP Server
1. Go to (https://gstreamer.freedesktop.org/src/gst-rtsp-server/), select the Gstreamer version you are using.
2. Download .tar.xz file
3. Extract the file
4. In terminal, go to the folder you have extracted (use "cd" command)
5. Type ./configure
6. Once you finished, type make

Note: If there is a error message said that "No package 'Glib-2.0' found" after the configuration, type:

    sudo apt-get install libglib2.0-dev

Then, re-type the ./configure again
