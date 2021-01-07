#include <VideoController/video_controller.h>
#include <iostream>

int main(int argc, char **argv) {
  using namespace std;
  using namespace cv;

  VideoCapture cap(0); // capture the video from webcam

  if (!cap.isOpened()) // if not success, exit program
  {
    cout << "Cannot open the web cam" << endl;
    return -1;
  } else {
    std::cout << "Exito!" << std::endl;
    double fps = cap.get(CAP_PROP_FPS);
    std::cout << "Frames per seconds : " << fps << endl;
    String window_name = "My First Video";
    while (true) {
      Mat frame;
      bool bSuccess = cap.read(frame); // read a new frame from video

      // Breaking the while loop at the end of the video
      if (bSuccess == false) {
        cout << "Found the end of the video" << endl;
        break;
      }
      // show the frame in the created window
      imshow(window_name, frame);

      // wait for for 10 ms until any key is pressed.
      // If the 'Esc' key is pressed, break the while loop.
      // If the any other key is pressed, continue the loop
      // If any key is not pressed withing 10 ms, continue the loop
      if (waitKey(10) == 27) {
        cout << "Esc key is pressed by user. Stoppig the video" << endl;
        break;
      }
    }
  }
  return 0;
}
