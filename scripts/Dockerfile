FROM ubuntu:latest
RUN apt-get update
RUN apt-get upgrade

RUN apt-get build-essential checkinstall cmake pkg-config yasm -y
RUN apt-get install qt5-default -y
RUN apt-get install libprotobuf-dev protobuf-compiler -y
RUN apt-get -y remove x264 libx264-dev
RUN apt-get -y install build-essential checkinstall cmake pkg-config yasm -y
RUN apt-get -y install git gfortran -y
RUN apt-get -y install libjpeg8-dev libjasper-dev libpng12-dev -y
RUN apt-get -y install libtiff5-dev -y
RUN apt-get -y install libtiff-dev -y
RUN apt-get -y install libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev -y
RUN apt-get -y install libxine2-dev libv4l-dev -y
WORKDIR /usr/include/linux
RUN ln -s -f ../libv4l1-videodev.h videodev.h
RUN apt-get -y install libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev
RUN apt-get -y install libgtk2.0-dev libtbb-dev qt5-default
RUN apt-get -y install libatlas-base-dev
RUN apt-get -y install libmp3lame-dev libtheora-dev
RUN apt-get -y install libvorbis-dev libxvidcore-dev libx264-dev
RUN apt-get -y install libopencore-amrnb-dev libopencore-amrwb-dev
RUN apt-get -y install libavresample-dev
RUN apt-get -y install x264 v4l-utils
RUN apt-get -y libgflags-dev

#opencv
WORKDIR /home/Documents
RUN git clone https://github.com/opencv/opencv.git
WORKDIR /home/Documents
RUN git clone https://github.com/opencv/opencv_contrib.git
RUN cd opencv && mkdir build&& cd build && cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D WITH_CUDA=OFF \
    -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
    -D OPENCV_ENABLE_NONFREE=ON \
    -D BUILD_EXAMPLES=ON .. && make -j 4 && make install && ldconfig

WORKDIR /home/Documents
#Install Glog
WORKDIR /home/Documents
RUN git clone https://github.com/google/glog.git
RUN cd glog && mkdir -p build && cd build && cmake .. -Bbuild -G "Unix Makefiles" && cmake --build build && cmake --build build --target install && ldconfig
#Installing GTest & GMock
WORKDIR /home/Documents
RUN git clone https://github.com/google/googletest.git
RUN cd googletest && mkdir build && cd build && cmake .. && make -j 4 && make install && ldconfig
