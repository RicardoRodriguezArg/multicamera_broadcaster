apt-get install build-essential checkinstall cmake pkg-config wget vim curl unzip -y
apt-get install qt5-default -y
apt-get install libprotobuf-dev protobuf-compiler -y

#opencv deps
apt-get install libjpeg-dev libpng-dev libtiff-dev -y
apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev -y
apt-get install libxvidcore-dev libx264-dev -y
apt-get install libgtk-3-dev -y
apt-get install libcanberra-gtk* -y
apt-get install libatlas-base-dev gfortran -y
apt-get install python3-dev -y
apt-get -y install libgphoto2-dev libeigen3-dev libhdf5-dev doxygen netcat# net-tools
#Raspi cam drivers
apt-get install autoconf gettext libtool libjpeg62-dev -y
wget https://bootstrap.pypa.io/get-pip.py
python3 get-pip.py
pip install numpy
#install Gtest/GMock/Gflags
apt-get install git libgflags-dev clang-tidy clang-format -y
/home/Documents
git clone https://github.com/google/glog.git
cd glog && mkdir -p build && cd build && cmake .. -Bbuild -G "Unix Makefiles" && cmake --build build && cmake --build build --target install && ldconfig
#Installing GTest & GMock
cd /home/Documents
git clone https://github.com/google/googletest.git
cd googletest && mkdir build && cd build && cmake .. && make -j 4 && make install && ldconfig

git clone https://github.com/opencv/opencv.git && cd opencv && git checkout 4.5.1
git clone https://github.com/opencv/opencv_contrib.git && cd opencv_contrib && git checkout 4.5.1
cd opencv && mkdir build&& cd build && cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
    -D ENABLE_NEON=OFF \
    -D ENABLE_VFPV3=OFF \
    -D BUILD_TESTS=OFF \
    -D OPENCV_ENABLE_NONFREE=ON \
    -D INSTALL_PYTHON_EXAMPLES=OFF \
    -D BUILD_EXAMPLES=OFF ..  && make && make install && ldconfig

sudo usermod -aG video operador
sudo chmod 777 /dev/vchiq
sudo apt-get install v4l-utils -y    
sudo modprobe bcm2835-v4l2

