#include "google_test.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);

    ModelView::Comparators::registerComparators();

    // run all google tests
    return RUN_ALL_TESTS();
}
