# install qt
sudo apt-get update
sudo apt-get install -y -qq --no-install-recommends qt5-default qtbase5-dev
sudo apt-get -qq clean

# install cmake
wget --no-check-certificate --quiet https://cmake.org/files/v3.14/cmake-3.14.6-Linux-x86_64.tar.gz
tar -zxf cmake-3.14.6-Linux-x86_64.tar.gz
mv ./cmake-3.14.6-Linux-x86_64 ./${CMAKE_DIRNAME}
rm cmake-3.14.6-Linux-x86_64.tar.gz
cd ${TRAVIS_BUILD_DIR}
