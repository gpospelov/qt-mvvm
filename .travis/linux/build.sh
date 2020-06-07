docker exec dd bash -c "mkdir build"
docker exec dd bash -c "cd build && cmake -DMVVM_ENABLE_FILESYSTEM=OFF -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DMVVM_GTEST_DISCOVER_TESTS=$TESTS_AUTODISCOVERY .."
docker exec dd bash -c "cd build && QT_DEBUG_PLUGINS=1 QT_QPA_PLATFORM=offscreen && make -j4"
