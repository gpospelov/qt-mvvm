#include "google_test.h"
#include <QStandardItem>

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    ModelView::Comparators::registerComparators();
    qRegisterMetaType<QStandardItem*>("QStandardItem*");

    // run all google tests
    return RUN_ALL_TESTS();
}
