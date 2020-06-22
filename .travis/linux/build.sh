# adding cmake to system path
export PATH=${TRAVIS_BUILD_DIR}/${CMAKE_DIRNAME}:${TRAVIS_BUILD_DIR}/${CMAKE_DIRNAME}/bin:$PATH

mkdir build
cd build
source /opt/qt514/bin/qt514-env.sh
cmake -DMVVM_ENABLE_FILESYSTEM=OFF -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DMVVM_DISCOVER_TESTS=$TESTS_AUTODISCOVERY ..
make -j4
