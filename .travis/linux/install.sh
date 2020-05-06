# install qt
sudo apt-add-repository -y ppa:beineri/opt-qt-5.12.8-bionic
sudo apt-get -qq update 
sudo apt-get -qq install libgl1-mesa-dev qt512tools qt512base qt512svg 
source /opt/qt512/bin/qt512-env.sh
sudo apt-get -qq clean

# install cmake
wget --no-check-certificate --quiet https://cmake.org/files/v3.14/cmake-3.14.6-Linux-x86_64.tar.gz
tar -zxf cmake-3.14.6-Linux-x86_64.tar.gz
mv ./cmake-3.14.6-Linux-x86_64 ./${CMAKE_DIRNAME}
rm cmake-3.14.6-Linux-x86_64.tar.gz
cd ${TRAVIS_BUILD_DIR}
