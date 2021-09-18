#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    
    cout << "Press ESC to quit" << endl;
    //cout << getBuildInformation() << endl;
    VideoCapture cap1("rtspsrc location=rtsp://10.32.56.75:5800/camera3 latency=100 buffer-mode=0 ! application/x-rtp,encoding-name=H264,media=video ! rtph264depay !  decodebin ! videoconvert ! appsink ", cv::CAP_GSTREAMER);
    VideoCapture cap2("rtspsrc location=rtsp://10.32.56.168:5801/camera2 latency=100 buffer-mode=0 ! application/x-rtp,encoding-name=H264,media=video ! rtph264depay !  decodebin ! videoconvert ! appsink ", cv::CAP_GSTREAMER);
    VideoCapture cap3("rtspsrc location=rtsp://10.32.56.13:5802/camera1 latency=100 buffer-mode=0 ! application/x-rtp,encoding-name=H264,media=video ! rtph264depay !  decodebin ! videoconvert ! appsink ", cv::CAP_GSTREAMER);
    if (!cap1.isOpened())    
    {  

        cout << "Webcam 1 Error" << endl;
        return -1;
    }
    if (!cap2.isOpened())
    {
        cout << "Webcam 2 Error" << endl;
        return -1;
    }
    if (!cap3.isOpened())
    {
        cout << "Webcam 3 Error" << endl;
        return -1;
    }
    
    int key = -1;
    while (key != 27) //because the ASCII value of ESC is 27
    {
        Mat frame1;
        Mat frame2;
        Mat frame3;
        cap1.read(frame1);
        cap2.read(frame2);
        cap3.read(frame3);
        if (frame1.empty())
            break;
        if (frame2.empty())
            break;
        if (frame3.empty())
            break;
        imshow("Camera 1", frame1);
        imshow("Camera 2", frame2);
        imshow("Camera 3", frame3);
        if(waitKey(1) == 27)
            break;
    }
    cap1.release();
    cap2.release();
    cap3.release();
    return 0;
}
