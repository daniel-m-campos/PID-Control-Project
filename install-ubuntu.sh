#! /bin/bash
sudo apt-get install libuv1-dev libssl-dev libz-dev
git clone https://github.com/uWebSockets/uWebSockets
cd uWebSockets || exit
git checkout e94b6e1
mkdir build
cd build || exit
cmake ..
make
sudo make install
cd ..
cd ..
sudo ln -s /usr/lib64/libuWS.so /usr/lib/libuWS.so
sudo rm -r uWebSockets

sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt update -y
sudo apt install -y gcc-9 g++-9
export CC=gcc-9
export CXX=g++-9
