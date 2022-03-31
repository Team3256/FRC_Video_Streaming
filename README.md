# FRC Video Streaming
**Live camera streaming project based on GStreamer.**

**YOU'RE HERE: Master branch:** Stable. Framerate can be controlled in real-time through SmartDashboard.
hardwareencoding branch: experimental branch -- currently NOT working. attempting to have framerate AND resolution controllable through SmartDashboard and use H.264 hardware encoding on the C920 Pro webcam to reduce system overhead.

Based on [Guide to H264 Streaming in FRC](https://rianadon.github.io/blog/2019/04/04/guide-to-h264-streaming-frc.html).

"[GStreamer](https://gstreamer.freedesktop.org/) is a pipeline-based multimedia framework and software that links together a wide variety of media processing systems to complete complex workflows. It contains enormous useful commends to decode, encode, and transport your live video."

## Short-term Goals
* Minimum 360p and 30 fps live streaming from 1 or 2 cameras using 1 Raspberry Pi (done!)
* Ability to control the resolution and frame-rate in real time through SmartDashboard (WIP)

## Long-term Goals
* Implement alternative streaming protocols (ex. SRT) to try to reduce latency / interference & increase resolution

## Hardware
* 1 Raspberry Pi 4
* 2 Logitech C920 webcams (or equivalent)
* 1 Micro-SD card to install Raspbian or Ubuntu Server (>= 16 GB)
* Power cable and connection that can supply sufficient power to the Pi (IMPORTANT! if enough power is not provided, it can shut down w/out warning in the middle of camera operation)

## Documentation
1. Installing & setting up GStreamer -- [install.md](https://github.com/Team3256/FRC_Video_Streaming/blob/master/docs/install.md)
2. Real Time Streaming Protocol (RTSP) -- [RTSP.md](https://github.com/Team3256/FRC_Video_Streaming/blob/master/docs/RTSP.md)
3. Automating everything (systemd) -- [systemd.md](https://github.com/Team3256/FRC_Video_Streaming/blob/master/docs/systemd.md)
4. Making it interactive (in progress) -- [interactive.md](https://github.com/Team3256/FRC_Video_Streaming/blob/master/docs/interactive.md)
5. SRT alternative protocol (on hold) -- [SRT.md](https://github.com/Team3256/FRC_Video_Streaming/blob/master/docs/SRT.md)
