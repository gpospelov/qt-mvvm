export PATH=/usr/local/opt/qt5/bin/:$PATH
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=/usr/local -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DMVVM_GTEST_DISCOVER_TESTS=$TESTS_AUTODISCOVRY ..
make -j4
