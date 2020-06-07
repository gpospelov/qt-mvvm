# install qt
sudo add-apt-repository -y ppa:ymshenyu/qt514
sudo apt-get -qq update 

sudo apt-get install libgl1-mesa-dev -y
sudo apt-get install qtbase-opensource-src qttools-opensource-src -y

# install cmake
wget --no-check-certificate --quiet https://cmake.org/files/v3.17/cmake-3.17.3-Linux-x86_64.tar.gz
tar -zxf cmake-3.17.3-Linux-x86_64.tar.gz
mv ./cmake-3.17.3-Linux-x86_64 ./${CMAKE_DIRNAME}
rm cmake-3.17.3-Linux-x86_64.tar.gz
cd ${TRAVIS_BUILD_DIR}
