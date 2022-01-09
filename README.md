# FRC Video Streaming

**This is the live video streaming project based on GStreamer. We connect our webcams to different Raspberry Pi's and they will send the video to the driver station.**

Links:
* [Guide to H264 Streaming in FRC](https://rianadon.github.io/blog/2019/04/04/guide-to-h264-streaming-frc.html)
* [OpenCV and Gstreamer (C++)](https://github.com/tik0/mat2gstreamer)
* [Shared memory](https://github.com/tik0/mat2gstreamer)

[GStreamer](https://gstreamer.freedesktop.org/) is a pipeline-based multimedia framework and software that links together a wide variety of media processing systems to complete complex workflows. It contains enormous useful commends to decode, encode, and transport your live video. 
  
## Goals
* Minimum 360p and 30 fps live streaming from 2 cameras using 1 Raspberry Pi
* Low latency
* Sustainability

## Hardware
* 1 Raspberry Pi 4
* 2 Logitech C920 webcam (or equivalent) 
* 1 Micro-SD card to install Raspbian or Ubuntu Server (preferably at least 16 GB)

## Documentation
1. Installing and Setting Up GStreamer -- [InstallSetup.md](https://github.com/Team3256/FRC_Video_Streaming_2020/blob/master/docs/InstallSetup.md)
2. Setting up Real Time Streaming Protocol (RTSP) -- [RTSP.md](https://github.com/Team3256/FRC_Video_Streaming_2020/blob/master/docs/RTSP.md)
3. Automating Everything (systemd) -- [Systemd.md](https://github.com/Team3256/FRC_Video_Streaming_2020/blob/master/docs/Systemd.md)
4. Making it interactive with SmartDashboard (in progress) -- [interactive.md](https://github.com/Team3256/FRC_Video_Streaming_2020/blob/master/docs/interactive.md)
5. Ubuntu Server and Installing SRT (on hold) -- [SRT.md](https://github.com/Team3256/FRC_Video_Streaming_2020/blob/master/docs/SRT.md)
