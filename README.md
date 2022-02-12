# FRC Video Streaming
**Live video streaming project based on GStreamer.**
**hardwareencoding branch:** working on native h.264 encoding on the C920 webcam

Links:
* [Guide to H264 Streaming in FRC](https://rianadon.github.io/blog/2019/04/04/guide-to-h264-streaming-frc.html)
* [OpenCV and Gstreamer (C++)](https://github.com/tik0/mat2gstreamer)
* [Shared memory](https://github.com/tik0/mat2gstreamer)

"[GStreamer](https://gstreamer.freedesktop.org/) is a pipeline-based multimedia framework and software that links together a wide variety of media processing systems to complete complex workflows. It contains enormous useful commends to decode, encode, and transport your live video."

## Goals
* Minimum 360p and 30 fps live streaming from 2 cameras using 1 Raspberry Pi through RTSP (done!)
* Ability to control the resolution and frame-rate in real time through SmartDashboard (WIP)
* Alternative streaming protocols (SRT) in an effort to reduce latency and increase resolution without increasing bandwidth
* Testing with a real-world network environment — heavily congested, lots of networks and robots being used — to ensure that the video feed will be clear at competition

## Hardware
* 1 Raspberry Pi 4
* 2 Logitech C920 webcams (or equivalent)
* 1 Micro-SD card to install Raspbian or Ubuntu Server (preferably at least 16 GB)
* Power cable and connection that can supply sufficient power to the Pi

## Additional Considerations
* Will we continue to use a Raspberry Pi? (If we use a Jetson we may be able to offload some of the functions to it.)
* Camera placement — will be dependent on drivers. 360p and 30 fps at a minimum should be OK, maybe to make it easier for drivers to see we can outline the balls that should be collected and desaturate the opposing team's colors

## Documentation
1. Installing and Setting Up GStreamer -- [install.md](https://github.com/Team3256/FRC_Video_Streaming/blob/master/docs/install.md)
2. Setting up Real Time Streaming Protocol (RTSP) -- [RTSP.md](https://github.com/Team3256/FRC_Video_Streaming/blob/master/docs/RTSP.md)
3. Automating Everything (systemd) -- [systemd.md](https://github.com/Team3256/FRC_Video_Streaming/blob/master/docs/systemd.md)
4. Making it interactive with SmartDashboard (in progress) -- [interactive.md](https://github.com/Team3256/FRC_Video_Streaming/blob/master/docs/interactive.md)
5. Ubuntu Server and Installing SRT (on hold) -- [SRT.md](https://github.com/Team3256/FRC_Video_Streaming/blob/master/docs/SRT.md)

## To-do
- Adjusting resolution to anything other than 360p, including 240p and 720p results in an error -- "reason not-negotiated (-4)"
- Need to fully test w/ SmartDashboard
