sudo apt-add-repository -y ppa:beineri/opt-qt-5.14.2-bionic
sudo apt-get -qq update 
sudo apt-get install qt514base qt514imageformats qt514svg  qt514tools libgl1-mesa-dev -y
#sudo apt-get install qt514-meta-full libgl1-mesa-dev -y
source /opt/qt514/bin/qt514-env.sh
sudo apt-get -qq clean


# install cmake
wget --no-check-certificate --quiet https://cmake.org/files/v3.17/cmake-3.17.3-Linux-x86_64.tar.gz
tar -zxf cmake-3.17.3-Linux-x86_64.tar.gz
mv ./cmake-3.17.3-Linux-x86_64 ./${CMAKE_DIRNAME}
rm cmake-3.17.3-Linux-x86_64.tar.gz
cd ${TRAVIS_BUILD_DIR}
