#include "google_test.h"
#include <QStandardItem>
#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Q_UNUSED(app)

    ModelView::Comparators::registerComparators();
    qRegisterMetaType<QStandardItem*>("QStandardItem*");

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
