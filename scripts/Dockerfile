FROM ubuntu:latest
ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install build-essential checkinstall cmake pkg-config wget vim curl unzip -y
RUN apt-get install qt5-default -y
RUN apt-get install libprotobuf-dev protobuf-compiler -y

#opencv deps
RUN apt-get install libjpeg-dev libpng-dev libtiff-dev -y
RUN apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev -y
RUN apt-get install libxvidcore-dev libx264-dev -y
RUN apt-get install libgtk-3-dev -y
RUN apt-get install libcanberra-gtk* -y
RUN apt-get install libatlas-base-dev gfortran -y
RUN apt-get install python3-dev -y
RUN wget https://bootstrap.pypa.io/get-pip.py
RUN python3 get-pip.py
RUN pip install numpy
#install Gtest/GMock/Gflags
RUN apt-get install git libgflags-dev -y
WORKDIR /home/Documents
#Install Glog
WORKDIR /home/Documents
RUN git clone https://github.com/google/glog.git
RUN cd glog && mkdir -p build && cd build && cmake .. -Bbuild -G "Unix Makefiles" && cmake --build build && cmake --build build --target install && ldconfig
#Installing GTest & GMock
WORKDIR /home/Documents
RUN git clone https://github.com/google/googletest.git
RUN cd googletest && mkdir build && cd build && cmake .. && make -j 4 && make install && ldconfig

#Download and build opencv
WORKDIR /home/Documents
RUN wget -O opencv.zip https://github.com/opencv/opencv/archive/4.0.0.zip
RUN wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.0.0.zip
RUN unzip opencv.zip && mv opencv-4.0.0 opencv
RUN unzip opencv_contrib.zip && mv opencv_contrib-4.0.0 opencv_contrib

RUN cd opencv && mkdir build&& cd build && cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
    -D ENABLE_NEON=ON \
    -D ENABLE_VFPV3=ON \
    -D BUILD_TESTS=OFF \
    -D OPENCV_ENABLE_NONFREE=ON \
    -D INSTALL_PYTHON_EXAMPLES=OFF \
    -D BUILD_EXAMPLES=OFF ..  && make -j 4 && make install && ldconfig

 
