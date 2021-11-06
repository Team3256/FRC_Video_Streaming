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

* 360p and 30 FPS live streaming from 2 cameras using one Raspberry Pi
* Low latency
* Sustainability

## Some information about the hardware

* 1 [Raspberry Pi 4](https://www.amazon.com/Raspberry-Model-2019-Quad-Bluetooth/dp/B07TD42S27/ref=sr_1_3?crid=314J4PUEPI6ZV&keywords=raspberry+pi+4&qid=1581813926&s=electronics&sprefix=rasp%2Celectronics%2C194&sr=1-3)
* 2 Logitech C920 webcam (It supports 1080P, 30 FPS maximum) [Newer Model: C922x Pro](https://www.amazon.com/Logitech-C922x-Pro-Stream-Webcam/dp/B01LXCDPPK/ref=sr_1_1_sspa?keywords=c920s&qid=1581813651&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUFGNzg5VTNRR09PT1omZW5jcnlwdGVkSWQ9QTA1OTcyOTQySTQ2OVJGTVg1UEdEJmVuY3J5cHRlZEFkSWQ9QTA4MTQxOTIxTEMzNk1LUUY3U0U0JndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==)
* 1 Micro-SD card to install Raspbian or Ubuntu Server [Example: Samsung 64GB Version](https://www.amazon.com/dp/B06XX29S9Q?aaxitk=cbwfyKhuwZuc09zBCGigew&pd_rd_i=B06XX29S9Q&pf_rd_p=591760d1-6468-480f-9b10-0ee9c85706fd&hsa_cr_id=4976542660401&sb-ci-n=asinImage&sb-ci-v=https%3A%2F%2Fm.media-amazon.com%2Fimages%2FI%2F81rpcHc0XzL.jpg&sb-ci-a=B06XX29S9Q)

## Guides:
1. Installing and Setting Up GStreamer -- [InstallSetup.md](https://github.com/Team3256/FRC_Video_Streaming_2020/blob/master/InstallSetup.md)
2. Setting up Real Time Streaming Protocol (RTSP) -- [RTSP.md](https://github.com/Team3256/FRC_Video_Streaming_2020/blob/master/RTSP.md)
3. Automating Everything (systemd) -- [Systemd.md](https://github.com/Team3256/FRC_Video_Streaming_2020/blob/master/Systemd.md)
4. Making it interactive with SmartDashboard (in progress) -- [interactive.md](https://github.com/Team3256/FRC_Video_Streaming_2020/blob/master/interactive.md)
5. Ubuntu Server and Installing SRT (on hold) -- [SRT.md](https://github.com/Team3256/FRC_Video_Streaming_2020/blob/master/SRT.md)
