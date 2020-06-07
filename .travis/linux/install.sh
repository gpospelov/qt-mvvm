# install qt
sudo add-apt-repository ppa:ymshenyu/qt514
sudo apt-get update
sudo apt-get install qt5-default libqt5designercomponents5 qttools5-dev libqt5svg5-dev libqt5opengl5-dev libgl1-mesa-dev -y

# install cmake
wget --no-check-certificate --quiet https://cmake.org/files/v3.17/cmake-3.17.3-Linux-x86_64.tar.gz
tar -zxf cmake-3.17.3-Linux-x86_64.tar.gz
mv ./cmake-3.17.3-Linux-x86_64 ./${CMAKE_DIRNAME}
rm cmake-3.17.3-Linux-x86_64.tar.gz
cd ${TRAVIS_BUILD_DIR}
