# install qt
sudo apt-add-repository -y ppa:beineri/opt-qt-5.13.2-bionic
sudo apt-get -qq update 
sudo apt-get install qt513base qt5133d qt513imageformats qt513svg  qt513tools -y
sudo apt-get install libgl1-mesa-dev -y
source /opt/qt513/bin/qt513-env.sh
sudo apt-get -qq clean

# install cmake
wget --no-check-certificate --quiet https://cmake.org/files/v3.14/cmake-3.14.6-Linux-x86_64.tar.gz
tar -zxf cmake-3.14.6-Linux-x86_64.tar.gz
mv ./cmake-3.14.6-Linux-x86_64 ./${CMAKE_DIRNAME}
rm cmake-3.14.6-Linux-x86_64.tar.gz
cd ${TRAVIS_BUILD_DIR}
