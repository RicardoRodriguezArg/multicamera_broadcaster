#include <VideoController/video_controller.h>
#include <iostream>

int main(int argc, char **argv) 
{
cv::VideoCapture _cv;
if(_cv.open("tcp://192.168.0.1:8080")) { // change MACRO to the actual values!
   std::cout << "Yahoo!!!"<< std::endl;
} else {
   std::cerr << "Can not open video source!";
}
 return 0; }
